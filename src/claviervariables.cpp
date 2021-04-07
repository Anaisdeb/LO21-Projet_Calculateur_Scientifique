#include "claviervariables.h"
#include "fenetrecalculatrice.h"
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox> // pour test
#include <QScrollArea>

ClavierVariables::ClavierVariables(QWidget* parent) {
    // LAYOUTS
    QVBoxLayout* mainLayout = new QVBoxLayout;
    varLayout = new QGridLayout();
    //QScrollArea* scrollArea = new QScrollArea();
    //scrollArea->setWidgetResizable(true);

    // QGROUPBOX
    QGroupBox* groupvar = new QGroupBox("Clavier 1");
    /*QPushButton* num = new QPushButton("NUM");
    connect(num, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* den = new QPushButton("DEN");
    connect(den, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* pow = new QPushButton("POW");
    connect(pow, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* sin = new QPushButton("SIN");
    connect(sin, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* cos = new QPushButton("COS");
    connect(cos, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* tan = new QPushButton("TAN");
    connect(tan, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* arcsin = new QPushButton("ARCSIN");
    connect(arcsin, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* arccos = new QPushButton("ARCCOS");
    connect(arccos, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* arctan = new QPushButton("ARCTAN");
    connect(arctan, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* sqrt = new QPushButton("SQRT");
    connect(sqrt, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* exp = new QPushButton("EXP");
    connect(exp, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* ln = new QPushButton("LN");
    connect(ln, SIGNAL(clicked()), parent, SLOT(clickOperateur())); */
    // QPUSHBUTTON
    QPushButton* egal = new QPushButton("=");
    // CONNEXION SIGNAUX/SLOTS
    connect(egal, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* notegal = new QPushButton("!=");
    connect(notegal, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* infegal = new QPushButton("<=");
    connect(infegal, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* supegal = new QPushButton(">=");
    connect(supegal, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* inf = new QPushButton("<");
    connect(inf, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* sup = new QPushButton(">");
    connect(sup, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* et = new QPushButton("AND");
    connect(et, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* ou = new QPushButton("OR");
    connect(ou, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* non = new QPushButton("NOT");
    connect(non, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* dup = new QPushButton("DUP");
    connect(dup, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* drop = new QPushButton("DROP");
    connect(drop, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* swap = new QPushButton("SWAP");
    connect(swap, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* ift = new QPushButton("IFT");
    connect(ift, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* sto = new QPushButton("STO");
    connect(sto, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    /*QPushButton* ifte = new QPushButton("IFTE");
    connect(ifte, SIGNAL(clicked()), parent, SLOT(clickOperateur())); // pas binaire
    QPushButton* tantque = new QPushButton("WHILE");
    connect(tantque, SIGNAL(clicked()), parent, SLOT(clickOperateur()));*/

    varLayout->addWidget(egal, 0, 0);
    varLayout->addWidget(notegal, 0, 1);
    varLayout->addWidget(infegal, 0, 2);
    varLayout->addWidget(supegal, 0, 3);
    varLayout->addWidget(inf, 1, 0);
    varLayout->addWidget(dup, 1, 1);
    varLayout->addWidget(drop, 1, 2);
    varLayout->addWidget(swap, 1, 3);
    varLayout->addWidget(sup, 2, 0);
    varLayout->addWidget(ift, 2, 1);
    varLayout->addWidget(et, 2, 2);
    varLayout->addWidget(ou, 2, 3);
    varLayout->addWidget(non, 3, 0);
    varLayout->addWidget(sto, 3, 1);
    /*varLayout->addWidget(num, 0, 1);
    varLayout->addWidget(den, 0, 2);
    varLayout->addWidget(pow, 0, 3);*/
    /*varLayout->addWidget(sin, 1, 1);
    varLayout->addWidget(cos, 1, 2);
    varLayout->addWidget(tan, 1, 3);*/
    /*varLayout->addWidget(arcsin, 2, 1);
    varLayout->addWidget(arccos, 2, 2);
    varLayout->addWidget(arctan, 2, 3);*/
    /*varLayout->addWidget(sqrt, 3, 1);
    varLayout->addWidget(exp, 3, 2);
    varLayout->addWidget(ln, 3, 3);*/
    /*varLayout->addWidget(ifte, 5, 2);
    varLayout->addWidget(tantque, 5, 3);*/

    groupvar->setLayout(varLayout);
    //scrollArea->setWidget(groupvar);
    mainLayout->addWidget(groupvar);
    this->setLayout(mainLayout);
}

void ClavierVariables::minimize1(int state) {
    if (state) {
        // ETAT DU CLAVIER VISIBLE
        this->setVisible(false); // on masque le clavier
    } else {
        // ETAT DU CLAVIER MASQUE
        this->setVisible(true); // on rend le clavier visible
    }
}

void ClavierVariables::ajoutBouton(const QString& nom) {
    // QPUSHBUTTON
    QPushButton* boutonVar = new QPushButton(nom);
    varLayout->addWidget(boutonVar, static_cast<int>(*ver), *hor); // ajout du bouton dans le layout
    (*hor)++; // on incrémente *ver et *hor pour le prochain boutton
    if (*hor%4 == 0) {
        // SI LE BOUTON EST SUR LA 5E COLONNE
        *hor = 0; // on prépare le prochain bouton sur la 1e colonne
        (*ver)++; // on prépare le boutton sur la prochaine ligne
    }
    connect(boutonVar, SIGNAL(clicked()), FenetreCalculatrice::donneInstance(), SLOT(clickOperateur()));
}
