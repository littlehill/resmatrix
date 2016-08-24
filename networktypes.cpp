#include "networktypes.hpp"


/*Connection Class*/
Connection::Connection() : UID(globalID++) {};  /* cout << "connection created"; */		
Connection::~Connection() {}; /* cout << "connection destroed"; */
ulong Connection::GetUID() {
	return UID;
}
/*Connection End*/

/*Junction Class*/
Junction::Junction (string inname) : UID(globalID++) {
	name = inname;
}
ulong Junction::GetUID() {
	return UID;
}
void Junction::setName(string newone) {
	name = newone;
}
string Junction::getName() {
	return name;
}
/*Junction End*/

/*Resistor Class*/
Resistor::Resistor (string indesignator, double invalue) {
	SetDesignator(indesignator);
	SetValue(invalue);
}
double Resistor::GetValue() {
	return value;
}
string Resistor::GetString() {
	return designator;
}
void Resistor::SetDesignator(string newone) {
	designator = newone;
}
void Resistor::SetValue(double newValue) {
	value = newValue;
}
/*Resistor End*/

/*Constant Class*/
Constant::Constant(double invalue){
	value = invalue;
}
double Constant::GetValue() {
	return value;
}	
string Constant::GetString(){
	std::ostringstream out;
	out << value;
	return out.str();
} 		
/*Constant End*/

/*Expression Class*/
Expression::Expression(Connection * singleEnd) {
	operation = NOP;
	left = singleEnd;
	right = NULL;
}	
Expression::Expression(Connection * L, Connection * R, MathAction setop) {
	left = L;
	right = R;
	operation = setop;
}
double Expression::GetValue() {
	switch (operation) {
		case PLUS:
			return ( left->GetValue() + right->GetValue() );
		case MINUS:
			return ( left->GetValue() - right->GetValue() );
		case MULTIPLY:
			return ( left->GetValue() * right->GetValue() );
		case DIVIDE:
			return ( left->GetValue() / right->GetValue() );
		case NOP:
			return left->GetValue();
		default:
			std::ostringstream sout;
			sout << this->GetUID();
			cout << "ERROR, operation was not set for item UID=" + sout.str() + " m returning zero;\n";
			return 0;					
	}
};
string Expression::GetString() {
	switch (operation) {
		case PLUS:
			return "(" + left->GetString() + "+" + right->GetString() + ")";
		case MINUS:
			return "(" + left->GetString() + "-" + right->GetString() + ")";
		case MULTIPLY:
			return "(" + left->GetString() + "*" + right->GetString() + ")";
		case DIVIDE:
			return "(" + left->GetString() + "/" + right->GetString() + ")";
		case NOP:
			return  "(" + left->GetString() + ")";
		default:
			return "(ERROR:unidentifiedOP)";					
	}
}
/*Expression End*/


/* TODO (#1#): Create expression link to store complex resistor 
               values. UID missing */
/*Impedance Class*/               
Impedance::Impedance (Junction * A, Junction * B, double resistance): UID(globalID++) {
	from = A;
	to = B;		
		
	std::ostringstream resdesignator;
	resdesignator << this->GetUID();
	Z = new Resistor("NZX"+resdesignator.str(),resistance);
}
Impedance::Impedance (Junction * A, Junction * B, Connection *inZ): UID(globalID++) {
	from = A;
	to = B;
	Z = inZ;
}
ulong Impedance::GetUID() {
	return UID;
}
Junction * Impedance::getFrom() {
	return this->from;
}
Junction * Impedance::getTo() {
	return this->to;
}
double Impedance::GetValue() {
	return Z->GetValue();
}	
string Impedance::GetString(){
	/* TODO (#1#): full string output */
	std::ostringstream printImpedance;
	printImpedance << "from:" + from->getName() + " to:" + to->getName() + " impedance is: " + Z->GetString() + " \n";
	return printImpedance.str();
} 
/*Impedance End*/
