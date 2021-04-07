#ifndef Litt_H
#define Litt_H


#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <memory>

class Operande {
    /**
     * @brief redéfinission de l'opérateur toString
     */
public:
    virtual std::string toString() const = 0;
};

/**
 * @brief La classe Litterale
 */
class Litterale : public Operande{
public:
    virtual ~Litterale() = default;
    std::string toString()const= 0;
    virtual void eval();
};

class LittExpression : public Litterale , public std::enable_shared_from_this<LittExpression>{
    std::string val;
public:
    /**
     * @brief Constructeur de litteralleEntiere.
     * @param v Expression en paramètre.
     */
    LittExpression(std::string v = ""): val(v){};
    /**
     * @brief redéfinission de l'opérateur toString
     */
    std::string toString()const override { return("'" + val + "'"); }
    /**
     * @brief Accesseur de l'unique attribut
     */
    std::string getParam()const { return val; };
    /**
     * @brief fonction appellée en cas d'évaluation de l'expression par l'utilisateur (opérateur EVAL)
     */
    void eval();
    /**
     * @brief Création d'atome
     * @param atome l'atome à créer
     */
    void sto(std::shared_ptr<Litterale> atome);
    /**
     * @brief Suppression d'atome
     */
    void forget();
};

class LittProgramme : public Litterale{
    std::string val;
public:
    LittProgramme();
    LittProgramme(std::string s):val(s){};
    /**
     * @brief redéfinission de l'opérateur toString
     */
    std::string toString() const override { return val;};
    /**
     * @brief Accesseur du vecteur d'opérandes
     */
    std::string getParam()const { return val; };
    /**
     * @brief fonction appellée en cas d'évaluation de l'expression par l'utilisateur (opérateur EVAL)
     */
    void eval();
};

/**
 * @brief The LittNumerique class
 */
class LittNumerique : public Litterale{
public:
    /**
     * @brief Methode virtuelle pure qui permet d'avoir la littérale sous sa forme chaine de caracteres.
     * @return Une reference vers la chaine de caracteres
     */
    virtual std::string toString()const = 0;
    /**
     * @brief Methode virtuelle pure qui redefinie l'operation + pour effectuer cette operation entre les litterales
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    virtual std::shared_ptr<LittNumerique> operator+(LittNumerique& l) = 0;
    /**
     * @brief Methode virtuelle pure qui redefinie l'operation * pour effectuer cette operation entre les litterales
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    virtual std::shared_ptr<LittNumerique> operator*(LittNumerique& l) = 0;
    /**
     * @brief Methode virtuelle pure qui redefinie l'operation - pour effectuer cette operation entre les litterales
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    virtual std::shared_ptr<LittNumerique> operator-(LittNumerique& l) = 0;
    /**
     * @brief Methode virtuelle pure qui redefinie l'operation / pour effectuer cette operation entre les litterales.
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération.
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat.
     */
    virtual std::shared_ptr<LittNumerique> operator/(LittNumerique& l) = 0;

