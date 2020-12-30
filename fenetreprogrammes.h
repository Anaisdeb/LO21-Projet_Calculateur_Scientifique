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
    QVBoxLayout* mainLayout;

    // METHODES
    void dataBaseConnect();
    void buildWindow();
    void dataBaseInit();
    void createTab();

public:

    void updateTab();
    static FenetreProgrammes* donneInstance();
    static void libereInstance();

public slots:
    void editerValeur();
    void validerValeur();
    void supprimerVariable();

signals:

};

#endif // FENETREPROGRAMMES_H
