#ifndef FENETREPROGRAMMES_H
#define FENETREPROGRAMMES_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>

class FenetreProgrammes : public QWidget {
    Q_OBJECT

private:
    FenetreProgrammes(QWidget *parent = nullptr);
    FenetreProgrammes(const FenetreProgrammes&) = delete;
    FenetreProgrammes& operator=(const FenetreProgrammes&) = delete;
    static FenetreProgrammes* uniqueInstance;

    // WIDGETS
    QPushButton* modifier;
    QPushButton* supprimer;
    QPushButton* valider;
    QLineEdit* infoUtilisateur;
    QLineEdit* champ;
    QLineEdit* passageValeurs;
    QTableWidget* tab;
    QLayoutItem *child;
    QHBoxLayout* boutons;
    QVBoxLayout* mainLayout;

    // METHODES
    /**
    * @brief : construire la fenêtre
    */
    void buildWindow();

    /**
    * @brief : créer le QTableWidget qui contiendra les variables
    */
    void createTab();

public:
    static FenetreProgrammes* donneInstance();
    static void libereInstance();

    /**
    * @brief : mettre à jour le QTableWidget avec les valeurs de la BDD
    */
    void updateTab();

public slots:
    /**
    * @brief : vérifier qu'une variable existe avant de pouvoir la modifier
    */
    void editerValeur();

    /**
    * @brief : modifier une variable dans la BDD et dans le Manager
    */
    void validerValeur();

    /**
    * @brief : supprimer une variable de la BDD et du Manager
    */
    void supprimerVariable();
};

#endif // FENETREPROGRAMMES_H
