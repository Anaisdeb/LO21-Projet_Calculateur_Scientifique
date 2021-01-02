/**
    * A20 - LO21 - Projet Comp'UT
    * Ecrit par :
    * DEBUREAUX Anaïs, GRALL Thibaut, MARGERIT Paul-Edouard, MARQUIS Antoine et ZHANG Aline.
**/

#include <QApplication>
#include "qcomputer.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QComputer fenetre;
    fenetre.show();

    return app.exec();
}

/* ===================== A FAIRE =====================
    * si la taille de la littérale dépasse la taille de la pile, mettre ". . ." à la fin de la ligne
    * vérification du contenu des QLineEdit pour la modification des var/prog nécessaire ?
*/

//  methode pour commenter
/**
* @brief : (à quoi sert ma méthode) : ajouter un élement de type Evt à mon vector
* @param : (paramètres de la fonction) référence vers l'EVT à ajouter
* @return : (valeur de retour) Agenda&, une référence vers l'agenda courant (this)
*/



