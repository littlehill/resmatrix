#include "network.hpp"

void insertResistorMatrix(Network * matrix, unsigned int xsize, unsigned int ysize) {
	register unsigned int fx, fy;
	Impedance *ztemp;
	
	string designator, tempdes2, zname;
	Junction * TJ1;
	Junction * TJ2;
	
	for (fx=0;fx<xsize;fx+=1) {
		designator = "Sig" + std::to_string(fx);
		cout << "adding Junction: " + designator + "\n";
		matrix->addJunction(designator);	
		designator.clear();
	}
	for (fy=0;fy<ysize;fy+=1) {
		tempdes2 = "Gnd" + std::to_string(fy);
		cout << "adding Junction: " + tempdes2 + "\n";
		matrix->addJunction(tempdes2);		
		designator.clear();		
	}
	
	for (fy=0;fy<ysize;fy+=1) {
		designator = "Gnd" + std::to_string(fy);
		for (fx=0;fx<xsize;fx+=1) {
			tempdes2 = "Sig" + std::to_string(fx);			
			TJ1 = matrix->getJunction(designator);
			TJ2 = matrix->getJunction(tempdes2);
			tempdes2.clear();
			zname.clear();
			zname = "R" + std::to_string(fy*6+fx);
			
			ztemp = new Impedance(TJ1,TJ2,new Resistor(zname,3000.0));
			matrix->addImpedance(ztemp);
			
			cout << "Added impedance between junctions: " + TJ1->getName() + " & " + TJ2->getName() + " //res-designator: " + zname + "\n";
		}
		designator.clear();		
	}
}


/*Class Network*/
Network::Network(){
	
}
ulong Network::getJunctionUID(string name) {
	Junction * data = getJunction(name);
	if (data!=NULL) 
		return data->GetUID();	
	else 
		return 0;
	
}
Junction * Network::getJunction(string name) {
	Junction * data;
	for (int fa=0;fa<junctions.size();fa+=1) {
		data = junctions[fa];
		if (name.compare(data->getName())==0) return data;
	}
	
	return NULL;
}
Junction * Network::getJunction(ulong jUID) {
	Junction * data;
	for (int fa=0;fa<junctions.size();fa+=1) {
		data = junctions[fa];
		if (jUID == data->GetUID()) return data;
	}
	
	return NULL;
}
void Network::addJunction(string name) {
	junctions.push_back(new Junction(name));
}
void Network::addJunction(Junction * jnc) {
	junctions.push_back(jnc);
}
void Network::addImpedance(Impedance * inz) {
	imps.push_back(inz);	
}
std::stringstream * Network::printAllContent() {
	register int fa,fmax;
	Junction * tmpj;
	Impedance * tmpz;
	
	std::stringstream * output;
	output = new std::stringstream();
	
	
	*output	<< "---- Matrix output ----\n"
			<< "listing all Junctions: \n";
	fmax = this->junctions.size();
	for (fa=0;fa<fmax;fa+=1) {
		tmpj = this->junctions.at(fa);
		*output << ".name:" + tmpj->getName() + " \tUID:" + std::to_string(tmpj->GetUID()) + " \tcount:J" + std::to_string(fa) + "\n";	
	}
	
	
	*output	<< "---- Matrix output ----\n"
			<< "listing all Impedances: \n";
	fmax = this->imps.size();
	for (fa=0;fa<fmax;fa+=1) {
		tmpz = this->imps.at(fa);
		--; //*output << ".from:" + tmpj->getName() + " \tUID:" + std::to_string(tmpj->GetUID()) + " \tcount:J" + std::to_string(fa) + "\n";	
	}
	*/
	
	return output;
}
/*Network End*/

