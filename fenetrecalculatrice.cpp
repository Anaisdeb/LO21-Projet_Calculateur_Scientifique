#include "fenetrecalculatrice.h"
#include "fenetrevariables.h"
#include "fenetreparametres.h"
#include "claviernumerique.h"
#include "claviervariables.h"
#include "controleur.h"
#include "projetexception.h"
#include <QObject>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>
#include <QKeyEvent>

FenetreCalculatrice* FenetreCalculatrice::uniqueInstance = nullptr;

// =============== CONSTRUCTEUR ===============

FenetreCalculatrice::FenetreCalculatrice(QWidget* parent) : QWidget(parent)
{
    // CREATION DE LA FENETRE
    buildWindow();
}

// =============== PRIVATE ===============

void FenetreCalculatrice::buildWindow() {
        mainLayout = new QVBoxLayout;

        message = new QLineEdit;
        message->setReadOnly(true);
        message->setStyleSheet("background-color:yellow; color:red");
        mainLayout->addWidget(message);

        controleur = &Controleur::donneInstance();
        controleur->pile.setNbItemsToAffiche(FenetreParametres::getNbLignesPiles());
        controleur->pile.setMessage("Bienvenue " + FenetreParametres::getNomUtilisateur() + " !");
        message->setText(Controleur::donneInstance().pile.getMessage());

        vuePile = new QTableWidget(static_cast<int>(FenetreParametres::getNbLignesPiles()), 1);
        vuePile->horizontalHeader()->hide();
        vuePile->horizontalHeader()->setStretchLastSection(true);
        vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
        vuePile->setSelectionMode(QAbstractItemView::NoSelection);
        vuePile->setStyleSheet("background-color:Teal; color:white;");
        vuePile->verticalHeader()->setStyleSheet("color:black");
        vuePile->setFixedHeight(static_cast<int>(FenetreParametres::getNbLignesPiles()) * vuePile->rowHeight(0) + 3);
        mainLayout->addWidget(vuePile);

        commande = new QLineEdit("");
        commande->installEventFilter(this);
        mainLayout->addWidget(commande);

        connect(commande, SIGNAL(returnPressed()), this, SLOT(getNextCommande()));
        QObject::connect(&controleur->pile, SIGNAL(modificationEtat()), this, SLOT(refresh())); // connect au refresh mrche pas je crois

        clavier1 = new ClavierVariables(this);
        clavier1->setVisible(true);

        clavier2 = new ClavierNumerique(this);
        clavier2->setVisible(true);

        QHBoxLayout* reduire = new QHBoxLayout();
        QCheckBox* minimize_var = new QCheckBox("Réduire le clavier 1");
        QCheckBox* minimize_num = new QCheckBox("Réduire le clavier 2");
        minimize_var->setChecked(false);
        minimize_num->setChecked(false);
        reduire->addWidget(minimize_var);
        reduire->addWidget(minimize_num);
        mainLayout->addLayout(reduire);
        connect(minimize_num, SIGNAL(stateChanged(int)), clavier2, SLOT(minimize2(int)));
        connect(minimize_var, SIGNAL(stateChanged(int)), clavier1, SLOT(minimize1(int)));

        mainLayout->addWidget(clavier1);

        mainLayout->addWidget(clavier2);

        mainLayout->addStretch();

        this->setLayout(mainLayout);
    }

// =============== PUBLIC ===============

FenetreCalculatrice* FenetreCalculatrice::donneInstance()
{
    if (uniqueInstance == nullptr)
    {
        uniqueInstance = new FenetreCalculatrice;
    }

    return uniqueInstance;
}

void FenetreCalculatrice::libereInstance()
{
    delete uniqueInstance;
    uniqueInstance = nullptr;
}

// =============== PUBLIC SLOTS ===============

void FenetreCalculatrice::majException(const std::string s)
{
    QString qstr = QString::fromStdString(s);
    message->setText(qstr);
}

