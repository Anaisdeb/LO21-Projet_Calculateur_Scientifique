#ifndef OPERATEURS_H
#define OPERATEURS_H


#include <iostream>
#include <memory>
#include "litterale.h" //Permet l'héritage de Operande
#include "operation.h"

/**
 * @brief Un objet Operateur est une opérande.
 * @details Une instance d'un objet Operateur peut représenter indifféremment un opérateur numérique, logique, de pile, de programme, etc.
 */
class Operateur : public Operande {

    /**
    * @brief Chaîne de caractères représentant l'opérateur.
    */
    std::string op;

    /**
     * @brief Arité de l'opérateur, i.e. le nombre d'opérandes sur lequel il s'applique, 1: unaire, 2: binaire.
     */
    const unsigned int arite;

     /**
     * @brief Pointeur sur objet Operation, qui représente le comportement de l'opérateur.
     */
    std::shared_ptr<Operation> operation;

public :

    /**
     * @brief Constructeur d'objet Operateur.
     * @param symbol Chaîne de caractère représentant l'opérateur.
     * @param arity Entier positif représentant le nombre d'opérandes sur lequel l'opérateur s'applique.
     * @param operation Pointeur sur Operation, définissant le comportement de l'opérateur.
     */
    Operateur(std::string operateur, const unsigned int arite, std::shared_ptr<Operation> operation) : op(operateur), arite(arite), operation(operation) { }
    /**
     * @brief Accesseur pour arite.
     * @return Entier non-signé.
     */
    const unsigned int getArite() const { return arite; }

    /**
    * @brief Accesseur pour operation.
    * @return  pointeur sur Operation.
    */
    const std::shared_ptr<Operation> getOperation() { return operation; }

    /**
     * @brief Retourn le symbole de l'opérateur.
     * @return Objet string.
     */
    std::string toString() const { return op; } // Accesseur constant pour le nom de l'opérateur

     /**
      * @brief Destructeur virtuel pur avec implémentation pour rendre la classe abstraite.
      */
    ~Operateur();
};

#endif // OPERATEURS_H
