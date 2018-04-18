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

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <fstream>
#include <map>
#include <list>
#include <set>
#include <algorithm>

#include "node.h"

class Graph {
	std::map<std::string, Node*> nodes;
public:
	/**
	 * Create an empty graph
	 */
	Graph();

	/**
	 * Load a graph from file
	 * @param fn Filename
	 */
	Graph(const std::string& fn);

	/**
	 * Copy a graph
	 * @return A deep copy of the graph
	 */
	Graph* copy();

	/**
	 * Create a new node from string form and
	 * add it to the graph
	 * @param data Node data in string form
	 */
	Node* addNodeFromString(const std::string& data);

	/**
	 * Convert the graph to string form
	 * @return String representing graph
	 */
	std::string toString();

	/**
	 * Save the graph to disk
	 * @param fn Filename
	 */
	void save(const std::string& fn);

	std::map<std::string, Node*> getNodes();

	/**
	 * Add a node to the graph
	 * @param n Node to add
	 */
	void addNode(Node* n);

	/**
	 * Remove a node from the graph
	 * @param n Node to remove
	 */
	void removeNode(Node* n);

	/**
	 * Rename a node in the graph
	 * @param node Node to rename
	 * @param name New name for node
	 */
	void renameNode(Node* node, const std::string& name);

	/**
	 * Connect two nodes in the graph
	 * @param n1 First node
	 * @param n2 Second node
	 * @param d Distance
	 */
	void connectNodes(Node* n1, Node* n2, float d);

	/**
	 * Disconnect two nodes in the graph
	 * @param n1 First node
	 * @param n2 Second node
	 */
	void disconnectNodes(Node* n1, Node* n2);

	/**
	 * Determine the total weight of the graph
	 * @return The sum of the weights of all the edges
	 */
	float totalGraphWeight();

	/**
	 * Obtain the minimum spanning tree for the graph
	 * using Kruskal's algorithm
	 * @return A new Graph object representing the MST
	 */
	Graph* minimumSpanningTree();

	/**
	 * Determine whether the graph is cyclic
	 * @return Whether any cycles are present in the graph
	 */
	bool isCyclic();

	/**
	 * Determine whether there is a cycle, starting at a given node
	 * and searching recursively
	 * @param n Node from which to start searching
	 * @param visited Map indicating which nodes have been visited
	 * @param p The node from which the search began
	 * @return Whether a cycle has been found
	 */
	bool hasCycleFrom(Node* n, std::map<Node*, bool>& visited, Node* p);
};

#endif
