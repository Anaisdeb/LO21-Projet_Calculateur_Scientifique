#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <vector>
#include <iostream>
#include <memory>
#include<QString>
#include "litterale.h"

class Manager{
    /**
     * @brief Map de chaine de caratères et de litteral représenrant les identifieurs.
     */
    std::map<std::string, std::shared_ptr<Litterale>> atomeManager;
    /**
     * @brief La classe étant un singleton, on passe le constructeur en privé
     */
    Manager()=default;
public:
    /**
     * @brief Suppression du constructeur de recopie et de l'opérateur d'affectation
     */
    Manager(const Manager&) = delete;
    void operator= (const Manager&) = delete;
    /**
     * @brief Récupération de la référence du singleton
     * @return Référence vers le singleton Manager
     */
    static Manager& getInstance();
    /**
     * @brief Ajout d'un atome à l'atome manager
     * @param nom Nom de l'atome sous forme d'une littérale expression
     * @param atome L'atome en lui même
     */
    void AddAtome(std::shared_ptr<LittExpression> nom, std::shared_ptr<Litterale> atome);
    /**
     * @brief Oublie d'un atome (suppression de celui-ci dans l'atome manager)
     * @param atome nom de l'atome à supprimer
     */
    void ForgetAtome(std::string atome);
    /**
     * @brief Récupère un atome grâce à son nom sous forme d'une littérale expression
     * @param atome Nom de l'atome à récupérer
     * @return L'atome en lui même
     */
    std::shared_ptr<Litterale> GetAtome(std::shared_ptr<LittExpression> atome);
    /**
     * @brief Même fonction mais avec en identifiant l'atome par une chaîne de charactères
     * @param atome Nom de l'atome à récupérer
     * @return L'atome en lui même
     */
    std::shared_ptr<Litterale> GetAtome(std::string atome);


    bool isAtome(std::string atome);

};

bool progExiste(QString nomProg);

#endif //Manager_H
