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
	
	public:
	std::vector<Junction*> junctions;
	std::vector<Impedance*> imps;
	
	Network();
	Network(Network *cloneme);
	ulong getJunctionUID(string name);
	Junction * getJunction(string name);
	Junction * getJunction(ulong UID);
	Impedance * getImpedance(ulong jUID);
	bool existsInNet(Connection *what);
	
	long int getJposition(ulong UID);
	long int getIposition(ulong UID);
	
	void addJunction(string name);
	void addJunction(Junction * jnc);
	void addImpedance(Impedance * inz);
	bool removeJunction(ulong UID);
	bool removeImpedance(ulong UID);
	bool removeJunction(Junction *soonToBeDeadJunction);
	bool removeImpedance(Impedance *soonToBeDeadImpedance);		
		
	std::stringstream * printAllContent();
};

void insertResistorMatrix(Network * matrix, unsigned int xsize, unsigned int ysize);
bool starMeshTransformation(Network *matrix, Junction *jToRemove);

#endif