    virtual ~LittNumerique() = default;
    /**
     * @brief Méthode virtuelle qui permet de simplifier des litérale, par défault elle ne fait rien.
     */
    virtual void simplifier(){};
    /**
     * @brief Méthode virtuelle permettant de calculer l'opposer d'une litterale numerqiue
     */
    virtual void neg() = 0;
    /**
     * @brief Methode virtuelle pure qui renvoie la valeur correspondant à la littérale (utile pour les comparaisons)
     * @return la valeur en type double
     */
    virtual double getVal() const = 0;
    /**
     * @brief Methode virtuelle qui calcul le reste d'une division entiere, (utile pour les littérales entières)
     * @return Un pointeur intelligent vers une littérale numérique entiere contenant le resultat.
     */
    virtual std::shared_ptr<LittNumerique> mod(LittNumerique&){return nullptr;}
    /**
     * @brief Calcul le quotien d'une division entiere, (utile pour les littérales entières)
     * @return Un pointeur intelligent vers une littérale numérique entiere contenant le resultat.
     */
    virtual std::shared_ptr<LittNumerique> div(LittNumerique&){return nullptr;}
    /**
     * @brief Redefinition de l'operator == pour tester l'egalité de 2 litterales numeriques
     * @param l
     * @return Un pointeur intelligent vers une littérale numérique entiere contenant le resultat (1 si vrai 0 sinon).
     */
    virtual std::shared_ptr<LittNumerique> operator==(LittNumerique& l);
    /**
     * @brief Redefinition de l'operator != pour tester l'inegalite de 2 litterales numeriques
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération.
     * @return Un pointeur intelligent vers une littérale numérique entiere contenant le resultat (1 si vrai 0 sinon).
     */
    virtual std::shared_ptr<LittNumerique> operator!=(LittNumerique& l);
    /**
     * @brief Redefinition de l'operator < pour tester si une litterale numerique est inferieur à une autre
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération.
     * @return Un pointeur intelligent vers une littérale numérique entiere contenant le resultat (1 si vrai 0 sinon).
     */
    virtual std::shared_ptr<LittNumerique> operator<(LittNumerique& l);
    /**
     * @brief Redefinition de l'operator > pour tester si une litterale numerique est superieure à une autre
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération.
     * @return Un pointeur intelligent vers une littérale numérique entiere contenant le resultat (1 si vrai 0 sinon).
     */
    virtual std::shared_ptr<LittNumerique> operator>(LittNumerique& l);
    /**
     * @brief Redefinition de l'operator <= pour tester si une litterale numerique est inferieur ou egale à une autre
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération.
     * @return Un pointeur intelligent vers une littérale numérique entiere contenant le resultat (1 si vrai 0 sinon).
     */
    virtual std::shared_ptr<LittNumerique> operator<=(LittNumerique& l);
    /**
     * @brief Redefinition de l'operator >= pour tester si une litterale numerique est superieur ou egale à une autre
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération.
     * @return Un pointeur intelligent vers une littérale numérique entiere contenant le resultat (1 si vrai 0 sinon).
     */
    virtual std::shared_ptr<LittNumerique> operator>=(LittNumerique& l);
    virtual std::shared_ptr<LittNumerique> NOT();
    virtual std::shared_ptr<LittNumerique> AND(LittNumerique& l);
    virtual std::shared_ptr<LittNumerique> OR(LittNumerique& l);
};

/**
 * @brief The LittEntiere class
 */
class LittEntiere : public LittNumerique{
    int val;
public:
    /**
     * @brief Constructeur de litteralleEntiere.
     * @param v Entier en paramètre.
     */
    LittEntiere(int v = 0): val(v){};
    /**
     * @brief Destructeur de la classe.
     */
    virtual ~LittEntiere() {/*std::cout<< "dest ent";*/};
    /**
     * @brief Redefinition de la methode afficher qui permet d'avoir la littérale sous sa forme chaine de caracteres.
     * @return Référence sur une chaine de caracteres.
     */
    std::string toString()const override;
    /**
     * @brief Accesseur de l'unique attribut
     * @return
     */
    int getParam()const {return val;};
    double getVal()const override;
    /**
     * @brief Redefinition de l'operator+, permettant d'additioner la litterale entiere avec nimporte quelle autre litterale numerique
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator+(LittNumerique& l) override;
    /**
     * @brief Redefinition de l'operator*, permettant de multiplier une litterale entiere avec nimporte quelle autre litterale numerique
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator*(LittNumerique& l) override;
    /**
     * @brief Redefinition de l'operator-, permettant de soustraire une litterale entiere avec nimporte quelle autre litterale numerique
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator-(LittNumerique& l) override;
    /**
     * @brief Redefinition de l'operator/, permettant de diviser une litterale entiere par nimporte quelle autre litterale numerique
     * @returnUn pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator/(LittNumerique& l) override;
    /**
     * @brief Methode permettant de faire passer une litterale entiere vers son opposé.
     */
    void neg() override;
    /**
     * @brief Implementation de la division entiere, cette methode calcul le reste.
     * @return Reste de la division entiere.
     */
    std::shared_ptr<LittNumerique> mod(LittNumerique& l) override;
    /**
     * @brief Implementation de la division entiere, cette methode calcul le quotient.
     * @return Quotient de la divion entiere.
     */
    std::shared_ptr<LittNumerique> div(LittNumerique& l) override;



};
/**
 * @brief The LittReelle class
 */
