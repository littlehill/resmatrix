#include <iostream>

#include "networktypes.hpp"
#include "network.hpp"

int main(int argc, char** argv) {
	Network  skynet;
	
	insertResistorMatrix(&skynet,6,6);
	
	std::stringstream * outs = skynet.printAllContent();
	cout << outs->str();
	
	return 0;
}
