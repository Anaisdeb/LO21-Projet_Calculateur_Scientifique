#if !defined(_OPERATEURS_H)
#define _OPERATEURS_H

using namespace std;

class Operateur : public Operande {
	string op; // Nom de l'opérateur
	const unsigned int arite; // 1: unaire, 2: binaire

public :
	Operateur(string operateur, const unsigned int arite) : op(operateur), arite(arite) { } // Constructeur
	const unsigned int getArite() const { return arite; } // Accesseur constant pour l'arité
	string toString() const { return op; } // Accesseur constant pour le nom de l'opérateur
	~Operateur() = 0; //Destructeur virtuel pur pour rendre la classe abstraite.
}

class OpLogique : public Operateur {

};

class OpManipulation : public Operateur {

};

class OpConditionnel : public Operateur {

};