class LittReelle: public LittNumerique{
    double val;
public:
    /**
     * @brief Constructeur sans argument, par défault la valeur est à 0
     */
    LittReelle(): val(0){};
    /**
     * @brief Constructeur à un argument
     * @param v, double à affecter à la valeur de la littérale
     */
    LittReelle(double v): val(v){};
    virtual ~LittReelle() = default;
    /**
     * @brief Redefinition de la methode afficher qui permet d'avoir la littérale sous sa forme chaine de caracteres.
     * @return Référence sur une chaine de caracteres.
     */
    std::string toString()const override;
    /**
     * @brief getParam
     * @return
     */
    double getParam()const {return val;};
    /**
     * @brief getVal
     * @return
     */
    double getVal()const override;
    /**
     * @brief  Redefinition de l'operator+, permettant d'additionner une litterale reelle avec nimporte quelle autre litterale numerique
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator+(LittNumerique& l) override;
    /**
     * @brief Redefinition de l'operator*, permettant de multiplier une litterale reelle avec nimporte quelle autre litterale numerique
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator*(LittNumerique& l) override;
    /**
     * @brief Redefinition de l'operator-, permettant de soustraire une litterale reelle par nimporte quelle autre litterale numerique
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator-(LittNumerique& l) override;
    /**
     * @brief Redefinition de l'operator-, permettant de diviser une litterale reelle par nimporte quelle autre litterale numerique
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator/(LittNumerique& l) override;
    /**
     * @brief Methode permettant de faire passer une litterale rationnelle vers son opposé.
     */
    void neg() override;
};

/**
 * @brief The LittRationnelle class
 */
class LittRationnelle : public LittNumerique{
    int num;
    int den;
public:
    // LittRationnelle(): num(0), den(1){};
    // LittRationnelle(int n): num(n), den(1){};
    /**
     * @brief Constructeur de la classe LittRationnelle
     * @param n, entier du numerateur.
     * @param d, entier du denominateur.
     */
    LittRationnelle(int n, int d): num(n), den(d){
        if (d == 0) throw("denominateur nul");
        this->simplifier();
    }
    ~LittRationnelle() {/*std::cout<< "dest rat";*/}

    /**
     * @brief Methode permettant de simplifier la fraction à chaque calcul
     */
    void simplifier() override;
    /**
     * @brief Redefinition de la methode afficher qui permet d'avoir la littérale sous sa forme chaine de caracteres.
     * @return Référence sur une chaine de caracteres.
     */
    std::string toString()const override;
    /**
     * @brief Accesseur revoyant le numerateur.
     * @return Un entier correpondant au numerateur.
     */
    int getNumerateur()const {return num;}
    /**
     * @brief Accesseur revoyant le denominateur.
     * @return Un entier correpondant au denominateur.
     */
    int getDenominateur()const {return den;}
    /**
     * @brief getVal()
     * @return Double correspondant à la valeur de la fraction.
     */
    double getVal()const override;
    /**
     * @brief operator +
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator+(LittNumerique& l) override;
    /**
     * @brief operator *
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator*(LittNumerique& l) override;
    /**
     * @brief operator -
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator-(LittNumerique& l) override;
    /**
     * @brief operator /
     * @param l, une reference vers la litterale numérique avec laquelle on veut réaliser l'opération
     * @return Un pointeur intelligent vers une littérale numérique contenant le resultat
     */
    std::shared_ptr<LittNumerique> operator/(LittNumerique& l) override;
    /**
     * @brief Methode permettant de faire passer une litterale rationnelle vers son opposé.
     */
    void neg() override;
};





#endif // Litt_H
