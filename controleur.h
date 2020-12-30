#ifndef _CONTROLEUR_H
#define _CONTROLEUR_H

#include <vector>
#include <string>
#include <memory>
#include "parse.h"
#include <stack>
#include "litterale.h"
#include <QString>
#include <QObject>


class Pile : public QObject {
    Q_OBJECT

    std::vector<std::shared_ptr<Operande>> contenu;
    size_t nbAffiche;
    QString message;
public:
    Pile() : nbAffiche(0), message("") {}
    virtual ~Pile() = default;
    void affiche() const;
    void push(std::shared_ptr<Operande> op);
    std::shared_ptr<Operande> pop();
    bool estVide() const;
    size_t taille() const;
    void clear();
    std::shared_ptr<Operande> top() const;
    void setMessage(const QString& m);
    QString getMessage() const;
    void setNbItemsToAffiche(size_t n);
    // iterator
    std::vector<std::shared_ptr<Operande>>::const_iterator begin() const { return contenu.begin(); }
    std::vector<std::shared_ptr<Operande>>::const_iterator end() const { return contenu.end(); }

signals:
    void modificationEtat();
};

class Controleur {

    Controleur() = default;
    static Controleur* instanceUnique;
    virtual ~Controleur();
public :
    Pile pile;
    void exec(std::string s);
    static Controleur& donneInstance();
    static void libereInstance();
    /**
     * @brief Suppression du constructeur de recopie.
     */
    Controleur(const Controleur&) = delete;
    /**
     * @brief Suppression de l'opérateur de recopie.
     */
    void operator=(const Controleur&) = delete;
};




// fonctions utiles pour le parsage et la reconnaissance des types

bool isExpression(std::string s);

bool isRationnel(std::string s);

bool isReel(std::string s);

bool isEntier(std::string s);


#endif
