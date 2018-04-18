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

#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <list>
#include <map>

#include "graph.h"

struct NodeInfo {
	bool locked;
	float distance;
	Node* bestPath;
};

class Pathfinder {
public:
	/**
	 * Find the shortest path between two nodes using
	 * Dijkstra's Algorithm
	 * @param g The graph in which to search
	 * @param n1 The starting node
	 * @param n2 The destination node
	 * @return A list representing the shortest path found
	 */
	static std::list<Node*> dijkstra(Graph*, Node*, Node*);
};

#endif
