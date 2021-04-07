#ifndef CLAVIERVARIABLES_H
#define CLAVIERVARIABLES_H

#include <QWidget>
#include <QGridLayout>

class ClavierVariables : public QWidget {
    Q_OBJECT

    // LAYOUT
    QGridLayout* varLayout;

    // ATTRIBUTS
    unsigned int *ver = new unsigned int(3);
    unsigned int *hor = new unsigned int(2);

public:
    ClavierVariables(QWidget* parent = nullptr);
    /**
     * @brief : Créer un bouton programme ou variable
     * @param : (const QString&) Nom du bouton
     */
    void ajoutBouton(const QString& nom);

public slots:
    /**
     * @brief : Masque le clavier variable
     * @param : (int) Etat du clavier
     */
    void minimize1(int state);
};
#endif // CLAVIERVARIABLES_H
