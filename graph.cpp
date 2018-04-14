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

Graph* Graph::minimumSpanningTree() {
	Graph* g = copy();
	return g;
}
