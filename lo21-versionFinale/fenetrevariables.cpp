#include "fenetrevariables.h"
#include "fenetrecalculatrice.h"
#include "projetexception.h"
#include "manager.h"
#include "controleur.h"
#include "connexionbasededonnees.h"
#include <QtSql>
#include <QVector>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

FenetreVariables* FenetreVariables::uniqueInstance = nullptr;

// =============== CONSTRUCTEUR ===============

FenetreVariables::FenetreVariables(QWidget *parent) : QWidget(parent)
{
    buildWindow();
}

// =============== PUBLIC ===============

void FenetreVariables::updateTab()
{
    child = mainLayout->takeAt(4);

    delete child->widget(); // delete the widget
    delete child;   // delete the layout item

    this->createTab();

    this->mainLayout->addWidget(tab);
    this->setLayout(mainLayout);
}

FenetreVariables* FenetreVariables::donneInstance()
{
    if (uniqueInstance == nullptr)
    {
        uniqueInstance = new FenetreVariables;
    }

    return uniqueInstance;
}

void FenetreVariables::libereInstance()
{
    delete uniqueInstance;
    uniqueInstance = nullptr;
}

// =============== PRIVATE ===============

void FenetreVariables::buildWindow()
{
        // QPUSHBUTTONS
        modifier = new QPushButton("Modifier");
        supprimer= new QPushButton("Supprimer");
        valider = new QPushButton("Valider");
        valider->setEnabled(false);

        // QLINEEDIT
        champ = new QLineEdit;
        infoUtilisateur = new QLineEdit("Rentrer dans le champ ci-dessous le nom d'une "
                                        "variable que vous souhaitez supprimer ou modifier");
        infoUtilisateur->setReadOnly(true);
        infoUtilisateur->setStyleSheet("background-color:yellow; color:red");

        passageValeurs = new QLineEdit;
        passageValeurs->setVisible(false);

        // QTABLEWIDGET
        this->createTab();

        // LAYOUTS
        boutons = new QHBoxLayout();
        boutons->addWidget(modifier);
        boutons->addWidget(valider);
        boutons->addWidget(supprimer);

        // AJOUT DES WIDGETS/LAYOUTS A LA FENETRE PRINCIPALE
        mainLayout = new QVBoxLayout;
        mainLayout->addWidget(passageValeurs);
        mainLayout->addWidget(infoUtilisateur);
        mainLayout->addWidget(champ);
        mainLayout->addLayout(boutons);
        mainLayout->addWidget(tab);
        this->setLayout(mainLayout);

        // CONNEXION SIGNAUX-SLOTS
        QObject::connect(modifier, SIGNAL(clicked()), this, SLOT(editerValeur()));
        QObject::connect(valider, SIGNAL(clicked()), this, SLOT(validerValeur()));
        QObject::connect(supprimer, SIGNAL(clicked()), this, SLOT(supprimerVariable()));
}


void FenetreVariables::createTab()
{
    QSqlQuery query;

    // NOMBRE D'ELEMENTS DE LA TABLES 'variables'
    if(!query.exec("select count(*) from variables"))
        qWarning() << "FenetreVariables::buildWindow - ERROR: " << query.lastError().text();

    query.first(); // sert à positionner query sur une donnée valide

    // QTABLEWIDGET
    tab = new QTableWidget(query.value(0).toInt(), 2);
    tab->horizontalHeader()->setStretchLastSection(true);
    tab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tab->verticalHeader()->setVisible(false);
    tab->setStyleSheet("background-color:Teal");
    tab->verticalHeader()->setStyleSheet("color:black");
    tab->setHorizontalHeaderItem(0, new QTableWidgetItem("Nom"));
    tab->setHorizontalHeaderItem(1, new QTableWidgetItem("Valeur"));

    if(!query.exec("select * from variables"))
        qWarning() << "ERROR: " << query.lastError().text();

    int j= 0;

    while (query.next())
    {
        for(int i = 0; i<2; i++)
        {
            tab->setItem(j, i, new QTableWidgetItem(query.value(i+1).toString()));
        }

        j++;
    }
}

