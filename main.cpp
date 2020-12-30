/**
    * A20 - LO21 - Projet Comp'UT
    * Ecrit par :
    * DEBUREAUX Anaïs, GRALL Thibaut, MARGERIT Paul-Edouard, MARQUIS Antoine et ZHANG Aline.
**/

#include <QApplication>
#include <QSqlDatabase>
#include <QDir>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include "fenetrecalculatrice.h"
#include "qcomputer.h"

// CONNEXION A LA BASE DE DONNEES QUI GERE LES VARIABLES, MINI-PROGRAMMES ET PARAMETRES
void dataBaseConnect()
{
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {

        QDir dbPath;
        QString path = dbPath.currentPath()+"/bdd_comput.db";
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
        db.setDatabaseName(path);

        if(!db.open())
                qWarning() << "FenetreVariables::dataBaseConnect - ERROR: " << db.lastError().text();
    }
    else
        qWarning() << "FenetreVariables::dataBaseConnect - ERROR: no driver " << DRIVER << " available";
}



// FONCTION MAIN
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    dataBaseConnect();

    QComputer fenetre;
    fenetre.show();

    return app.exec();
}

/*
 *singelton fenetre parametres
 */

/* ===================== A FAIRE =====================

    * METTRE A JOUR LA PILE QUAND ON CHANGE LES PARAMS
        -- >idée : faire des classes fenetre des singletons --> où faut-il écrire libereInstance

    * DECONNEXION DE LA BDD

    * RENDRE LE CODE CLAIR DANS LA CLASSE FENETRECALCULATRICE (SUR LE MEME MODELE QUE FENETREVARIABLES)

    * AJOUTER DE LA COULEUR DANS LES CHOIX DES PARAMETRES

    * VERIFIER QUE L'ON AJOUTE SOIT QUE DES entiers/fractions/réels,
    * SOIT QUE DES MAJUSCULES DANS LES VARIABLES
        --> idée : transformer un QLineEdit en QDoubleSpinBox au moment de rentrer la valeur

    * VERIFIER QUE LES MINI-PROG COMMENCENT PAR [ et finissent par ] quand on les modifie
        --> idée : transformer un QLineEdit en QDoubleSpinBox au moment de rentrer la valeur

    * si la taille de la littérale dépasse la taille de la pile, mettre ". . ." à la fin de la ligne
    *
    *
    *
* Problèmes rencontrés :
 *
 * connexion à la base de données (où mettre la fonction de connexion, où fermer la base de données)
 * design pattern singleton pour les fenêtres : 1ère implémentation car il faut un pointeur
 *  -> où faut-il libérer l'instance ?
 * faut-il mettre des destructeurs pour les différentes fenêtres (lu que pas forcément besoin)
 *  -> si oui, dans quels cas ?
 * vérification du contenu des QLineEdit pour la modification des var/prog nécessaire ?
 * faut-il mettre un singleton dans la fenetre parametres ou alors les attributs static suffisent ?
 * possible de surcharger un slot ? cf majPile dans fenetreparametres.Cpp
 * faut-il commenter chaque méthode ?
 * quels widgets mettre en attributs de classe
 *
*

*
 *
-	Remplacer pile par Controleur::donneInstance().pile
-	Remplacer notre controleur par le leur
-	Faire fonction qui rentre toutes les variables de la bdd via AddAtome
 *



*/

//  methode pour commenter
/**
* @brief : (à quoi sert ma méthode) : ajouter un élement de type Evt à mon vector
* @param : (paramètres de la fonction) référence vers l'EVT à ajouter
* @return : (valeur de retour) Agenda&, une référence vers l'agenda courant (this)
*/



