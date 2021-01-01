#include "fenetreparametres.h"
#include "fenetrecalculatrice.h"
#include <QtSql>
#include <QSqlQuery>
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QRadioButton>
#include <QMessageBox>
#include <QGroupBox>
#include <QObject>
#include <QSpinBox>

// INITIALISATION DES VARIABLES STATIC
unsigned int FenetreParametres::nbLignesPile = 4;
QString FenetreParametres::nomUtilsateur = "Utilisateur1";

// =============== CONSTRUCTEUR ===============

FenetreParametres::FenetreParametres(QWidget* parent) : QWidget(parent)
{
    // CREATION DE LA TABLE 'parametres' SI ELLE N'EXISTE PAS
    dataBaseInit();

    // CREATION DE LA FENETRE
    buildWindow();
}

// =============== PRIVATE ===============

void FenetreParametres::dataBaseInit()
{
    QSqlQuery query("CREATE TABLE IF NOT EXISTS parametres (id INTEGER PRIMARY KEY "
                    "AUTOINCREMENT, nbLignesPile VARCHAR(20), nomUtilisateur VARCHAR(20))");

    if(!query.isActive())
        qWarning() << "FenetreParametres::dataBaseInit - ERROR: " << query.lastError().text();
}

void FenetreParametres::buildWindow()
{
    // QLABEL
    QLabel* label_nom = new QLabel("Nom de l'utilisateur : ");
    QLabel* label_nb = new QLabel("Nombre d'éléments de la pile à afficher : ");

    // QLINEEDIT
    infoUtilisateur = new QLineEdit("Voici la fenêtre où vous pouvez modifier les paramètres "
                                    "de l'application à votre guise.");
    infoUtilisateur->setReadOnly(true);
    infoUtilisateur->setStyleSheet("background-color:yellow; color:red");

    nom = new QLineEdit;
    nom->setMaxLength(20);

    // QSPINBOX
    nb = new QSpinBox;
    nb->setRange(1, 10);
    nb->setValue(nbLignesPile);

    this->setDataBaseData();

    // LAYOUTS
    mainLayout = new QVBoxLayout;

    QHBoxLayout* layout_nom = new QHBoxLayout;
    layout_nom->addWidget(label_nom);
    layout_nom->addWidget(nom);

    QHBoxLayout* layout_nb = new QHBoxLayout;
    layout_nb->addWidget(label_nb);
    layout_nb->addWidget(nb);

    mainLayout->addWidget(infoUtilisateur);
    mainLayout->addLayout(layout_nom);
    mainLayout->addLayout(layout_nb);
    mainLayout->addStretch();

    this->setLayout(mainLayout);

    // CONNEXION SIGNAUX/SLOTS
    QObject::connect(nom, SIGNAL(textChanged(const QString&)), this, SLOT(actuNom(const QString&)));
    QObject::connect(nb, SIGNAL(valueChanged(int)), this, SLOT(actuNb(int)));
    QObject::connect(nb, SIGNAL(valueChanged(int)), FenetreCalculatrice::donneInstance(), SLOT(majPile(int)));
}

void FenetreParametres::setDataBaseData()
{
    QSqlQuery query;

    if(!query.exec("SELECT * FROM parametres"))
      qWarning() << "FenetreParametres::setDataBaseData - ERROR: " << query.lastError().text();

    if(query.first())
    {
        nb->setValue(query.value(1).toInt());
        FenetreParametres::setNbLignesPiles(static_cast<unsigned int>(query.value(1).toInt()));

        nom->setText(query.value(2).toString());
        FenetreParametres::setNomUtilisateur(query.value(2).toString());
    }
    else
        qWarning() << "FenetreParametres::setDataBaseData - ERROR: " << query.lastError().text();
}

// =============== PUBLIC SLOTS ===============

void FenetreParametres::actuNom(const QString& text)
{
    this->nom->setText(text.simplified()); // supprime les espaces dans la zone de texte du QLineEdit
    QString nomU = this->nom->text();

    if(nomU.isEmpty())
    {
        // CHAMP VIDE
        this->infoUtilisateur->setText("Veuillez remplir le champ relatif au nom.");
        this->nom->setFocus();
    }
    else
    {
        // CHAMP NON VIDE
        QSqlQuery query;

        query.prepare("UPDATE parametres SET nomUtilisateur = ? WHERE id = '1'");
        query.addBindValue(nomU);

        FenetreParametres::setNomUtilisateur(nomU);

        if(!query.exec())
            qWarning() << "ERROR: " << query.lastError().text();
    }
}

void FenetreParametres::actuNb(int i)
{
        QSqlQuery query;

        QString s = QString::number(i);

        query.prepare("UPDATE parametres SET nbLignesPile = ? WHERE id = '1'");
        query.addBindValue(s);

        FenetreParametres::setNbLignesPiles(static_cast<unsigned int>(i));

        if(!query.exec())
            qWarning() << "ERROR: " << query.lastError().text();
}
