#include "manager.h"
#include "litterale.h"
#include "operateursmanager.h"
#include "controleur.h"
#include "projetexception.h"
#include "fenetrecalculatrice.h"
#include "fenetreprogrammes.h"
#include "fenetrevariables.h"
//#include "claviervariables.h"
#include <string>
#include <iostream>
#include <memory>
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>
#include <QPushButton>


Manager& Manager::getInstance() {
    static Manager instance;
    return instance;
}

std::shared_ptr<Litterale> Manager::GetAtome(std::shared_ptr<LittExpression> atome){
    try {
        return atomeManager.at(atome->getParam());
    } catch(ProjetException& e) {
        throw("Atome introuvable");
    }
}

std::shared_ptr<Litterale> Manager::GetAtome(std::string atome){
    try {
        return atomeManager.at(atome);
    } catch(ProjetException& e) {
        throw("Atome introuvable");
    }
}

void Manager::AddAtome(std::shared_ptr<LittExpression> nom, std::shared_ptr<Litterale> atome){
    //3 4 + 'X1' [ 4 5 * ] STO X1

    if (!isAtome(nom->getParam()) && !OperateursManager::getInstance().isOperateur(nom->getParam()))
    {

        //Ajout à la base de données
        QSqlQuery query;
        if (auto op1 = std::dynamic_pointer_cast<LittNumerique>(atome) == nullptr)
        {

            atomeManager.insert(std::pair<std::string,std::shared_ptr<Litterale>>(nom->getParam(),atome));

            // Ajout d'un programme
            FenetreCalculatrice::donneInstance()->majException("Le programme "+ nom->getParam() +" a bien été stocké.");
            if(!query.exec("insert into programmes values(NULL, '"+QString::fromStdString(nom->getParam())+"', '"+QString::fromStdString(atome->toString())+"')"))
                qWarning() << "Manager::AddAtome - ERREUR insertion programme : " << query.lastError().text();
            FenetreProgrammes::donneInstance()->updateTab();
            FenetreCalculatrice::donneInstance()->ajoutBouton(QString::fromStdString(nom->getParam()));
        }
        else
        {
            atomeManager.insert(std::pair<std::string,std::shared_ptr<Litterale>>(nom->getParam(),atome));

            // Ajout d'une variable
            FenetreCalculatrice::donneInstance()->majException("La variable "+ nom->getParam() +" a bien été stockée");
            if(!query.exec("insert into variables values(NULL, '"+QString::fromStdString(nom->getParam())+"', '"+QString::fromStdString(atome->toString())+"')"))
                qWarning() << "Manager::AddAtome - ERREUR insertion variables : " << query.lastError().text();
            FenetreVariables::donneInstance()->updateTab();
            FenetreCalculatrice::donneInstance()->ajoutBouton(QString::fromStdString(nom->getParam()));
        }
    }
}

void Manager::ForgetAtome(std::string atome){

    if (isAtome(atome))
    {
        atomeManager.erase(atome);

        QSqlQuery query;

        // SUPPRESSION D'UNE VARIABLE
        QString s = QString::fromStdString(atome);

        if(!query.exec("delete from programmes where nom = '" + s + "'"))
            qWarning() << "Manager::ForgetAtome - ERREUR : " << query.lastError().text();

        if(!query.exec("delete from variables where nom = '" + s + "'"))
            qWarning() << "Manager::ForgetAtome - ERREUR : " << query.lastError().text();
        // SUPPRESSION D'UN PROGRAMME
        FenetreVariables::donneInstance()->updateTab();
        FenetreProgrammes::donneInstance()->updateTab();
    }
};

bool Manager::isAtome(std::string atome){
    for (std::map<std::string,std::shared_ptr<Litterale>>::iterator it=atomeManager.begin(); it!=atomeManager.end(); it++){
        if (it->first == atome) return true;
    }
    return false ;
};


