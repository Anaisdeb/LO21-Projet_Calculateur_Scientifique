#ifndef FENETRECALCULATRICE_H
#define FENETRECALCULATRICE_H

#include "computer.h"
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

class FenetreCalculatrice : public QWidget{
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

    QLineEdit* message;
    QVBoxLayout * mainLayout;
    //Pile* pile;
    QTableWidget* vuePile;
    QLineEdit* commande;
    Controleur* controleur;
    ClavierNumerique* clavier2;
    ClavierVariables* clavier1;
    //Expression save(int v); // jsp

protected:
    bool eventFilter(QObject* object, QEvent *event) override;

public:
    static FenetreCalculatrice* donneInstance();
    static void libereInstance();
    //void keyPressEvent(QKeyEvent *event);
       /*void clickMod();
       void clickDiv();
       void clickNeg();
       void clickNum();
       void clickDen();
       void clickPow();
       void clickSin();
       void clickCos();
       void clickTan();
       void clickArcsin();
       void clickArccos();
       void clickArctan();
       void clickSqrt();
       void clickExp();
       void clickLn();
       void clickEgal();
       void clickNotegal();
       void clickInfegal();
       void clickSupegal();
       void clickInf();
       void clickSup();
       void clickEt();
       void clickOu();
       void clickNon();
       void clickDup();
       void clickDrop();
       void clickSwap();
       void clickIft();
       void clickIfte();
       void clickTantque();*/

public slots:
    void majPile(int);
    void refresh();
    void getNextCommande();
    void clickChiffre();
    void clickOperateur();
    void clickClear();
    void clickUndo();
    void clickRedo();
    void clickOpUnaire();
    void clickOpBinaire();
    void majException(const std::string s);

};



#endif // FENETRECALCULATRICE_H
