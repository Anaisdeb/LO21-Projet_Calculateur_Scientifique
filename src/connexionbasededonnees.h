#ifndef CONNEXIONBASEDEDONNEES_H
#define CONNEXIONBASEDEDONNEES_H

#include <QString>
#include <QtSql>

class ConnexionBaseDeDonnees
{
private:
    ~ConnexionBaseDeDonnees();
    ConnexionBaseDeDonnees();
    ConnexionBaseDeDonnees(const ConnexionBaseDeDonnees&) = delete;
    ConnexionBaseDeDonnees& operator=(const ConnexionBaseDeDonnees&) = delete;
    QSqlDatabase db;

    /**
     * @brief dataBaseInit : initialiser les tables
     */
    void dataBaseInit();
    /**
     * @brief dataBaseConnect : créer/connecter la base de données
     */
    void dataBaseConnect(QString);

public:
    /**
     * @brief donneInstance : retourner l'instance unique de la classe et la créer si nécessaire
     * @return : l'instance unique de la classe ConnexionBaseDeDonnees
     */
    static ConnexionBaseDeDonnees& donneInstance();
};

#endif // CONNEXIONBASEDEDONNEES_H
