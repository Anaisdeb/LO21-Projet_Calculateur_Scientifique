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
