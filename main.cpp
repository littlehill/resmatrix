#include <iostream>

#include "networktypes.hpp"
#include "network.hpp"

int main(int argc, char** argv) {
	Network  skynet;
	string inJunctionName, outJunctionName;
	Junction *inJunction, *outJunction;
	
	insertResistorMatrix(&skynet,6,6);
	
	std::stringstream * outs = skynet.printAllContent();
	cout << outs->str();
	
	
	// IN and OUT junction selection:
	cout 	<< "\n--------------------------------- \n";
	inJunction = NULL;
	while (inJunction==NULL) {
		cout	<<   "Please enter the input junction name: ";
		cin >> inJunctionName;
		inJunction = skynet.getJunction(inJunctionName);
		if (inJunction==NULL) 
			cout << "Invalid Junction name, try again.\n";
		else
			cout << "You have selected input Junction: " + inJunctionName + " \tUID=" + std::to_string(inJunction->GetUID()) + "\n";
	}
	
	outJunction = NULL;
	while (outJunction==NULL) {
		cout	<<   "Please enter the output Junction name: ";
		cin >> outJunctionName;
		outJunction = skynet.getJunction(outJunctionName);
		if (outJunction==NULL) 
			cout << "Invalid Junction name, try again.\n";
		else if (outJunction->GetUID()==inJunction->GetUID()) {
			cout << "You have selected this Junction for input. Please choose different one.\n";
			outJunction = NULL;
			}
		else
			cout << "You have selected output Junction: " + outJunctionName + " \tUID=" + std::to_string(outJunction->GetUID()) + "\n";
	}
	
	/* TODO (#1#): Select Junction to remove, do the 
	               transformation on this junction; */
	---; //
	
	
	
	return 0;
}
