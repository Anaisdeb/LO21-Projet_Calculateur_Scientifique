#include "projetexception.h"
#include "controleur.h"
#include "operateursmanager.h"
#include "operation.h"
#include "operateurs.h"
#include "manager.h"
#include "litterale.h"
#include "fabriquelitterale.h"
#include <iostream>
#include <string>
#include <vector>

Controleur* Controleur::instanceUnique = nullptr;
Controleur& Controleur::donneInstance() {
    if (instanceUnique == nullptr)
        instanceUnique = new Controleur;
     // static Controleur instance; //Libérée automatiquement
     return *instanceUnique;
}
void Controleur::libereInstance(){
    delete instanceUnique;
    instanceUnique = nullptr;
}
Controleur::~Controleur(){}//delete pile1;}

void Controleur::exec(std::string s) {
    std::vector<std::string> res = tdParse(s);
    for (std::string t : res) {
        if (t[0] == '[') {
            //Appeler la fabrique puis empiler
            pile.push(FabriqueLitterale::donneInstance().makeLitteraleProgramme(t));
        }
        else if (OperateursManager::getInstance().isOperateur(t)) {
            std::shared_ptr<Operateur> op = OperateursManager::getInstance().getOperateur(t); // recherche de l'opérateur (op)
            int arite = op->getArite(); // recherche de son arité
            // dépile (pop)
            if (pile.taille() < arite) throw ProjetException("Pas assez de littérales.");
            Donnees<std::shared_ptr<Operande>> params;
            for (int i = 0; i < arite; i++) {
                std::shared_ptr<Operande> temp = pile.pop();
                //pile.pop();
                params.push_back(temp);
            }
            std::reverse(params.begin(), params.end()); // on remet les paramèetres dans le bon ordre
            std::shared_ptr<Operation> oper = op->getOperation();
            Donnees<std::shared_ptr<Operande>> res = oper->eval(params);
            // std::shared_ptr<Operande> res = op->getOperation()->eval(params); // eval d'operateur
            if (res[0] != nullptr) {
                //push dans la pile
                for(int i = 0; i< res.size(); i++){
                pile.push(res[i]);
                }
            }
        }
        else if (isExpression(t)) {
            //Appeler la fabrique puis empiler
            pile.push(FabriqueLitterale::donneInstance().makeLitteraleExpression(t));
        }
        else if (isEntier(t)) {
            //Appeler la fabrique puis empiler
            pile.push(FabriqueLitterale::donneInstance().makeLitterale(std::stoi(t)));
        }
        else if (isReel(t)) {
            //Appeler la fabrique " creer le progamme" puis empiler
            pile.push(FabriqueLitterale::donneInstance().makeLitterale(std::stod(t)));
        }
        else if (isRationnel(t)) {
            //Appeler la fabrique " creer le progamme" puis empiler
            int i = t.find('/');
            pile.push(FabriqueLitterale::donneInstance().makeLitterale(std::stoi(t), std::stoi(t.substr(i+1, t.length()-i-1))));
        }
        else if (Manager::getInstance().isAtome(t)) {
            std::shared_ptr<Litterale> atome = Manager::getInstance().GetAtome(t);
            atome->eval();
        }
        else throw(ProjetException("Operande invalide"));
     }

}

/*
void Controleur::executer() {
    std::string s;
    std::cout << "Veuillez saisir une valeur ou q pour arreter: ";
    std::cin.clear();
    std::cout<< "coucou"<<"\n";
    std::getline(std::cin, s);
    std::cout<< "coucou"<<"\n";
    while (s != "q") {
        // Traitement de la ligne de commande
        try {
            exec(s);
            // pileAff.affiche();
        }
        catch (ProjetException& e) {
            std::cout << e.what() << std::endl;
        }
        // On redemande une ligne
        std::cout << "Veuillez saisir une valeur ou q pour arreter: ";
        std::cin.clear();
        std::getline(std::cin, s);
    }
}
*/

bool isExpression(std::string s){
    if (!isLettreMaj(s[1])) return false;
    if (s[0] != '\'' || s[s.length() - 1]!='\'') return false;
    for (int i = 1; i < s.length()-1; i++) {
        if (!isLettreMaj(s[i]) && !isChiffre(s[i])) return false;
    }
    return true;
}

bool isEntier(std::string s) {
    for (unsigned int i = 0; i < s.length(); i++) {
        if (!isChiffre(s[i])) return false;
    }
    return true;
}

bool isReel(std::string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i]=='.') {
        bool res = isEntier(s.substr(0,i)) && isEntier(s.substr(i+1, s.length()-i-1));
        return (res);
    }
    }
    return false;
}

bool isRationnel(std::string s) {
    for(int i = 0; i< s.length(); i++){
        if(s[i] =='/'){
            bool res = isEntier(s.substr(0, i)) && isEntier(s.substr(i + 1, s.length() - i - 1));
            return (res);
        }
    }
    return false;
}

// ----------------
// Partie de la pile
// ----------------



void Pile::push(std::shared_ptr<Operande> op) {
    contenu.push_back(op);
}

std::shared_ptr<Operande> Pile::pop() {
    if (contenu.size() == 0) {
        throw ProjetException("Plus de litterale dans la Pile");
    }
    std::shared_ptr<Operande> op = contenu[contenu.size()-1];
    contenu.pop_back();
    return op;
}

std::shared_ptr<Operande> Pile::top() const {
    if (contenu.size() == 0) {
        throw ProjetException("Pas d'Item dans la Pile");
    }
    std::shared_ptr<Operande> op = contenu[contenu.size()-1];
    return op;
}

void Pile::affiche() const {
    std::cout << "Voici l'etat de la Pile : \n";
    for (std::vector<std::shared_ptr<Operande>>::const_iterator it = contenu.begin(); it !=contenu.end(); it++) {
        std::shared_ptr<Operande> temp = (*it);
        auto temp2 = std::dynamic_pointer_cast<Litterale>(temp);
        std::cout<< temp2->toString()<<std::endl;
    }
    std::cout << std::endl;
}

bool Pile::estVide() const {
    return contenu.size() == 0 ? true : false;
}

size_t Pile::taille() const {
    return contenu.size();
}

void Pile::setMessage(const QString& m) {
    message = m;
}

QString Pile::getMessage() const {
    return message;
}


void Pile::setNbItemsToAffiche(size_t n) {
    nbAffiche = n;
}

void Pile::clear(){
    contenu.clear();
}
