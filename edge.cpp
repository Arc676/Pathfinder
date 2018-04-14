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

#include "edge.h"
#include "node.h"

Edge::Edge(Node* n1, Node* n2, float dist) : dist(dist) {
	node1 = n1;
	node2 = n2;
}

Node* Edge::getNode1() {
	return node1;
}

Node* Edge::getNode2() {
	return node2;
}

float Edge::getWeight() {
	return dist;
}
