#ifndef OPERATEURSMANAGER_H
#define OPERATEURSMANAGER_H


#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <iostream>

#include "operation.h"

class Operande; //Litteral.h
class Operateur; //Operateurs.h
class Litterale; //Litteral.h
class LittExpression;
template <typename T>
class Donnees; //Donnees.h

/**
  \brief Singleton chargé du management des opérateurs (déclaration, accès) et l'attribution des opérations.
  \details L'objet OperateurManager contient des objets Operateur.
 */

class OperateursManager {

    /**
     * @brief Constructeur privé
     */
    OperateursManager();

    /**
     * @brief brief Conteneur d'instance de pointeurs sur Operateur.
     */
    std::vector<std::shared_ptr<Operateur>> operateurs;

    /**
     * @brief Pointeur sur l'opérateur utilisé pour l'évalution des programmes (que l'on doit rajouter manuellement pour un atome sur un programme).
     */
    std::shared_ptr<Operateur> evalOperateur;

public:
    /**
     * @brief OperatorManager est un Singleton : on supprime le constructeur de recopie.
     */
    OperateursManager(const OperateursManager&) = delete;

    /**
     * @brief OperatorManager est un Singleton : on supprime l'opérateur d'affectation.
     */
    void operator=(const OperateursManager&) = delete;

    /**
      * @brief Renvoie l'instance du singleton OperateurnManager
      * @return Référence constante de l'instance du singleton.
      */
    static const OperateursManager& getInstance();

    /**
     * @brief Renvoie l'instance d'un opérateur à partir de son symbole, s'il existe.
     * @param symbole Symbole de l'objet Operateur à renvoyer.
     * @exception argument_inexistant si le symbole demandé n'est attribué à aucun opérateur.
     * @return Référence constante sur un shared_ptr sur Operateur.
     */
    const std::shared_ptr<Operateur> getOperateur(std::string symbole) const;

    /**
     * @brief Renvoie si une expression est un opérateur ou non.
     * @param symbole Identificateur à tester.
     * @return Booléen.
     */
    bool isOperateur(const std::string& symbole) const;

};

#endif // OPERATEURSMANAGER_H
