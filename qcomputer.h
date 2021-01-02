#ifndef QCOMPUTER_H
#define QCOMPUTER_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>

class QComputer : public QWidget {
    Q_OBJECT

private:
    QTabWidget *tabWidget;
    QVBoxLayout *mainLayout;

    /**
     * @brief : Construire à l'aide de widgets la fenêtre à afficher
     */
    void buildWindow();

public:

    ~QComputer();
    explicit QComputer(QWidget *parent = nullptr);

};

/**
 * @brief addDatabaseToManager : remplir le manager avec les valeurs contenues dans la BDD
 */
void addDatabaseToManager();

#endif // QCOMPUTER_H
