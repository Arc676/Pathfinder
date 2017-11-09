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

//Based on work by Matthew Chen
//Copyright (C) 2017 Matthew Chen

#include "pathfinder.h"
/*
Node* Pathfinder::findNodeByName(std::vector<Node*> nodes, Node* node) {
	for (std::vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		if ((*it)->getName() == node->getName()) {
			return *it;
		}
	}
	return nullptr;
}
*/
std::vector<Node*> Pathfinder::dijkstra(Graph* graph, Node* start, Node* end) {
/*	std::vector<Node*> nodes = graph->getNodes();
	Node* current = Pathfinder::findNodeByName(nodes, start);
	Node* dest = Pathfinder::findNodeByName(nodes, end);*/

	std::map<std::string, Node*> nodes = graph->getNodes();
	Node* current = nodes[start->getName()];

	std::map<Node*, bool> nodeLock;
	std::map<Node*, float> nodeDistances;
	for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		nodeLock[it->second] = false;
		nodeDistances[it->second] = -1;
	}
	nodeDistances[start] = 0;

	while (true) {
		nodeLock[current] = true;
		if (nodeLock[dest]) {
			break;
		}
		for (std::map<std::string, float>::iterator it = current->getAdjacentNodes().begin(); it != current->getAdjacentNodes().end(); it++) {
			Node* nextNode = nodes[it->first];
			float currentDistance = it->second + nodeDistances[current];
			if (nodeDistances[nextNode] < 0 ||
			    currentDistance < nodeDistances[nextNode]) {
				nodeDistances[nextNode] = currentDistance;
			}
		}
		float lowestDistance = -1;
		for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
			Node* node = it->second;
			if (!nodeLock[node] && (lowestDistance < 0 || nodeDistances[node] < lowestDistance)) {
				current = node;
			}
		}
	}

	std::list<Node*> path;
	path.push_front(current);
	while (current->getName() != start->getName()) {
		
	}
	return path;
}