void FenetreCalculatrice::majPile(int n)
{
    QLayoutItem *child;
    child = mainLayout->takeAt(1);
    delete child->widget();
    delete child;

    vuePile = new QTableWidget(static_cast<int>(FenetreParametres::getNbLignesPiles()), 1);
    vuePile->horizontalHeader()->hide();
    vuePile->horizontalHeader()->setStretchLastSection(true);
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vuePile->setSelectionMode(QAbstractItemView::NoSelection);
    vuePile->setStyleSheet("background-color:Teal; color:white;");
    vuePile->verticalHeader()->setStyleSheet("color:black");
    vuePile->setFixedHeight(n * vuePile->rowHeight(0) + 3);

    this->mainLayout->insertWidget(1, vuePile);
    this->setLayout(mainLayout);

    refresh();
}

void FenetreCalculatrice::refresh() {
    std::vector<std::shared_ptr<Operande>>::const_iterator it = controleur->pile.end();
    for (unsigned int i = 0; i < FenetreParametres::getNbLignesPiles(); i++) {
        QTableWidgetItem* item;
        if (it !=controleur->pile.begin()) {
            --it;
            item = new QTableWidgetItem(QString::fromStdString((*it)->toString()));
        } else {
            item = new QTableWidgetItem("");
        }
            vuePile->setItem(static_cast<int>(i), 0, item);
    }
    message->setText(controleur->pile.getMessage());
}

void FenetreCalculatrice::getNextCommande() {
    try
    {
        controleur->pile.setMessage("");
        std::string sList = (commande->text()).toStdString();
        controleur->exec(sList);
        commande->clear();
        refresh();
        return;
    }
    catch(ProjetException& e)
    {
        FenetreCalculatrice::donneInstance()->majException(e.what());
    }

}

void FenetreCalculatrice::clickChiffre() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}

void FenetreCalculatrice::clickOperateur() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
    getNextCommande();
    refresh();
}

void FenetreCalculatrice::clickClear() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();

}

void FenetreCalculatrice::clickUndo() {
    if (controleur->pile.estVide()) throw ProjetException("La pile est vide.");
    auto save = controleur->pile.top();
    controleur->pile.pop();
    // if (pile->estVide()) throw exception;
    //Expression& save = pile->top();
    //pop();
    refresh();
}

void FenetreCalculatrice::clickRedo() {
    // pile->push(save);
        refresh();
}

// marche pas
/*void FenetreCalculatrice::keyPressEvent(QKeyEvent *event) {
    if (Qt::Key_Asterisk || Qt::Key_Plus || Qt::Key_Minus || Qt::Key_Slash) {
        getNextCommande();
    }
}*/

bool FenetreCalculatrice::eventFilter(QObject *object, QEvent *event) {
    QKeyEvent* pressed = static_cast<QKeyEvent*>(event);
    if (event->type() == QEvent::KeyPress) {
        if (pressed->key() == Qt::Key_Up) {
            QMessageBox::information(FenetreCalculatrice::donneInstance(), "Erreur", "la valeur est dans la zone");
        }
    }
}

void FenetreCalculatrice::clickOpUnaire() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
    getNextCommande();
    refresh();
}
void FenetreCalculatrice::clickOpBinaire() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
    getNextCommande();
    refresh();
}

/*
void FenetreCalculatrice::clickMod() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}

void FenetreCalculatrice::clickDiv() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}

void FenetreCalculatrice::clickNeg() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}

void FenetreCalculatrice::clickNum() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickDen() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickPow() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickSin() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickCos() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickTan() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickArcsin() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickArccos() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickArctan() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickSqrt() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickExp() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickLn() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickEgal() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickNotegal() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickInfegal() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickSupegal() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickInf() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickSup() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickEt() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickOu() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickNon() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickDup() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickDrop() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickSwap() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickIft() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickIfte() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}
void FenetreCalculatrice::clickTantque() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}*/
