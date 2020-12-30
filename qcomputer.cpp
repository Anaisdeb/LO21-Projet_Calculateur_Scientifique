#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSql>


#include "qcomputer.h"
#include "controleur.h"
#include "fenetrecalculatrice.h"
#include "fenetrevariables.h"
#include "fenetreparametres.h"
#include "fenetreprogrammes.h"

// =============== CONSTRUCTEUR ===============

QComputer::QComputer(QWidget *parent) : QWidget(parent)
{
    // CONSTRUCTION DE LA FENETRE
    buildWindow();
}

// =============== PRIVATE ===============

void QComputer::buildWindow()
{
    FenetreParametres* fparam = new FenetreParametres();

    // STYLE PAR DEFAUT
    QString tabStyle1("QTabBar::tab {color: rgb(89, 89, 89);}"
                     "QTabBar::tab:selected {color:rgb(255, 217, 18);}");

    tabWidget = new QTabWidget;
    tabWidget->setStyleSheet(tabStyle1);
    tabWidget->setMovable(true);

    // AJOUT DES DIFFERENTS ONGLETS
    tabWidget->addTab(FenetreCalculatrice::donneInstance(), "Calculatrice");
    tabWidget->setTabToolTip(0, "Permet de réaliser des calculs");

    tabWidget->addTab(FenetreVariables::donneInstance(), "Variables");
    tabWidget->setTabToolTip(1, "Permet de modifier/supprimer des variables");

    tabWidget->addTab(FenetreProgrammes::donneInstance(), "Programmes");
    tabWidget->setTabToolTip(2, "Permet de modifier/supprimer des programmes");

    tabWidget->addTab(fparam, "Paramètres");
    tabWidget->setTabToolTip(3, "Permet de modifier les paramètres de la calculatrice");

    // LAYOUTS
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);

    this->setLayout(mainLayout);

    addDatabaseToManager();

    // TITRE DE LA FENETRE PRINCIPALE
    this->setWindowTitle("Comp'Ut");
}

void addDatabaseToManager()
{
    QSqlQuery query;
    QString strcommande = "";

    // CONCATENATION DES VALEURS DES TABLES 'programmes' ET 'variables'
    if(!query.exec("select * from programmes"))
        qWarning() << "ERROR: " << query.lastError().text();

    while (query.next())
    {
        strcommande = strcommande + "'" + query.value(1).toString() + "' " + query.value(2).toString() + " " + "STO" + " ";
    }

    if(!query.exec("select * from variables"))
        qWarning() << "ERROR: " << query.lastError().text();

    while (query.next())
    {
        strcommande = strcommande + "'" + query.value(1).toString() + "' " + query.value(2).toString() + " " + "STO" + " ";
    }


    // SUPPRESSION DES DONNEES DANS LA BDD
    if(!query.exec("delete from programmes"))
        qWarning() << "ERROR: " << query.lastError().text();

    if(!query.exec("delete from variables"))
        qWarning() << "ERROR: " << query.lastError().text();

    QMessageBox::information(FenetreCalculatrice::donneInstance(), "test", strcommande);
    Controleur::donneInstance().exec(strcommande.toUtf8().constData());
}
