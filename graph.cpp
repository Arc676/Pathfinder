//Written by Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>
//Copyright (C) 2017 Arc676/Alessandro Vinciguerra

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
		loadGraphDataFromString(line);
	}
	file.close();
}

void Graph::loadGraphDataFromString(const std::string& data) {
	Node* n = new Node(data);
	nodes[n->getName()] = n;
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
