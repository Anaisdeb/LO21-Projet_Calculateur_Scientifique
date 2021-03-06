#include "fenetrecalculatrice.h"
#include "fenetrevariables.h"
#include "fenetreparametres.h"
#include "claviernumerique.h"
#include "claviervariables.h"
#include "controleur.h"
#include "operateursmanager.h"
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
        // LAYOUT
        mainLayout = new QVBoxLayout;
        reduire = new QHBoxLayout();

        // MESSAGE POUR L'UTILISATEUR
        message = new QLineEdit;
        message->setReadOnly(true);
        message->setStyleSheet("background-color:yellow; color:red");
        mainLayout->addWidget(message);

        // CONTROLEUR
        controleur = &Controleur::donneInstance();
        controleur->pile.setNbItemsToAffiche(FenetreParametres::getNbLignesPiles());
        controleur->pile.setMessage("Bienvenue !");
        message->setText(Controleur::donneInstance().pile.getMessage());
        QObject::connect(&controleur->pile, SIGNAL(modificationEtat()), this, SLOT(refresh()));

        // AFFICHAGE ETAT DE LA PILE
        vuePile = new QTableWidget(static_cast<int>(FenetreParametres::getNbLignesPiles()), 1);
        vuePile->horizontalHeader()->hide();
        vuePile->horizontalHeader()->setStretchLastSection(true);
        vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
        vuePile->setSelectionMode(QAbstractItemView::NoSelection);
        vuePile->setStyleSheet("background-color:Teal; color:white;");
        vuePile->verticalHeader()->setStyleSheet("color:black");
        vuePile->setFixedHeight(static_cast<int>(FenetreParametres::getNbLignesPiles()) * vuePile->rowHeight(0) + 3);
        mainLayout->addWidget(vuePile);

        // LIGNE DE COMMANDE
        commande = new QLineEdit("");
        commande->installEventFilter(this);
        mainLayout->addWidget(commande);
        connect(commande, SIGNAL(returnPressed()), this, SLOT(getNextCommande()));

        // CLAVIER VARIABLE
        clavier1 = new ClavierVariables(this);
        clavier1->setVisible(true);

        // CLAVIER NUMERIQUE
        clavier2 = new ClavierNumerique(this);
        clavier2->setVisible(true);

        // MASQUER LES CLAVIERS
        minimize_var = new QCheckBox("R??duire le clavier 1");
        minimize_num = new QCheckBox("R??duire le clavier 2");
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
    child = mainLayout->takeAt(1);
    delete child->widget(); // on supprime l'ancier QTableWidget
    delete child;

    vuePile = new QTableWidget(static_cast<int>(FenetreParametres::getNbLignesPiles()), 1); // on en cr??e un nouveau avec le nouveau nombre d'??l??ments
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
    std::vector<std::shared_ptr<Operande>>::const_iterator it = controleur->pile.end(); // iterateur sur le dernier ??l??ment de la pile
    for (unsigned int i = 0; i < FenetreParametres::getNbLignesPiles(); i++) {
        QTableWidgetItem* item;
        if (it !=controleur->pile.begin()) {
            --it;
            item = new QTableWidgetItem(QString::fromStdString((*it)->toString())); // on cr??e un QTableWidgetItem contenant l'??l??ment
        } else {
            item = new QTableWidgetItem("");
        }
            vuePile->setItem(static_cast<int>(i), 0, item); // on affiche l'??l??ment dans vuePile
    }
    message->setText(controleur->pile.getMessage()); // on affiche le message s'il y en a un
}

void FenetreCalculatrice::getNextCommande() {
    try
    {
        controleur->pile.setMessage("");
        std::string sList = (commande->text()).toStdString(); // on r??cupere la ligne de commande
        controleur->exec(sList); // on l'??x??cute
        commande->clear(); // on vide la ligne de commande
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
    commande->setText(commande->text() + button->text()); // on affiche le texte du bouton cliqu?? sur la ligne de commande
    commande->setFocus();
}

void FenetreCalculatrice::clickOperateur() {
    try {
        QPushButton* button = qobject_cast<QPushButton*>(sender());
        commande->setText(commande->text() + button->text()); // on affiche le texte du bouton cliqu?? sur la ligne de commande
        commande->setFocus();
        getNextCommande(); // on ex??cute la ligne de commande
        refresh(); // on met a jour l'affichage de la pile
    } catch(ProjetException& e) {
        FenetreCalculatrice::donneInstance()->majException(e.what());
    }
}

void FenetreCalculatrice::clickClear() {
    if (!controleur->pile.estVide()) {
        while (!controleur->pile.estVide()) {
            controleur->pile.pop(); // on d??pile la pile tant qu'elle n'est pas vide
        }
        refresh();
    } else {
        message->setText("La pile est vide.");
    }
}

bool FenetreCalculatrice::eventFilter(QObject *object, QEvent *event) {
    QStringList sList = commande->text().split(" "); // on r??cupere la ligne de commande dans une liste delimit??e par " "
    QKeyEvent* pressed = static_cast<QKeyEvent*>(event);
    if (event->type() == QEvent::KeyPress) { // si l'utilisateur presse une cl?? du clavier
        if (OperateursManager::getInstance().isOperateur(pressed->text().toStdString()) && sList.indexOf("STO") != -1) {
            // SI LIGNE D'OPERANDE ET L'UTILISATEUR PRESSE UN OPERATEUR
            getNextCommande(); // on ex??cute la ligne de commande
            refresh();
            return true;
        }
    }
    return false;
}

void FenetreCalculatrice::ajoutBouton(const QString& nom) {
    clavier1->ajoutBouton(nom);
}
