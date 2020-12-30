#ifndef CLAVIERVARIABLES_H
#define CLAVIERVARIABLES_H

#include <QWidget>
#include <QGridLayout>

class ClavierVariables : public QWidget {
    Q_OBJECT

    QGridLayout* varLayout;
       unsigned int *ver = new unsigned int(6);
       unsigned int *hor = new unsigned int(3);

public:
    ClavierVariables(QWidget* parent = nullptr);
public slots:
    void minimize1(int state);
    void ajoutBouton(const QString& nom);
};
#endif // CLAVIERVARIABLES_H
