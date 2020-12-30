#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "computer.h"
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QPushButton>
#include <QGroupBox>

class Affichage : public QWidget {
    Q_OBJECT

    QLineEdit* message;
    Pile* pile;
    QTableWidget* vuePile;
    QLineEdit* commande;
    Controleur* controleur;
    QGroupBox* clavierop;
    QGridLayout* numerosLayout;
    QVBoxLayout* operateursLayout;
    QHBoxLayout* padLayout;

public:
    explicit Affichage(QWidget *parent = nullptr);

public slots:
    void refresh();
    void getNextCommande();
    /* void click1();
    void click2();
    void click3();
    void click4();
    void click5();
    void click6();
    void click7();
    void click8();
    void click9();
    void click0();
    void clickPlus();
    void clickMois();
    void clickEtoile();
    void clickDiv();
    void clickEgal();
    void clickSuppr();
    void clickAC();*/
};

#endif // QCOMPUTER_H
