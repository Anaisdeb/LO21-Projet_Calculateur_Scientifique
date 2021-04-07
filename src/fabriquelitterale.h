#ifndef FABRIQUELITTERALE_H
#define FABRIQUELITTERALE_H

#include "litterale.h"
#include <iostream>
#include <memory>



class FabriqueLitterale
{
    /**
     * @brief Constructeur privé de la fabrique.
     */
    FabriqueLitterale() = default;
public:
    /**
     * @brief Récupération de l'instance du singleton.
     * @return Référence constance sur LiteralFactory.
     */
    static const FabriqueLitterale& donneInstance();
    /**
     * @brief Suppression du constructeur de recopie.
     */
    FabriqueLitterale(const FabriqueLitterale&) = delete;
    /**
     * @brief Suppression de l'opérateur de recopie.
     */
    void operator=(const FabriqueLitterale&) = delete;
    /**
     * @brief Méthode générale de fabrication d'une littérale quelconque à partir d'une chaîne.
     * @details Appels successifs et ordonnées des fonctions référencés par _allocatorsPriority_.
     * @param str Chaîne à parser.
     * @exception invalid_argument Si aucun modèle de fabrique n'a reconnu le format de la chaîne.
     * @return Pointeur sur LittNumerique.
     */
    std::shared_ptr<LittNumerique> makeLitteralFromString(std::string str) const;
    /**
     * @brief Fabrique d'un objet LittEntiere.
     * @param n Entier relatif.
     * @return Pointeur sur LittNumerique.
     */

    std::shared_ptr<LittNumerique> makeLitterale(int n) const;
    /**
     * @brief Fabrique d'un objet LittRationnelle ou LittEntiere si le denominateur vaut 1.
     * @details La classe LittRationnelle s'occupe de simplifier la fraction à chaque fois que celle ci est traitée
     * si le dénominateur vaut 1, la fraction est convertie en entier
     * @param num Entier représentant le numérateur.
     * @param den Entier représentant le dénominateur.
     * @return Pointeur intelligent sur LittNumerique.
     */
    std::shared_ptr<LittNumerique> makeLitterale(int num, int den) const;
    /**
     * @brief Fabrique d'un objet LittReelle ou LittEntiere si la partie après la virgule est nulle.
     * @param v Nombre à virgule flottante.
     * @return Pointeur sur LittNumerique.
     */
    std::shared_ptr<LittNumerique> makeLitterale(double v) const;
    /**
     * @brief Fabrique d'un objet ExpressionLiteral.
     * @param s Chaîne de charactère.
     * @return Pointeur sur Literal.
     */
    std::shared_ptr<LittExpression> makeLitteraleExpression(const std::string& s) const;
    std::shared_ptr<LittProgramme> makeLitteraleProgramme(const std::string& s) const;

};
#endif // FABRIQUELITTERALE_H
