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

Graph::Graph(const std::string &filename) : Graph() {
	std::ifstream file;
	file.open(filename);
	if (!file.is_open()) {
		return;
	}
	std::string line;
	while (getline(file, line)) {
		addNodeFromString(line);
	}
	file.close();
}

Graph* Graph::copy() {
	Graph* g = new Graph();
	for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		g->addNode(it->second->copy());
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
	for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		ss << it->second->toString() << "\n";
	}
	return ss.str();
}

std::map<std::string, Node*> Graph::getNodes() {
	return nodes;
}

void Graph::addNode(Node* node) {
	nodes[node->getName()] = node;
}

void Graph::removeNode(Node* node) {
	for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		if (it->second->getName() == node->getName()) {
			continue;
		}
		if (it->second->getAdjacentNodes().count(node->getName()) != 0) {
			it->second->removeAdjacentNode(node);
		}
	}
	nodes.erase(node->getName());
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
	for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		std::map<std::string, Edge*> adjacent = it->second->getAdjacentNodes();
		if (adjacent.count(originalName)) {
			it->second->updateAdjacentNodeName(originalName, newName);
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
	for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		std::map<std::string, Edge*> adjacent = it->second->getAdjacentNodes();
		for (std::map<std::string, Edge*>::iterator it2 = adjacent.begin(); it2 != adjacent.end(); it2++) {
			totalWeight += it2->second->getWeight();
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
	for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		g->addNodeFromString(it->second->getName());
		std::map<std::string, Edge*> adjacent = it->second->getAdjacentNodes();

		std::list<Edge*> newEdges = std::list<Edge*>();

		//check which edges to adjacent nodes are already listed
		for (std::map<std::string, Edge*>::iterator edgeit = adjacent.begin(); edgeit != adjacent.end(); edgeit++) {
			Edge* edge = edgeit->second;
			bool found = false;
			for (std::list<Edge*>::iterator it2 = edges.begin(); it2 != edges.end(); it2++) {
				if (*edge == **it2) {
					found = true;
				}
			}
			if (!found) {
				newEdges.push_back(edge);
			}
		}
		//add new edges to list
		for (std::list<Edge*>::iterator newEdge = newEdges.begin(); newEdge != newEdges.end(); newEdge++) {
			edges.push_back(*newEdge);
		}
	}

	//sort the list of edges by weight
	edges.sort(edgeCompare);

	//list of nodes already connected
	std::list<std::string> spannedNodes = std::list<std::string>();

	//nodes in graph
	std::map<std::string, Node*> gnodes = g->getNodes();

	//add the edges back to the graph until the graph represents a spanning tree
	int edgesAdded = 0;
	for (std::list<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
		Edge* edge = *it;
		bool n1Found = false, n2Found = false;

		//search for the edge's endpoints
		for (std::list<std::string>::iterator node = spannedNodes.begin(); node != spannedNodes.end(); node++) {
			if (!n1Found && *node == edge->getNode1()) {
				n1Found = true;
			}
			if (!n2Found && *node == edge->getNode2()) {
				n2Found = true;
			}
			//if both nodes found, stop looking
			if (n1Found && n2Found) {
				break;
			}
		}

		//in order for a cycle to form, both endpoints must already be spanned
		//if either endpoint is missing, add the edge
		if (!n1Found || !n2Found) {
			Node* n1 = gnodes[edge->getNode1()];
			Node* n2 = gnodes[edge->getNode2()];

			//connect nodes
			connectNodes(n1, n2, edge->getWeight());
			edgesAdded++;

			//if necessary, indicate nodes are now connected
			if (!n1Found) {
				spannedNodes.push_back(edge->getNode1());
			}
			if (!n2Found) {
				spannedNodes.push_back(edge->getNode2());
			}
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
	for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		visited[it->second] = false;
	}
	for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		Node* node = it->second;
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
	for (std::map<std::string, Edge*>::iterator it = adjacent.begin(); it != adjacent.end(); it++) {
		Node* adjNode = nodes[it->second->getNode2()];
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
