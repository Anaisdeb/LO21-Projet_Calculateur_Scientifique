#ifndef FENETRECALCULATRICE_H
#define FENETRECALCULATRICE_H

#include "claviernumerique.h"
#include "claviervariables.h"
#include "controleur.h"
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QPushButton>
#include <QGroupBox>
#include <QCheckBox>

class ClavierNumerique;

class FenetreCalculatrice : public QWidget {
    Q_OBJECT

private:
    // METHODES
    /**
     * @brief : Construire à l'aide de widgets la fenêtre à afficher
     */
    void buildWindow();
    FenetreCalculatrice(QWidget *parent = nullptr);
    FenetreCalculatrice(const FenetreCalculatrice&) = delete;
    FenetreCalculatrice& operator=(const FenetreCalculatrice&) = delete;
    static FenetreCalculatrice* uniqueInstance;

    // WIDGETS
    QLineEdit* message;
    QVBoxLayout * mainLayout;
    QTableWidget* vuePile;
    QLineEdit* commande;
    Controleur* controleur;
    ClavierNumerique* clavier2;
    ClavierVariables* clavier1;

protected:
    /**
    * @brief : Filtre la ligne de commande
    * @param : (QObject*, QEvent*) Objet parent, Click sur une touche du clavier ordinateur
    * @return : (bool) TRUE si le click a ete filtré, FALSE sinon
    */
    bool eventFilter(QObject* object, QEvent *event) override;

public:

    static FenetreCalculatrice* donneInstance();
    static void libereInstance();

public slots:
    void majPile(int);
    /**
    * @brief : Mise à jour de l'affichage de la pile sur vuePile
    */
    void refresh();
    /**
    * @brief : Envoie la ligne de commande au controleur
    */
    void getNextCommande();
    /**
    * @brief : Appui sur un bouton chiffre (1, 2, ..., 9, 0)
    */
    void clickChiffre();
    /**
    * @brief : Appui sur un bouton opérateur (*, DUP, SWAP, =, ...)
    */
    void clickOperateur();
    /**
    * @brief : Vide tous les éléments de la pile
    */
    void clickClear();
    void clickUndo();
    void clickRedo();
    void majException(const std::string s);

};



#endif // FENETRECALCULATRICE_H
