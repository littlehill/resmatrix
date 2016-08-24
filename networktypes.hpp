#ifndef NETWORKTYPES_H
#define NETWORKTYPES_H

#include <iostream>
#include <sstream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define ulong unsigned long long int
static ulong globalID =0x0000000000000001;

enum MathAction {
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	NOP
};

class Connection {
	ulong UID;
	
	public:
	Connection();  /* cout << "connection created"; */		
	~Connection(); /* cout << "connection destroed"; */
	
	virtual double GetValue() = 0;
	virtual string GetString() = 0;  /*should return recurcsively the string representation*/
	ulong GetUID();
};

class Junction {
	private: 
	string name;
	ulong UID;
	
	public:
	Junction (string inname);
	
	ulong GetUID();
	void setName(string newone);
	string getName();
};

class Resistor: public Connection {
	private: 
	string designator;
	double value; /*value of the resistor in ohms, value<0==unknown*/
	/* tip: for negative ressitance use voltage /current ource */
	
	public:
	Resistor (string indesignator, double invalue);
	
	double GetValue();
	string GetString();
	void SetDesignator(string newone);
	void SetValue(double newValue);
};

class Constant: public Connection {
	double value;
	public:
		Constant(double invalue);
		double GetValue();
		string GetString();
};

class Expression: public Connection {
	Connection * left;
	Connection * right;
	MathAction operation;
	
	public:
		Expression(Connection * singleEnd);
		Expression(Connection * L, Connection * R, MathAction setop);
		
		double GetValue();
		string GetString();
};

class  Impedance {
	Junction *from;
	Junction *to;
	Connection *Z;
	ulong UID;
	
	public:
		Impedance (Junction * A, Junction * B, double resistance);
		Impedance (Junction * A, Junction * B, Connection *inZ);
		ulong GetUID();
		double GetValue();
		string GetString();
		Junction * getFrom();
		Junction * getTo();
};

#endif

