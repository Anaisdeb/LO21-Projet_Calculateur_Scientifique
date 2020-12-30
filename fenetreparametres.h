#ifndef FENETREPARAMETRES_H
#define FENETREPARAMETRES_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QSpinBox>

class FenetreParametres : public QWidget
{
    Q_OBJECT

private:
    // ATTRIBUTS
    static unsigned int nbLignesPile;
    static QString nomUtilsateur;

    // WIDGETS
    QLineEdit* infoUtilisateur;
    QLineEdit* nom;
    QSpinBox* nb;
    QVBoxLayout* mainLayout;

    // METHODES
    /**
     * @brief : Construire à l'aide de widgets la fenêtre à afficher
     */
    void buildWindow();

    /**
     * @brief : Initialiser les attributs avec les valeurs de la BDD
     */
    void setDataBaseData();

    /**
     * @brief : Créer la table 'parametres' si elle n'existe pas
     */
    void dataBaseInit();

public:
    /**
     * @brief : Constructeur
     */
    explicit FenetreParametres(QWidget *parent = nullptr);

    // GETTERS
    /**
     * @brief : Retourner le nombre d'items de la pile à afficher
     * @return : Attribut nbLignesPile
     */
    static unsigned int getNbLignesPiles() { return  nbLignesPile; }

    /**
     * @brief : Retourner le nom de l'utilisateur
     * @return : Attribut nomUtilisateur
     */
    static QString getNomUtilisateur() { return nomUtilsateur; }

    // SETTERS
    /**
     * @brief : Modifier la valeur de l'attribut nbLignesPile
     * @param : (int) nouvelle valeur de l'attribut
     */
    static void setNbLignesPiles(unsigned int val) { nbLignesPile = val; }

    /**
     * @brief : Modifier la valeur de l'attribut nomUtilisateur
     * @param : (QString) nouvelle valeur de l'attribut
     */
    static void setNomUtilisateur(QString nom)  { nomUtilsateur = nom; }



public slots:
    void actuNom(const QString&);
    void actuNb(int);
};

#endif // FENETREPARAMETRES_H
