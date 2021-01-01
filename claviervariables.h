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
    unsigned int *hor = new unsigned int(1);

public:
    ClavierVariables(QWidget* parent = nullptr);
public slots:
    /**
     * @brief : Masque le clavier variable
     * @param : (int) Etat du clavier
     */
    void minimize1(int state);
    /**
     * @brief : Ajoute un bouton programme ou variable au clavier
     * @param : (QString&) Nom du bouton
     */
    void ajoutBouton(const QString& nom);
};
#endif // CLAVIERVARIABLES_H
