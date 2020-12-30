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
    /*operateurs.push_back(std::make_shared<Operateur>("POW", 2, std::make_shared<PowOperation>)); //Puissance
    operateurs.push_back(std::make_shared<Operateur>("SIN", 1, std::make_shared<SinOperation>)); //Sinus
    operateurs.push_back(std::make_shared<Operateur>("COS", 1, std::make_shared<CosOperation>)); //Cosinus
    operateurs.push_back(std::make_shared<Operateur>("TAN", 1, std::make_shared<TanOperation>)); //Tangeante
    operateurs.push_back(std::make_shared<Operateur>("ARCSIN", 1, std::make_shared<ArcSinOperation>())); //Inverse sinus
    operateurs.push_back(std::make_shared<Operateur>("ARCCOS", 1, std::make_shared<ArcCosOperation>())); //Inverse cosinus
    operateurs.push_back(std::make_shared<Operateur>("ARCTAN", 1, std::make_shared<ArcTanOperation>())); //Inverse tangeante
    operateurs.push_back(std::make_shared<Operateur>("SQRT", 1, std::make_shared<SqrtOperation>())); //Racine carrée
    operateurs.push_back(std::make_shared<Operateur>("EXP", 1, std::make_shared<ExpOperation>())); //Exponentielle
    operateurs.push_back(std::make_shared<Operateur>("LN", 1, std::make_shared<LnOperation>())); //Logarithme naturel
    operateurs.push_back(std::make_shared<Operateur>("NUM", 1, std::make_shared<NumOperation>())); //Numérateur
    operateurs.push_back(std::make_shared<Operateur>("DEN", 1, std::make_shared<DenOperation>())); //Dénominateur*/

    operateurs.push_back(std::make_shared<Operateur>("AND", 2, std::make_shared<EtLogique>())); //ET Logique
    operateurs.push_back(std::make_shared<Operateur>("OR", 2, std::make_shared<OuLogique>())); //OU Logique
    operateurs.push_back(std::make_shared<Operateur>("NOT", 1, std::make_shared<NonLogique>())); //NON Logique

    evalOperateur = std::make_shared<Operateur>("EVAL", 1, std::make_shared<Eval>()); //Evaluation de littérale
    operateurs.push_back(evalOperateur);
    operateurs.push_back(std::make_shared<Operateur>("IFT", 2, std::make_shared<IFT>())); //Condition binaire
    /*operateurs.push_back(std::make_shared<Operateur>("IFTE", 3, std::make_shared<IFTE>())); //Condition ternaire
    operateurs.push_back(std::make_shared<Operateur>("WHILE", 2, std::make_shared<WHILE>())); //Boucle conditionnelle*/

    //Création des opérateurs d'identifieurs
    operateurs.push_back(std::make_shared<Operateur>("STO", 2, std::make_shared<StoOperation>())); //Enregistrement d'identificateur
    operateurs.push_back(std::make_shared<Operateur>("FORGET", 1, std::make_shared<ForgetOperation>())); //Suppression d'identificateur

    //Création des opérateurs de manipulation de la pile
    operateurs.push_back(std::make_shared<Operateur>("DUP", 1, std::make_shared<DupOperation>())); //Empile une nouvelle littérale identique à celle du sommet de la pile.
    operateurs.push_back(std::make_shared<Operateur>("DROP", 1, std::make_shared<DropOperation>())); //Dépile la littérale au sommet de la pile.
    operateurs.push_back(std::make_shared<Operateur>("SWAP", 2, std::make_shared<SwapOperation>())); //Intervertit les deux derniers éléments empilés dans la pile.
    /*operateurs.push_back(std::make_shared<Operateur>("UNDO", 0, std::make_shared<UndoOperation>())); //Rétablit l’état du calculateur avant la dernière opération
    operateurs.push_back(std::make_shared<Operateur>("REDO", 0, std::make_shared<RedoOperation>())); //Rétablit l’état du calculateur avant l’application de la dernière opération UNDO.*/
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
