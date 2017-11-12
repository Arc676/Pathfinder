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

Graph::Graph(const std::string &filename) : nodes() {
	std::ifstream file;
	file.open(filename);
	if (!file.is_open()) {
		return;
	}
	std::string line;
	while (getline(file, line)) {
		Node* n = new Node(line);
		nodes[n->getName()] = n;
	}
	file.close();
}

void Graph::save(const std::string &filename) {
	std::ofstream file;
	file.open(filename);
	if (!file.is_open()) {
		return;
	}
	for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		file << it->second->toString() << "\n";
	}
	file.close();
}

std::map<std::string, Node*> Graph::getNodes() {
	return nodes;
}

void Graph::addNode(Node* node) {
	nodes[node->getName()] = node;
}

void Graph::removeNode(Node* node) {
	nodes.erase(node->getName());
}
