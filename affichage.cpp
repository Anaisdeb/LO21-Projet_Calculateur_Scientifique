#include "affichage.h"
#include "computer.h"
#include <QLineEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QObject>

Affichage::Affichage(QWidget* parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;

    message = new QLineEdit;
    message->setReadOnly(true);
    message->setStyleSheet("background-color:lightGray; color:black");
    mainLayout->addWidget(message);

    pile = new Pile();
    pile->setMessage("Bienvenue!");
    message->setText(pile->getMessage());
    pile->setNbItemsToAffiche(4); // a modif avec les paramètres

    vuePile = new QTableWidget(4, 1); // a modif avec les paramètres
    vuePile->horizontalHeader()->hide();
    vuePile->horizontalHeader()->setStretchLastSection(true);
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vuePile->setSelectionMode(QAbstractItemView::NoSelection);
    vuePile->setStyleSheet("background-color:Teal; color:white;");
    vuePile->verticalHeader()->setStyleSheet("color:black");
    vuePile->setFixedHeight(pile->getNbItemsToAffiche() * vuePile->rowHeight(0) + 3);
    mainLayout->addWidget(vuePile);

    commande = new QLineEdit("");
    mainLayout->addWidget(commande);

    controleur = new Controleur(ExpressionManager::getInstance(), *pile);
    connect(pile, SIGNAL(modificationEtat()), this, SLOT(refresh()));
    connect(commande, SIGNAL(returnPressed()), this, SLOT(getNextCommande()));

    QGroupBox* groupvar = new QGroupBox("Clavier variables et programmes");
    QPushButton* num = new QPushButton("NUM");
    QPushButton* den = new QPushButton("DEN");
    QPushButton* pow = new QPushButton("POW");
    QPushButton* sin = new QPushButton("SIN");
    QPushButton* cos = new QPushButton("COS");
    QPushButton* tan = new QPushButton("TAN");
    QPushButton* arcsin = new QPushButton("ARCSIN");
    QPushButton* arccos = new QPushButton("ARCCOS");
    QPushButton* arctan = new QPushButton("ARCTAN");
    QPushButton* sqrt = new QPushButton("SQRT");
    QPushButton* exp = new QPushButton("EXP");
    QPushButton* ln = new QPushButton("LN");
    QPushButton* egal = new QPushButton("=");
    QPushButton* notegal = new QPushButton("!=");
    QPushButton* infegal = new QPushButton("=<");
    QPushButton* supegal = new QPushButton(">=");
    QPushButton* inf = new QPushButton("<");
    QPushButton* sup = new QPushButton(">");
    QPushButton* et = new QPushButton("AND");
    QPushButton* ou = new QPushButton("OR");
    QPushButton* non = new QPushButton("NOT");
    QPushButton* dup = new QPushButton("DUP");
    QPushButton* drop = new QPushButton("DROP");
    QPushButton* swap = new QPushButton("SWAP");
    QPushButton* ift = new QPushButton("IFT");
    QPushButton* ifte = new QPushButton("IFTE");
    QPushButton* tantque = new QPushButton("WHILE");
    QGridLayout* varLayout = new QGridLayout();
    varLayout->addWidget(egal, 0, 0);
    varLayout->addWidget(num, 0, 1);
    varLayout->addWidget(den, 0, 2);
    varLayout->addWidget(pow, 0, 3);
    varLayout->addWidget(notegal, 1, 0);
    varLayout->addWidget(sin, 1, 1);
    varLayout->addWidget(cos, 1, 2);
    varLayout->addWidget(tan, 1, 3);
    varLayout->addWidget(infegal, 2, 0);
    varLayout->addWidget(arcsin, 2, 1);
    varLayout->addWidget(arccos, 2, 2);
    varLayout->addWidget(arctan, 2, 3);
    varLayout->addWidget(supegal, 3, 0);
    varLayout->addWidget(sqrt, 3, 1);
    varLayout->addWidget(exp, 3, 2);
    varLayout->addWidget(ln, 3, 3);
    varLayout->addWidget(inf, 4, 0);
    varLayout->addWidget(dup, 4, 1);
    varLayout->addWidget(drop, 4, 2);
    varLayout->addWidget(swap, 4, 3);
    varLayout->addWidget(sup, 5, 0);
    varLayout->addWidget(ift, 5, 1);
    varLayout->addWidget(ifte, 5, 2);
    varLayout->addWidget(tantque, 5, 3);
    varLayout->addWidget(et, 6, 0);
    varLayout->addWidget(ou, 7, 0);
    varLayout->addWidget(non, 8, 0);

    QGroupBox* groupnum = new QGroupBox("Clavier opérateurs");
    QPushButton* b1 = new QPushButton("1");
    QPushButton* b2 = new QPushButton("2");
    QPushButton* b3 = new QPushButton("3");
    QPushButton* b4 = new QPushButton("4");
    QPushButton* b5 = new QPushButton("5");
    QPushButton* b6 = new QPushButton("6");
    QPushButton* b7 = new QPushButton("7");
    QPushButton* b8 = new QPushButton("8");
    QPushButton* b9 = new QPushButton("9");
    QPushButton* b0 = new QPushButton("0");
    QPushButton* undo = new QPushButton("UNDO");
    QPushButton* redo = new QPushButton("REDO");
    QPushButton* clear = new QPushButton("CLEAR");
    QPushButton* div = new QPushButton("DIV");
    QPushButton* mod = new QPushButton("MOD");
    QPushButton* neg = new QPushButton("NEG");
    QPushButton* eval = new QPushButton("EVAL");
    QPushButton* bPlus = new QPushButton("+");
    QPushButton* bMoins = new QPushButton("-");
    QPushButton* bEtoile = new QPushButton("\303\227");
    QPushButton* bSlash = new QPushButton("\303\267");
    QPushButton* virgule = new QPushButton(",");
    QGridLayout* numLayout = new QGridLayout();
    numLayout->addWidget(b7, 0, 0);
    numLayout->addWidget(b8, 0, 1);
    numLayout->addWidget(b9, 0, 2);
    numLayout->addWidget(undo, 0, 3);
    numLayout->addWidget(redo, 0, 4);
    numLayout->addWidget(clear, 0, 5);
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
    numLayout->addWidget(virgule, 3, 2);
    numLayout->addWidget(neg, 3, 3);
    numLayout->addWidget(eval, 3, 4, 1, 2);

    groupvar->setLayout(varLayout);
    groupnum->setLayout(numLayout);
    mainLayout->addWidget(groupvar);
    mainLayout->addWidget(groupnum);

    this->setLayout(mainLayout);
}

void Affichage::refresh() {
    Pile::iterator it = pile->begin();
    for (unsigned int i = 0; i < pile->getNbItemsToAffiche(); i++) {
        QTableWidgetItem* item;
        if (it != pile->end()) {
            item = new QTableWidgetItem(((*it).toString()));
            ++it;
        } else {
            item = new QTableWidgetItem("");
        }
        vuePile->setItem(i, 0, item);
    }
    message->setText(pile->getMessage());
}

void Affichage::getNextCommande() {
    pile->setMessage("");
    QStringList sList = commande->text().split(" ");
    QStringList::const_iterator c_it;
    for (c_it = sList.constBegin(); c_it != sList.constEnd(); ++c_it) {
            controleur->commande(*c_it) ;
    }
    commande->clear();
    return;
}



