#include "operateursmanager.h"
#include "litterale.h"
#include "operateurs.h"
#include "operation.h"

#include "projetexception.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <memory>

/**
 * @details Ce constructeur privé crée une seule fois les instances d'Operateur correspondant
 * aux opérateurs manipulables par l'application et leur associe une instance d'Operation pour définir leur comportement.
 */
OperateursManager::OperateursManager(){

    //Création des opérateurs
    operateurs.push_back(std::make_shared<Operateur>("+", 2, std::make_shared<PlusOperation>())); //Addition
    operateurs.push_back(std::make_shared<Operateur>("-", 2, std::make_shared<MoinsOperation>())); //Soustraction
    operateurs.push_back(std::make_shared<Operateur>("*", 2, std::make_shared<MulOperation>())); //Multiplication
    operateurs.push_back(std::make_shared<Operateur>("/", 2, std::make_shared<DivOperation>())); //Division
    operateurs.push_back(std::make_shared<Operateur>("=", 2, std::make_shared<EgalOperation>())); //Egalité
    operateurs.push_back(std::make_shared<Operateur>("!=", 2, std::make_shared<NonEgalOperation>())); //Non-égalité
    operateurs.push_back(std::make_shared<Operateur>("<=", 2, std::make_shared<InfOuEgal>())); //Inférieur ou égal
    operateurs.push_back(std::make_shared<Operateur>(">=", 2, std::make_shared<SupOuEgal>())); //Supérieur ou égal
    operateurs.push_back(std::make_shared<Operateur>("<", 2, std::make_shared<Inferieur>())); //Inférieur strict
    operateurs.push_back(std::make_shared<Operateur>(">", 2, std::make_shared<Superieur>())); //Supérieur strict
    operateurs.push_back(std::make_shared<Operateur>("NEG", 1, std::make_shared<NegOperation>())); //Négation
    operateurs.push_back(std::make_shared<Operateur>("DIV", 2, std::make_shared<EntDivOperation>())); //Division entière
    operateurs.push_back(std::make_shared<Operateur>("MOD", 2, std::make_shared<ModOperation>())); //Modulo

    operateurs.push_back(std::make_shared<Operateur>("AND", 2, std::make_shared<EtLogique>())); //ET Logique
    operateurs.push_back(std::make_shared<Operateur>("OR", 2, std::make_shared<OuLogique>())); //OU Logique
    operateurs.push_back(std::make_shared<Operateur>("NOT", 1, std::make_shared<NonLogique>())); //NON Logique

    operateurs.push_back(std::make_shared<Operateur>("EVAL", 1, std::make_shared<Eval>())); //Evaluation de littérale);
    operateurs.push_back(std::make_shared<Operateur>("IFT", 2, std::make_shared<IFT>())); //Condition binaire

    //Création des opérateurs d'identifieurs
    operateurs.push_back(std::make_shared<Operateur>("STO", 2, std::make_shared<StoOperation>())); //Enregistrement d'identificateur
    operateurs.push_back(std::make_shared<Operateur>("FORGET", 1, std::make_shared<ForgetOperation>())); //Suppression d'identificateur

    //Création des opérateurs de manipulation de la pile
    operateurs.push_back(std::make_shared<Operateur>("DUP", 1, std::make_shared<DupOperation>())); //Empile une nouvelle littérale identique à celle du sommet de la pile.
    operateurs.push_back(std::make_shared<Operateur>("DROP", 1, std::make_shared<DropOperation>())); //Dépile la littérale au sommet de la pile.
    operateurs.push_back(std::make_shared<Operateur>("SWAP", 2, std::make_shared<SwapOperation>())); //Intervertit les deux derniers éléments empilés dans la pile.
    operateurs.push_back(std::make_shared<Operateur>("CLEAR", 0, std::make_shared<ClearOperation>())); //Vide tous les éléments de la pile.

}

const OperateursManager& OperateursManager::getInstance() {
    static OperateursManager instance;
    return instance;
}

const std::shared_ptr<Operateur> OperateursManager::getOperateur(std::string opcode) const {
    //Recherche d'un opérateur défini dont le symbole est le même que la chaîne passée en argument.
    for (std::vector<std::shared_ptr<Operateur>>::const_iterator it = operateurs.begin(); it != operateurs.end(); it++) {
        if ((*it)->toString() == opcode) return *it;
    }
    throw ProjetException("Opérateur introuvable.");
}

bool OperateursManager::isOperateur(const std::string& opcode) const {
    try {
        getOperateur(opcode);
        return true;
    }
    catch (ProjetException e) {
        return false;
    }
}
