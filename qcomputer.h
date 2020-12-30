#ifndef QCOMPUTER_H
#define QCOMPUTER_H

#include <QWidget>
#include <QTabWidget>

class QComputer : public QWidget {
    Q_OBJECT

private:
    QTabWidget *tabWidget;

    /**
     * @brief : Construire à l'aide de widgets la fenêtre à afficher
     */
    void buildWindow();

public:
    /**
     * @brief : Constructeur
     */
    explicit QComputer(QWidget *parent = nullptr);

};

void addDatabaseToManager();

#endif // QCOMPUTER_H
