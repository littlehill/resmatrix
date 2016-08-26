#include "network.hpp"

/*Class Network*/
Network::Network(){
	
}
Network::Network(Network *cloneme) {
	this->junctions	= cloneme->junctions;
	this->imps		= cloneme->imps;
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
Junction * Network::getJunction(ulong UID) {
	Junction * data;
	for (int fa=0;fa<junctions.size();fa+=1) {
		data = junctions[fa];
		if (UID == data->GetUID()) return data;
	}
	
	return NULL;
}
Impedance * Network::getImpedance(ulong UID) {
	Impedance * data;
	for (int fa=0;fa<imps.size();fa+=1) {
		data = imps[fa];
		if (UID == data->GetUID()) return data;
	}
	
	return NULL;
}

long int Network::getJposition(ulong UID) {
	Junction * data;
	for (int fa=0;fa<junctions.size();fa+=1) {
		data = junctions[fa];
		if (UID == data->GetUID()) return fa;
	}
	return -1;
}
long int Network::getIposition(ulong UID) {
	Impedance * data;
	for (int fa=0;fa<imps.size();fa+=1) {
		data = imps[fa];
		if (UID == data->GetUID()) return fa;
	}
	return -1;
}
bool Network::existsInNet(Connection *what) {
	long int status=0;
	if (what==NULL) {
		cerr << "Error: exist function called on NULL Connection *;" << endl;
		return false;
	}
	status = this->getIposition(what->GetUID());
	if (status>=0) return true;
	else return false;
}
bool Network::existsInNet(Junction *what) {
	long int status=0;
	if (what==NULL) {
		cerr << "Error: exist function called on NULL Junction *;" << endl;
		return false;
	}
	status = this->getJposition(what->GetUID());
	if (status>=0) return true;
	else return false;
}
std::vector<Impedance*> *getConnectedList(Junction *centerJ) {
	std::vector<Impedance*> *output = new std::vector<Impedance*>();
	return output;
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
		*output << ".impedance: \t" + tmpz->GetString() ; //"\n";	
	}
	
	return output;
}
bool Network::removeJunction(ulong UID) {
	long int position = this->getJposition(UID);
	if (position>=0) {
		this->junctions.erase(junctions.begin()+position);
		return true;
	}
	else {
		cerr << "Error: Attempt to remove not-existing junction;\n";
		return false;
	}
}
bool Network::removeImpedance(ulong UID) {
	long int position = this->getIposition(UID);
	if (position>=0) {
		this->imps.erase(imps.begin()+position);
		return true;
	}
	else {
		cerr << "Error: Attempt to remove not-existing impedance;\n";
		return false;
	}
}
bool Network::removeJunction(Junction *soonToBeDeadJunction) {
	if (soonToBeDeadJunction!=NULL) {
		return this->removeJunction(soonToBeDeadJunction->GetUID()) ;
	}
	else {
		cerr << "Error: attempt to remove NULL junction;" << endl;
		return false;
	}
}
bool Network::removeImpedance(Impedance *soonToBeDeadImpedance) {
	if (soonToBeDeadImpedance!=NULL) {
		return this->removeImpedance(soonToBeDeadImpedance->GetUID()) ;
	}
	else {
		cerr << "Error: attempt to remove NULL impedance;" << endl;
		return false;
	}
}
/*Network End*/

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

bool starMeshTransformation(Network *srcNet, Junction *jToRemove) {
	Network tempNet(srcNet);

	std::vector<Impedance*> star;

	if (!tempNet.existsInNet(jToRemove)) {
		cerr << "ERROR: selected junction for removal has not been found in Network." << endl;
		return false;
	}
	
	
	
	
	
}
