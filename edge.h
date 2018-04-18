//Pathfinder library, version 1.3
//Written by Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>
//Copyright (C) 2018 Arc676/Alessandro Vinciguerra

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

#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge {
	std::string node1;
	std::string node2;
	float dist;
public:
	/**
	 * Create a new Edge
	 * @param n1 First node
	 * @param n2 Second node
	 * @param d Edge weight
	 */
	Edge(std::string n1, std::string n2, float d);

	/**
	 * Compare two edges for equality; Edges are equal
	 * if they have the same weight and connect
	 * the same endpoints
	 * @param e Other edge
	 * @return Whether the edges are equal
	 */
	bool operator== (const Edge& e);

	/**
	 * Check if edges are not equal
	 * @param e Other edge
	 * @return Whether the edges are not the same edge
	 */
	bool operator!= (const Edge& e);

	/**
	 * Compare edges
	 * @param e Other edge
	 * @return Whether this edge has a lower weight than the other edge
	 */
	bool operator<  (const Edge& e);

	void setNode1(const std::string&);
	void setNode2(const std::string&);
	void setWeight(float);

	std::string getNode1();
	std::string getNode2();
	float getWeight();
};

#endif
