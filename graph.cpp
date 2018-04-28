//Pathfinder library, version 1.3
//Written by Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>
//Copyright (C) 2017-2018 Arc676/Alessandro Vinciguerra

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3)

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//See README and LICENSE for more details

#include "graph.h"

Graph::Graph() : nodes() {}

Graph* Graph::graphFromFile(const std::string &filename) {
	std::ifstream file;
	file.open(filename);
	if (!file.is_open()) {
		return nullptr;
	}
	Graph* g = new Graph();
	std::string line;
	while (getline(file, line)) {
		g->addNodeFromString(line);
	}
	file.close();
	return g;
}

Graph* Graph::graphFromAdjacencyTable(const std::string &filename) {
	std::ifstream file;
	file.open(filename);
	if (!file.is_open()) {
		return nullptr;
	}
	Graph* g = new Graph();
	std::string line;
	std::stringstream nodedata;
	int node = 0;
	while (getline(file, line)) {
		nodedata << node << " ";

		std::stringstream row(line);
		std::string edge;
		int adj = 0;
		while (getline(row, edge, ',')) {
			try {
				float weight = std::stof(edge);
				nodedata << adj << " " << weight << " ";
			} catch (const std::invalid_argument &e) {}
			adj++;
		}
		g->addNodeFromString(nodedata.str());
		nodedata.str("");
		node++;
	}
	file.close();
	return g;
}

Graph* Graph::copy() {
	Graph* g = new Graph();
	for (auto const& [name, node] : nodes) {
		g->addNode(node->copy());
	}
	return g;
}

Node* Graph::addNodeFromString(const std::string& data) {
	Node* n = new Node(data);
	addNode(n);
	return n;
}

void Graph::save(const std::string &filename) {
	std::ofstream file;
	file.open(filename);
	if (!file.is_open()) {
		return;
	}
	file << toString();
	file.close();
}

std::string Graph::toString() {
	std::stringstream ss;
	for (auto const& [name, node] : nodes) {
		ss << node->toString() << "\n";
	}
	return ss.str();
}

std::map<std::string, Node*> Graph::getNodes() {
	return nodes;
}

void Graph::addNode(Node* node) {
	nodes[node->getName()] = node;
}

void Graph::removeNode(Node* toRemove) {
	for (auto const& [name, node] : nodes) {
		if (node->getName() == toRemove->getName()) {
			continue;
		}
		if (node->getAdjacentNodes().count(toRemove->getName()) != 0) {
			node->removeAdjacentNode(toRemove);
		}
	}
	nodes.erase(toRemove->getName());
}

void Graph::renameNode(Node* node, const std::string &newName) {
	if (node->getName() == newName) {
		return;
	}
	std::string originalName = node->getName();
	Node* modifiedNode = nodes[originalName];
	nodes.erase(originalName);
	modifiedNode->setName(newName);
	nodes[newName] = modifiedNode;
	for (auto const& [name, node] : nodes) {
		std::map<std::string, Edge*> adjacent = node->getAdjacentNodes();
		if (adjacent.count(originalName)) {
			node->updateAdjacentNodeName(originalName, newName);
		}
	}
}

void Graph::connectNodes(Node* n1, Node* n2, float dist) {
	n1->addAdjacentNode(n2, dist);
	n2->addAdjacentNode(n1, dist);
}

void Graph::disconnectNodes(Node* n1, Node* n2) {
	n1->removeAdjacentNode(n2);
	n2->removeAdjacentNode(n1);
}

float Graph::totalGraphWeight() {
	float totalWeight = 0;
	for (auto const& [name, node] : nodes) {
		std::map<std::string, Edge*> adjacent = node->getAdjacentNodes();
		for (auto const& [adjName, edge] : adjacent) {
			totalWeight += edge->getWeight();
		}
	}
	return totalWeight / 2;
}

bool edgeCompare(Edge* e1, Edge* e2) {
	return *e1 < *e2;
}

Graph* Graph::minimumSpanningTree() {
	Graph* g = new Graph();
	std::list<Edge*> edges = std::list<Edge*>();
	
	//copy nodes without connections to new graph
	//build list of nodes and edges
	for (auto const& [nodeName, node] : nodes) {
		g->addNodeFromString(nodeName);
		std::map<std::string, Edge*> adjacent = node->getAdjacentNodes();

		std::list<Edge*> newEdges = std::list<Edge*>();

		//check which edges to adjacent nodes are already listed
		for (auto const& [adjName, edge] : adjacent) {
			bool found = false;
			for (auto const& edge2 : edges) {
				if (*edge == *edge2) {
					found = true;
					break;
				}
			}
			if (!found) {
				newEdges.push_back(edge);
			}
		}
		//add new edges to list
		for (auto const& newEdge : newEdges) {
			edges.push_back(newEdge);
		}
	}

	//sort the list of edges by weight
	edges.sort(edgeCompare);

	//set of nodes already connected
	std::set<std::string> spannedNodes = std::set<std::string>();

	//nodes in graph
	std::map<std::string, Node*> gnodes = g->getNodes();

	//add the edges back to the graph until the graph represents a spanning tree
	int edgesAdded = 0;
	for (auto const& edge : edges) {
		Node* n1 = gnodes[edge->getNode1()];
		Node* n2 = gnodes[edge->getNode2()];

		//connect the nodes
		g->connectNodes(n1, n2, edge->getWeight());

		std::map<Node*, bool> visited = std::map<Node*, bool>();
		for (auto const& [name, node] : nodes) {
			visited[node] = false;
		}

		//if adding this edge creates a cycle, discard the edge
		//otherwise, add the edge and continue
		if (g->hasCycleFrom(n1, visited, nullptr)) {
			g->disconnectNodes(n1, n2);
		} else {
			edgesAdded++;
			spannedNodes.insert(edge->getNode1());
			spannedNodes.insert(edge->getNode2());
		}

		//if all nodes are spanned AND there are (v - 1) edges, MST has been created
		if (spannedNodes.size() == gnodes.size() && edgesAdded == gnodes.size() - 1) {
			break;
		}
	}

	//return the minimum spanning tree
	return g;
}

bool Graph::isCyclic() {
	std::map<Node*, bool> visited = std::map<Node*, bool>();
	for (auto const& [name, node] : nodes) {
		visited[node] = false;
	}
	for (auto const& [name, node] : nodes) {
		if (!visited[node]) {
			if (hasCycleFrom(node, visited, nullptr)) {
				return true;
			}
		}
	}
	return false;
}

bool Graph::hasCycleFrom(Node* node, std::map<Node*, bool> &visited, Node* parent) {
	visited[node] = true;
	std::map<std::string, Edge*> adjacent = node->getAdjacentNodes();
	for (auto const& [adjName, edge] : adjacent) {
		Node* adjNode = nodes[edge->getNode2()];
		if (!visited[adjNode]) {
			if (hasCycleFrom(adjNode, visited, node)) {
				return true;
			}
		} else if (adjNode != parent) {
			return true;
		}
	}
	return false;
}
