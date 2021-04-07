#include <QString>
#include <QtSql>
#include "connexionbasededonnees.h"

// =============== PUBLIC ===============

ConnexionBaseDeDonnees& ConnexionBaseDeDonnees::donneInstance()
{
    static ConnexionBaseDeDonnees uniqueInstance;
    return uniqueInstance;
}

// =============== PRIVATE ===============

ConnexionBaseDeDonnees::ConnexionBaseDeDonnees()
{
    dataBaseConnect("bdd_comput");
    dataBaseInit();
}

void ConnexionBaseDeDonnees::dataBaseConnect(QString nomBDD)
{
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {

        QDir dbPath;
        QString path = dbPath.currentPath()+ "/" + nomBDD + ".db";
        db = QSqlDatabase::addDatabase(DRIVER);
        db.setDatabaseName(path);

        if(!db.open())
                qWarning() << "ConnexionBaseDeDonnees::dataBaseConnect - ERROR: " << db.lastError().text();
    }
    else
        qWarning() << "ConnexionBaseDeDonnees::dataBaseConnect - ERROR: no driver " << DRIVER << " available";
}

ConnexionBaseDeDonnees::~ConnexionBaseDeDonnees()
{
    db.close();
}

void ConnexionBaseDeDonnees::dataBaseInit()
{
    QSqlQuery query;

    if(!query.exec("CREATE TABLE IF NOT EXISTS parametres (id INTEGER PRIMARY KEY "
                   "AUTOINCREMENT, nbLignesPile VARCHAR(20), nomUtilisateur VARCHAR(20))"))
        qWarning() << "ConnexionBaseDeDonnees::dataBaseInit - ERROR: " << query.lastError().text();

    if(!query.exec("CREATE TABLE IF NOT EXISTS programmes (id INTEGER PRIMARY KEY "
                   "AUTOINCREMENT, nom VARCHAR(20), valeur VARCHAR(20))"))
        qWarning() << "ConnexionBaseDeDonnees::dataBaseInit - ERROR: " << query.lastError().text();

    if(!query.exec("CREATE TABLE IF NOT EXISTS variables (id INTEGER PRIMARY KEY "
                    "AUTOINCREMENT, nom VARCHAR(20), valeur VARCHAR(20))"))
        qWarning() << "ConnexionBaseDeDonnees::dataBaseInit - ERROR: " << query.lastError().text();
}
