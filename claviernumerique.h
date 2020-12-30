#ifndef CLAVIERNUMERIQUE_H
#define CLAVIERNUMERIQUE_H

#include "fenetrecalculatrice.h"
#include <QWidget>

class ClavierNumerique : public QWidget {
    Q_OBJECT

public:
    ClavierNumerique(QWidget* parent = nullptr);
public slots:
    void minimize2(int state);
};

#endif // CLAVIERNUMERIQUE_H
