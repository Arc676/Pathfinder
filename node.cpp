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

//Based on work by Matthew Chen
//Copyright (C) 2017 Matthew Chen

#include "node.h"

Node::Node(const std::string &text) {
	std::istringstream ss(text);
	ss >> name;
	while (ss) {
		std::string node;
		float distance;
		ss >> node;
		if (node == "") {
			break;
		}
		ss >> distance;
		addAdjacentNodeByName(node, distance);
	}
}

Node* Node::copy() {
	return new Node(toString());
}

std::string Node::toString() {
	std::ostringstream ss;
	ss << name << " ";
	#if __cplusplus >= 201703L

	for (auto const& [node, edge] : adjacentNodes) {

	#else

	for (std::map<std::string, Edge*>::iterator it = adjacentNodes.begin(); it != adjacentNodes.end(); it++) {
		std::string node = it->first;
		Edge* edge = it->second;

	#endif

		ss << node << " " << edge->getWeight() << " ";
	}
	return ss.str();
}

std::map<std::string, Edge*> Node::getAdjacentNodes() {
	return adjacentNodes;
}

void Node::setName(const std::string &newName) {
	name = newName;
	#if __cplusplus >= 201703L

	for (auto const& [node, edge] : adjacentNodes) {

	#else

	for (std::map<std::string, Edge*>::iterator it = adjacentNodes.begin(); it != adjacentNodes.end(); it++) {
		Edge* edge = it->second;

	#endif
		edge->setNode1(newName);
	}
}

std::string Node::getName() {
	return name;
}

void Node::addAdjacentNode(Node* node, float distance) {
	addAdjacentNodeByName(node->getName(), distance);
}

void Node::addAdjacentNodeByName(const std::string &name, float distance) {
	adjacentNodes[name] = new Edge(getName(), name, distance);
}

void Node::updateAdjacentNodeName(const std::string &oldName, const std::string &newName) {
	Edge* edge = adjacentNodes[oldName];
	adjacentNodes.erase(oldName);
	edge->setNode2(newName);
	adjacentNodes[newName] = edge;
}

void Node::updateAdjacentNodeDistance(const std::string &node, float dist) {
	adjacentNodes[node]->setWeight(dist);
}

void Node::removeAdjacentNode(Node* node) {
	removeAdjacentNodeByName(node->getName());
}

void Node::removeAdjacentNodeByName(const std::string &name) {
	adjacentNodes.erase(name);
}
