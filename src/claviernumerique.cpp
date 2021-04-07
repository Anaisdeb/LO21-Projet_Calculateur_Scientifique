#include "claviernumerique.h"
#include "fenetrecalculatrice.h"
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox> // pr test

// =============== CONSTRUCTEUR ===============

ClavierNumerique::ClavierNumerique(QWidget* parent) : QWidget(parent) {
    // LAYOUT
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QGridLayout* numLayout = new QGridLayout();

    // QGROUPBOX
    QGroupBox* groupnum = new QGroupBox("Clavier 2");
    // QPUSHBUTTON
    QPushButton* b1 = new QPushButton("1");
    // CONNEXION SIGNAUX/SLOTS
    connect(b1, SIGNAL(clicked()), parent, SLOT(clickChiffre()));
    QPushButton* b2 = new QPushButton("2");
    connect(b2, SIGNAL(clicked()), parent, SLOT(clickChiffre()));
    QPushButton* b3 = new QPushButton("3");
    connect(b3, SIGNAL(clicked()), parent, SLOT(clickChiffre()));
    QPushButton* b4 = new QPushButton("4");
    connect(b4, SIGNAL(clicked()), parent, SLOT(clickChiffre()));
    QPushButton* b5 = new QPushButton("5");
    connect(b5, SIGNAL(clicked()), parent, SLOT(clickChiffre()));
    QPushButton* b6 = new QPushButton("6");
    connect(b6, SIGNAL(clicked()), parent, SLOT(clickChiffre()));
    QPushButton* b7 = new QPushButton("7");
    connect(b7, SIGNAL(clicked()), parent, SLOT(clickChiffre()));
    QPushButton* b8 = new QPushButton("8");
    connect(b8, SIGNAL(clicked()), parent, SLOT(clickChiffre()));
    QPushButton* b9 = new QPushButton("9");
    connect(b9, SIGNAL(clicked()), parent, SLOT(clickChiffre()));
    QPushButton* b0 = new QPushButton("0");
    connect(b0, SIGNAL(clicked()), parent, SLOT(clickChiffre()));
    //QPushButton* undo = new QPushButton("UNDO");
    // connect(undo, SIGNAL(clicked()), parent, SLOT(clickUndo()));
    //QPushButton* redo = new QPushButton("REDO");
    // connect(redo, SIGNAL(clicked()), parent, SLOT(clickRedo()));
    QPushButton* clear = new QPushButton("CLEAR");
    connect(clear, SIGNAL(clicked()), parent, SLOT(clickClear()));
    QPushButton* div = new QPushButton("DIV");
    connect(div, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* mod = new QPushButton("MOD");
    connect(mod, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* neg = new QPushButton("NEG");
    connect(neg, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* eval = new QPushButton("EVAL");
    connect(eval, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* bPlus = new QPushButton("+");
    connect(bPlus, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* bMoins = new QPushButton("-");
    connect(bMoins, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* bEtoile = new QPushButton("*");
    connect(bEtoile, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* bSlash = new QPushButton("/");
    connect(bSlash, SIGNAL(clicked()), parent, SLOT(clickOperateur()));
    QPushButton* point = new QPushButton(".");
    connect(point, SIGNAL(clicked()), parent, SLOT(clickChiffre()));

    numLayout->addWidget(b7, 0, 0);
    numLayout->addWidget(b8, 0, 1);
    numLayout->addWidget(b9, 0, 2);
    // numLayout->addWidget(undo, 0, 3);
    // numLayout->addWidget(redo, 0, 4);
    numLayout->addWidget(neg, 0, 3);
    numLayout->addWidget(clear, 0, 4, 1, 2);
    numLayout->addWidget(b4, 1, 0);
    numLayout->addWidget(b5, 1, 1);
    numLayout->addWidget(b6, 1, 2);
    numLayout->addWidget(div, 1, 3);
    numLayout->addWidget(bEtoile, 1, 4);
    numLayout->addWidget(bSlash, 1, 5);
    numLayout->addWidget(b1, 2, 0);
    numLayout->addWidget(b2, 2, 1);
    numLayout->addWidget(b3, 2, 2);
    numLayout->addWidget(mod, 2, 3);
    numLayout->addWidget(bPlus, 2, 4);
    numLayout->addWidget(bMoins, 2, 5);
    numLayout->addWidget(b0, 3, 0, 1, 2);
    numLayout->addWidget(point, 3, 2);
    numLayout->addWidget(eval, 3, 3, 1, 3);

    groupnum->setLayout(numLayout);
    mainLayout->addWidget(groupnum);
    this->setLayout(mainLayout);
}

// =============== PUBLIC SLOTS ===============

void ClavierNumerique::minimize2(int state) {
    if (state) {
        // ETAT DU CLAVIER VISIBLE
        this->setVisible(false); // on masque le clavier
    } else {
        // ETAT DU CLAVIER MASQUE
        this->setVisible(true); // on rend le clavier visible
    }
}
