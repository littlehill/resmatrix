#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <string>

//using namespace std;

#include "networktypes.hpp"

class Network {
	std::vector<Junction*> junctions;
	std::vector<Impedance*> imps;
	
	public:
	Network();
	ulong getJunctionUID(string name);
	Junction * getJunction(string name);
	Junction * getJunction(ulong jUID);
	
	void addJunction(string name);
	void addJunction(Junction * jnc);
	void addImpedance(Impedance * inz);
	
	std::stringstream * printAllContent();
	
};

void insertResistorMatrix(Network * matrix, unsigned int xsize, unsigned int ysize);

#endif



