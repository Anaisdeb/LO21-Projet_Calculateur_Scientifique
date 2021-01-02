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
        mainLayout = new QVBoxLayout;

        message = new QLineEdit;
        message->setReadOnly(true);
        message->setStyleSheet("background-color:yellow; color:red");
        mainLayout->addWidget(message);

        controleur = &Controleur::donneInstance();
        controleur->pile.setNbItemsToAffiche(FenetreParametres::getNbLignesPiles());
        controleur->pile.setMessage("Bienvenue !");
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
        QObject::connect(&controleur->pile, SIGNAL(modificationEtat()), this, SLOT(refresh()));

        clavier1 = new ClavierVariables(this);
        clavier1->setVisible(true);

        clavier2 = new ClavierNumerique(this);
        clavier2->setVisible(true);

        reduire = new QHBoxLayout();
        minimize_var = new QCheckBox("Réduire le clavier 1");
        minimize_num = new QCheckBox("Réduire le clavier 2");
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
    std::vector<std::shared_ptr<Operande>>::const_iterator it = controleur->pile.end(); // iterateur sur le dernier élément de la pile
    for (unsigned int i = 0; i < FenetreParametres::getNbLignesPiles(); i++) {
        QTableWidgetItem* item;
        if (it !=controleur->pile.begin()) {
            --it;
            item = new QTableWidgetItem(QString::fromStdString((*it)->toString())); // on crée un QTableWidgetItem contenant l'élément
        } else {
            item = new QTableWidgetItem("");
        }
            vuePile->setItem(static_cast<int>(i), 0, item); // on affiche l'élément dans vuePile
    }
    message->setText(controleur->pile.getMessage()); // on affiche le message s'il y en a un
}

void FenetreCalculatrice::getNextCommande() {
    try
    {
        controleur->pile.setMessage("");
        std::string sList = (commande->text()).toStdString(); // on récupere la ligne de commande
        controleur->exec(sList); // on l'éxécute
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
    commande->setText(commande->text() + button->text()); // on affiche le texte du bouton cliqué sur la ligne de commande
    commande->setFocus();
}

void FenetreCalculatrice::clickOperateur() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text()); // on affiche le texte du bouton cliqué sur la ligne de commande
    commande->setFocus();
    getNextCommande(); // on exécute la ligne de commande
    refresh(); // on met a jour l'affichage de la pile
}

void FenetreCalculatrice::clickClear() {
    if (!controleur->pile.estVide()) {
        while (!controleur->pile.estVide()) {
            controleur->pile.pop(); // on dépile la pile tant qu'elle n'est pas vide
        }
        refresh();
    } else {
        message->setText("La pile est vide.");
    } // comment throw exception? majExcecption ne prends pas de QString
}

void FenetreCalculatrice::clickUndo() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}

void FenetreCalculatrice::clickRedo() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    commande->setText(commande->text() + button->text());
    commande->setFocus();
}

bool FenetreCalculatrice::eventFilter(QObject *object, QEvent *event) {
    QStringList sList = commande->text().split(" "); // on récupere la ligne de commande dans une liste delimitée par " "
    QKeyEvent* pressed = static_cast<QKeyEvent*>(event);
    if (event->type() == QEvent::KeyPress) { // si l'utilisateur presse une clé du clavier
        if (OperateursManager::getInstance().isOperateur(pressed->text().toStdString()) && sList.indexOf("STO") != -1) {
            // SI LIGNE D'OPERANDE ET L'UTILISATEUR PRESSE UN OPERATEUR
            getNextCommande(); // on exécute la ligne de commande
            refresh();
            return true;
        }
    }
    return QObject::eventFilter(object, event);
}