// =============== PUBLIC SLOTS ===============

void FenetreVariables::editerValeur()
{
    this->champ->setText(this->champ->text().simplified()); // supprime les espaces dans la zone de texte du QLineEdit
    QString nomVar = this->champ->text();

    if(nomVar.isEmpty())
    {
        // CHAMP VIDE
        this->infoUtilisateur->setText("Veuillez remplir le champ avant de modifier une variable.");
        this->champ->setFocus();
    }
    else
    {
        // CHAMP NON VIDE
        QSqlQuery query;

        query.prepare("SELECT id FROM variables WHERE nom = ?");
        query.addBindValue(this->champ->text());

        if(!query.exec())
          qWarning() << "ERROR: " << query.lastError().text();

        if(!query.first())
        {
            // LA VARIABLE N'EXISTE PAS
            this->infoUtilisateur->setText("La variable que vous avez renseignée n'existe pas.");
            this->champ->clear();
            this->champ->setFocus();
        }
        else
        {
            // LA VARIABLE EXISTE
            this->passageValeurs->setText(query.value(0).toString()); //idVar rangé
            this->infoUtilisateur->setText("Veuillez remplir la nouvelle valeur de la "
                                           "variable " + nomVar + ".");
            this->champ->clear();
            this->champ->setFocus();
            this->modifier->setEnabled(false);
            this->valider->setEnabled(true);
        }
    }
}

void FenetreVariables::validerValeur()
{
    this->champ->setText(this->champ->text().simplified());
    QString valVar = this->champ->text();

    if(valVar.isEmpty())
    {
        // CHAMP VIDE
        this->infoUtilisateur->setText("Veuillez remplir le champ avant de valider.");
        this->champ->setFocus();
    }
    else
    {
        // CHAMP NON VIDE
        QSqlQuery query;

        // RECUPERATION DE L'ID DE LA VARIABLE
        QString idVar = this->passageValeurs->text();

        // RECUPERATION DU NOM
        if(!query.exec("Select nom FROM variables WHERE id = '" + idVar +  "'"))
            qWarning() << "ERROR: " << query.lastError().text();

        if(query.first())
        {
            QString nomVar = query.value(0).toString();

            try {
                Manager::getInstance().ForgetAtome(nomVar.toUtf8().constData());
                QString s = "'"+ nomVar +"' "+valVar+" STO";
                Controleur::donneInstance().exec(s.toUtf8().constData());
            } catch (ProjetException& e) {
                infoUtilisateur->setText(e.what());
            }

            this->infoUtilisateur->setText("La variable " + nomVar + " a bien été modifiée.");
            this->champ->clear();
            this->modifier->setEnabled(true);
            this->valider->setEnabled(false);

            this->updateTab();
        }
        else
            qWarning() << "ERROR: " << query.lastError().text();
    }
}

void FenetreVariables::supprimerVariable()
{
    this->champ->setText(this->champ->text().simplified()); // supprime les espaces dans la zone de texte du QLineEdit
    QString nomVar = this->champ->text();

    if(nomVar.isEmpty())
    {
        // CHAMP VIDE
        this->infoUtilisateur->setText("Veuillez remplir le champ avant de supprimer une variable.");
        this->champ->setFocus();
    }
    else
    {
        // CHAMP NON VIDE
        QSqlQuery query;

        // RECUPERATION DE L'IDENTIFIANT
        query.prepare("SELECT id FROM variables WHERE nom = ?");
        query.addBindValue(this->champ->text());

        if(!query.exec())
          qWarning() << "ERROR: " << query.lastError().text();

        if(!query.first())
        {
            this->infoUtilisateur->setText("La variable que vous avez renseignée n'existe pas.");
            this->champ->clear();
            this->champ->setFocus();
        }
        else
        {
            Manager::getInstance().ForgetAtome(nomVar.toUtf8().constData());

            this->infoUtilisateur->setText("La variable " + nomVar + " a bien été supprimée.");
            this->champ->clear();
            this->champ->setFocus();
            updateTab();
        }
    }
}
