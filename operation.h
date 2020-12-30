#ifndef OPERATION_H
#define OPERATION_H


#include "litterale.h"
#include "donnees.h"
#include "fabriquelitterale.h"

#include <vector>
#include <functional>
#include <memory>

class Operation : public std::enable_shared_from_this<Operation> {
protected:
    typedef Donnees<std::shared_ptr<Operande>> Operandes;
    typedef Donnees<std::shared_ptr<Litterale>> Generique;
    typedef Donnees<std::shared_ptr<LittEntiere>> Entiers;
    typedef Donnees<std::shared_ptr<LittRationnelle>> Rationnels;
    typedef Donnees<std::shared_ptr<LittReelle>> Reels;
    typedef Donnees<std::shared_ptr<LittNumerique>> Numerique;
    typedef Donnees<std::shared_ptr<LittExpression>> Expressions;
    typedef Donnees<std::shared_ptr<LittProgramme>> Programmes;

public:

    virtual Operandes eval(Operandes) const = 0;

    /**
     * @brief Destructeur virtuel.
     */
    virtual ~Operation() {}
};

/*-----------------OpÈrateurs numÈriques-----------------*/

/**
 * @brief Un objet PlusOperation implÈmente l'opÈration d'addition.
 * @details Les littÈrales supportÈes sont LittRationnelle.
 */
class PlusOperation : public Operation {
public:
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet MulOperation implÈmente l'opÈration de multiplication.
 * @details Les littÈrales supportÈes sont LittRationnelle.
 */
class MulOperation : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet NegOperation implÈmente l'opÈration de nÈgation. (il s'agit de la multiplication par -1)
 * @details Toutes les littÈrales sont supportÈes.
 */
class NegOperation : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet MoinsOperation implÈmente l'opÈration de soustraction (il s'agit de la nÈgation et l'addition).
 * @details Toutes les littÈrales sont supportÈes.
 */
class MoinsOperation : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet DivOperation implÈmente l'opÈration de division (rationnelle)
 * @details Les littÈrales supportÈes sont LittRationnelle.
 */
class DivOperation : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet EntDivOperation implÈmente l'opÈration de division entiËre.
 * @details Les littÈrales supportÈes sont LittEntiere.
 */
class EntDivOperation : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet ModOperation implÈmente l'opÈration de modulo.
 * @details Les littÈrales supportÈes sont LittEntiere.
 */
class ModOperation : public Operation {
    Operandes eval(Operandes dn) const override;
};

/*-----------------OpÈrateurs logiques-----------------*/

/**
 * @brief Un objet EgalOperation implÈmente la relation d'Èquivalence d'ÈgalitÈ.
 * @details Les littÈrales supportÈes sont LittRationnelle.
 */
class EgalOperation : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet NonEgalOperation implÈmente la relation de diffÈrence.
 * @details Les littÈrales supportÈes sont LittRationnelle.
 */
class NonEgalOperation : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet InfOuEgal implÈmente la relation d'ordre infÈrieur ou Ègal.
 * @details Les littÈrales supportÈes sont LittReelle.
 */
class InfOuEgal : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet SupOuEgal implÈmente la relation d'ordre supÈrieur ou Ègal.
 * @details Les littÈrales supportÈes sont LittReelle.
 */
class SupOuEgal : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet Inferieur implÈmente la relation d'ordre strict infÈrieur.
 * @details Les littÈrales supportÈes sont LittReelle.
 */
class Inferieur : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet Superieur implÈmente la relation d'ordre strict supÈrieur.
 * @details Les littÈrales supportÈes sont LittReelle.
 */
class Superieur : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet EtLogique implÈmente l'opÈration logique ET.
 * @details Les littÈrales supportÈes sont LittEntiere.
 */
class EtLogique : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet OuLogique implÈmente l'opÈration logique OU.
 * @details Les littÈrales supportÈes sont LittEntiere.
 */
class OuLogique : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet NonLogique implÈmente l'opÈration logique NOT.
 * @details Les littÈrales supportÈes sont LittEntiere.
 */
class NonLogique : public Operation {
    Operandes eval(Operandes dn) const override;
};

/*-----------------OpÈrateurs programmes-----------------*/

/**
 * @brief Un objet StoOperation enregistre un identificateur rÈfÈrenÁant une Litterale.
 * @details Une Litterale atome doit Ítre fournie entre guillemets pour la faire devenir l'identificateur d'une variable.
 */
class StoOperation : public Operation {
    Operandes eval(Operandes dn) const override;
};

/**
 * @brief Un objet ForgetOperation efface la variable ou le programme associÈ ? l'atome proposÈ en argument.
 */
class ForgetOperation : public Operation {
    Operandes eval(Operandes dn) const override;
};

/*-----------------OpÈrateurs de Manipulation de la pile-----------------*/

/**
 * @brief Un objet DupOperation empile une nouvelle littÈrale identique ? celle du sommet de la pile.
 */
class DupOperation : public Operation {
    Operandes eval(Operandes) const override;
};

/**
 * @brief Un objet DropOperation dÈpile la littÈrale au sommet de la pile.
 */
class DropOperation : public Operation {
    Operandes eval(Operandes) const override;
};

/**
 * @brief Un objet SwapOperation intervertit les deux derniers ÈlÈments empilÈs dans la pile.
 */
class SwapOperation : public Operation {
    Operandes eval(Operandes) const override;
};

class ClearOperation : public Operation {
    Operandes eval(Operandes) const override;
};

/*-----------------OpÈrateurs LitÈralles expressions-----------------*/

/**
 * @brief Un objet Eval Èvalue des littÈrales.
 * @detail Les littÈrales expressions sont parsÈes puis leur contenu est ÈvaluÈ.
 *         Les littÈrales programmes sont exÈcutÈes.
 */
class Eval : public Operation {
    Operandes eval(Operandes dn) const override;
};

/*-----------------OpÈrateurs Conditionnels et de Boucle-----------------*/

/**
 * @brief Un objet IFT implÈmente un test logique binaire. Si la premiËre littÈrale est vraie, la seconde est ÈvaluÈe.
 */
class IFT : public Operation {
    Operandes eval(Operandes dn) const override;
};

#endif // OPERATION_H
