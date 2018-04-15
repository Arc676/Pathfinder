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

Edge::Edge(std::string n1, std::string n2, float dist) : node1(n1), node2(n2), dist(dist) {}

bool Edge::operator== (const Edge &e1, const Edge &e2) {
	//edges are not equal if their weights differ
	if (e1.dist != e2.dist) {
		return false;
	}
	//edges are equal if they have the same endpoints regardless of direction
	if (e1.node1 == e2.node1 && e1.node2 == e2.node2) {
		return true;
	}
	if (e1.node1 == e2.node2 && e1.node2 == e2.node1) {
		return true;
	}
	return false;
}

bool Edge::operator!= (const Edge &e1, const Edge &e2) {
	return !(e1 == e2);
}

Edge* Edge::reverse() {
	return new Edge(node2, node1, dist);
}

void Edge::setNode1(const std::string &n) {
	node1 = n;
}

std::string Edge::getNode1() {
	return node1;
}

void Edge::setNode2(const std::string &n) {
	node2 = n;
}

std::string Edge::getNode2() {
	return node2;
}

void Edge::setWeight(float dist) {
	this->dist = dist;
}

float Edge::getWeight() {
	return dist;
}
