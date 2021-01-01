#ifndef CLAVIERNUMERIQUE_H
#define CLAVIERNUMERIQUE_H

#include "fenetrecalculatrice.h"
#include <QWidget>

class ClavierNumerique : public QWidget {
    Q_OBJECT

public:
    ClavierNumerique(QWidget* parent = nullptr);

public slots:
    /**
    * @brief : Masquer le clavier numérique
    * @param : (int) Etat du clavier
    */
    void minimize2(int state);
};

#endif // CLAVIERNUMERIQUE_H
