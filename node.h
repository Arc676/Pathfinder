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

#ifndef NODE_H
#define NODE_H

#include <map>
#include <sstream>
#include <string>

#include "edge.h"

class Node {
	std::string name;
	std::map<std::string, Edge*> adjacentNodes;
public:
	/**
	 * Create a new node with the given data
	 * @param data Node data in string form
	 */
	Node(const std::string& data);

	/**
	 * Copy the node
	 * @return A deep copy of the node
	 */
	Node* copy();

	/**
	 * Convert the node to string form
	 * @return String containing node data
	 */
	std::string toString();

	std::map<std::string, Edge*> getAdjacentNodes();

	void setName(const std::string&);
	std::string getName();

	/**
	 * Indicate that a given node is adjacent to this one
	 * @param n Name of adjacent node
	 * @param d Weight of connecting edge
	 */
	void addAdjacentNodeByName(const std::string& n, float d);

	/**
	 * Indicate that a given node is adjacent to this one
	 * @param n The adjacent node
	 * @param d Weight of conencting edge
	 */
	void addAdjacentNode(Node* n, float d);

	/**
	 * Change the name of an adjacent node
	 * @param name The name of the node
	 * @param newname The new name of the node
	 */
	void updateAdjacentNodeName(const std::string& name, const std::string& newname);

	/**
	 * Change the weight of the edge to an adjacent node
	 * @param name The name of the node
	 * @param weight The new weight of the edge
	 */
	void updateAdjacentNodeDistance(const std::string& name, float weight);

	/**
	 * Indicate that a given node is not adjacent to this one
	 * @param n The name of the node
	 */
	void removeAdjacentNodeByName(const std::string& n);

	/**
	 * Indicate that a given node is not adjacent to this one
	 * @param n The node
	 */
	void removeAdjacentNode(Node* n);
};

#endif
