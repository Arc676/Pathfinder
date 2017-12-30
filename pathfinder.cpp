//Pathfinder library, version 1.0
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

std::list<Node*> Pathfinder::dijkstra(Graph* graph, Node* start, Node* end) {
	std::map<std::string, Node*> nodes = graph->getNodes();
	Node* current = nodes[start->getName()];

	std::map<Node*, NodeInfo> nodeInfo;
	for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		nodeInfo[it->second] = {false, -1, nullptr};
	}
	nodeInfo[start].distance = 0;
	nodeInfo[start].bestPath = start;

	while (true) {
		nodeInfo[current].locked = true;
		if (nodeInfo[end].locked) {
			break;
		}
		std::map<std::string, float> adjacent = current->getAdjacentNodes();
		for (std::map<std::string, float>::iterator it = adjacent.begin(); it != adjacent.end(); it++) {
			Node* nextNode = nodes[it->first];
			float currentDistance = it->second + nodeInfo[current].distance;
			if (nodeInfo[nextNode].distance < 0 ||
			    currentDistance < nodeInfo[nextNode].distance) {
				nodeInfo[nextNode].distance = currentDistance;
				nodeInfo[nextNode].bestPath = current;
			}
		}
		float lowestDistance = -1;
		for (std::map<std::string, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
			Node* node = it->second;
			if (!nodeInfo[node].locked && (lowestDistance < 0 || 
							(nodeInfo[node].distance > 0 && nodeInfo[node].distance < lowestDistance))) {
				lowestDistance = nodeInfo[node].distance;
				current = node;
			}
		}
	}

	std::list<Node*> path;
	path.push_front(current);
	while (current->getName() != start->getName()) {
		current = nodeInfo[current].bestPath;
		path.push_front(current);
	}
	return path;
}
