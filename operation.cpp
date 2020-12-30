#include "operation.h"
#include "operateursmanager.h"
#include "manager.h"
#include "projetexception.h"
#include "litterale.h"
#include "controleur.h"

#include <iostream>
#include <memory>



/*-----------------Opérateurs numériques-----------------*/

Operation::Operandes PlusOperation::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1) + (*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
      }
 }

 Operation::Operandes NegOperation::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     if (op1 != nullptr) {
         op1->neg();
         return {op1};
     }
     else {
         throw ProjetException("Type invalide pour l'operation demandÈe");
     }
 }

 Operation::Operandes MulOperation::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1) * (*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes MoinsOperation::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1) - (*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes DivOperation::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1) / (*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes EntDivOperation::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittEntiere>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittEntiere>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1) / (*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes ModOperation::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittEntiere>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittEntiere>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1).mod(*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 /*-----------------OpÈrateurs Logiques-----------------*/

 Operation::Operandes EgalOperation::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1) == (*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes NonEgalOperation::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1) != (*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes InfOuEgal::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1) <= (*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes SupOuEgal::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1) >= (*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes Inferieur::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1) < (*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes Superieur::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1) > (*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes EtLogique::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1).AND(*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes OuLogique::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     auto op2 = std::dynamic_pointer_cast<LittNumerique>(dn.back());
     if (op1 != nullptr && op2 != nullptr) {
         return { (*op1).OR(*op2) };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

 Operation::Operandes NonLogique::eval(Operation::Operandes dn) const {
     auto op1 = std::dynamic_pointer_cast<LittNumerique>(dn.front());
     if (op1 != nullptr) {
         return { (*op1).NOT() };
     }
     else {
         throw ProjetException("Type invalide pour l'opÈration demandÈe");
     }
 }

/*-----------------OpÈrateurs programmes-----------------*/

 Operation::Operandes StoOperation::eval(Operation::Operandes dn) const {
 auto op1 = std::dynamic_pointer_cast<LittExpression>(dn.front());
 auto op2 = std::dynamic_pointer_cast<Litterale>(dn.back());
 if (op1 != nullptr && op2 != nullptr) {
     op1->sto(op2);
     return { nullptr };
 }
 else {
     throw ProjetException("Type invalide pour l'opÈration demandÈe");
 }
}

 Operation::Operandes ForgetOperation::eval(Operation::Operandes dn) const {
 auto op1 = std::dynamic_pointer_cast<LittExpression>(dn.front());
 if (op1 != nullptr) {
     op1->forget();
     return { nullptr };
 }
 else {
     throw ProjetException("Type invalide pour l'opÈration demandÈe");
 }
}

/*-----------------OpÈrateurs de Manipulation de la pile-----------------*/

 Operation::Operandes DupOperation::eval(Operation::Operandes dn) const {
 //le dernier ÈlÈment empilÈ est dÈpilÈ, on empile deux fois cette ÈlÈment donc on retourne deux fois la donnÈe.
 return { dn.front(), dn.front() };
}

 Operation::Operandes DropOperation::eval(Operation::Operandes) const {
 //le dernier ÈlÈment empilÈ est dÈpilÈ, rien n'est empilÈ ? nouveau donc rien est retournÈ.
 std::shared_ptr<Operande> res = nullptr;
 return { res };
}

 Operation::Operandes SwapOperation::eval(Operation::Operandes dn) const {
 //les deux derniers ÈlÈments empilÈs sont dÈpilÈs, on les empile dans l'ordre inverse.
 return { dn.back(), dn.front() };
}

 Operation::Operandes ClearOperation::eval(Operation::Operandes) const {
 std::shared_ptr<Operande> res = nullptr;
 Controleur::donneInstance().pile.clear(); //OpÈration de Manager
 return { res };
}

/*-----------------OpÈrateur LitÈralles expressions-----------------*/ //Fonction d'Antoine dans Manager : return {Manager::eval()};

 Operation::Operandes Eval::eval(Operation::Operandes dn) const {
 auto op1 = std::dynamic_pointer_cast<Litterale>(dn.front());
 if (op1!=nullptr){
    op1->eval();
 }
 else {
     throw ProjetException("L'expression ne peut pas Ítre ÈvaluÈe");
 }
 return { nullptr };
}

/*-----------------OpÈrateurs Conditionnels et de Boucle-----------------*/

 Operation::Operandes IFT::eval(Operation::Operandes dn) const {
 auto prog = std::dynamic_pointer_cast<Litterale>(dn.back());
 auto test = std::dynamic_pointer_cast<LittEntiere>(dn.front());
 if (test != nullptr && prog !=nullptr) {
     if (test->getParam() != 0) prog->eval(); //Premier argument = true, on provoque l'Èvaluation du deuxiËme
     return { nullptr };
 }
 throw ProjetException("Le premier argument ne peut pas Ítre interprÈtÈ comme un boolÈen entier");
}
