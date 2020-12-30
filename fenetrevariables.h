#ifndef FENETREVARIABLES_H
#define FENETREVARIABLES_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>

class FenetreVariables : public QWidget {
    Q_OBJECT

private:
    FenetreVariables(QWidget *parent = nullptr);
    FenetreVariables(const FenetreVariables&) = delete;
    FenetreVariables& operator=(const FenetreVariables&) = delete;
    static FenetreVariables* uniqueInstance;

    // WIDGETS
    QPushButton* modifier;
    QPushButton* supprimer;
    QPushButton* valider;
    QLineEdit* infoUtilisateur;
    QLineEdit* champ;
    //QDoubleSpinBox* champ;
    QLineEdit* passageValeurs;
    QTableWidget* tab;
    QVBoxLayout* mainLayout;

    // METHODES
    void dataBaseConnect();
    void buildWindow();
    void dataBaseInit();
    void createTab();

public:
    static FenetreVariables* donneInstance();
    static void libereInstance();
    void updateTab();

public slots:
    void editerValeur();
    void validerValeur();
    void supprimerVariable();

signals:

};

#endif // FENETREVARIABLES_H
