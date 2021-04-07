#include "litterale.h"
#include <string>
#include <iostream>
#include "fabriquelitterale.h"
#include "Controleur.h"
#include "Manager.h"
#include <typeinfo>

void LittExpression::eval(){
    Manager::getInstance().GetAtome(val)->eval();
}

void LittExpression::sto(std::shared_ptr<Litterale> atome){
    Manager::getInstance().AddAtome(shared_from_this() , atome);
}

void LittExpression::forget(){
    //std::cout<<typeid(shared_from_this()).name() <<std::endl;
    Manager::getInstance().ForgetAtome(getParam());
}

void LittProgramme::eval(){
    Controleur::donneInstance().exec(val.substr(1,val.length()-2));
}

void Litterale::eval(){
    Controleur::donneInstance().exec(toString());
}

// part II

void LittRationnelle::simplifier(){
    int a=num, b=den;
    // on ne travaille qu’avec des valeurs positives...
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while(a != b){
        if (a > b) a = a-b;
        else b = b-a;

    }
    // on divise le numerateur et le denominateur par le PGCD=a
    num/=a; den/=a;
    // si le denominateur est négatif, on fait passer le signe - au numérateur
    if (den<0) { den=-den; num=-num; }
}

// **************************************************
// definition des methodes aficher pour chaque classe
// **************************************************

std::string LittRationnelle::toString()const{
    std::string s;
    s = std::to_string(getNumerateur())+ "/" + std::to_string(this->getDenominateur());
    return s;
}

std::string LittReelle::toString()const{
    std::string s;
    s = std::to_string(getParam());
    size_t i =s.length();
    while(s[i-1] == '0'){
        i--;
    }
    s.erase(i,s.length()-i );
    if (s[0] == '0')
        s.erase(0, 1);
    else if (s[0] == '-' && s[1] =='0')
        s.erase(1, 1);
    return s;
}

std::string LittEntiere::toString()const{
    std::string s ;
    s = std::to_string(getParam());
    return s;
}


// *************************************************************
// Définition des opérateurs pour la classe LittRationnelle
// *************************************************************

std::shared_ptr<LittNumerique> LittRationnelle::operator+(LittNumerique& l){
    std::shared_ptr<LittNumerique> result = nullptr;
    LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
    LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
    LittReelle* ree = dynamic_cast<LittReelle*>(&l);
    if(ent!=0){
        LittRationnelle temp = LittRationnelle(num + ent->getParam() * den, den);
        temp.simplifier();
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getNumerateur(), temp.getDenominateur());
    }
    else if(rat != 0){
        auto temp = LittRationnelle(num * rat->getDenominateur() + rat->getNumerateur() * den, den * rat->getDenominateur());
        temp.simplifier();
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getNumerateur(), temp.getDenominateur());
    }
    else if(ree != 0){
        auto temp = LittReelle(this->getVal() + ree->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    return result;
};

std::shared_ptr<LittNumerique> LittRationnelle::operator-(LittNumerique& l){
    std::shared_ptr<LittNumerique> result = nullptr;
    LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
    LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
    LittReelle* ree = dynamic_cast<LittReelle*>(&l);
    if(ent!=0){
        auto temp = LittRationnelle(num - ent->getParam() * den, den);
        temp.simplifier();
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getNumerateur(), temp.getDenominateur());
    }
    else if(rat != 0){
        auto temp = LittRationnelle(num * rat->getDenominateur() - rat->getNumerateur() * den, den * rat->getDenominateur());
        temp.simplifier();
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getNumerateur(), temp.getDenominateur());
    }
    else if(ree != 0){
        auto temp = LittReelle(this->getVal() - ree->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    return result;
};

std::shared_ptr<LittNumerique> LittRationnelle::operator*(LittNumerique& l){
    std::shared_ptr<LittNumerique> result = nullptr;
    LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
    LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
    LittReelle* ree = dynamic_cast<LittReelle*>(&l);
    if(ent!=0){
        auto temp = LittRationnelle(num * ent->getParam(), den);
        temp.simplifier();
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getNumerateur(), temp.getDenominateur());
    }
    else if(rat != 0){
        auto temp =  LittRationnelle(num * rat->getNumerateur(), den * rat->getDenominateur());
        temp.simplifier();
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getNumerateur(), temp.getDenominateur());
    }
    else if(ree != 0){
        auto temp = LittReelle(this->getVal() * ree->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    return result;
};

std::shared_ptr<LittNumerique> LittRationnelle::operator/(LittNumerique& l){
    std::shared_ptr<LittNumerique> result = nullptr;
    LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
    LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
    LittReelle* ree = dynamic_cast<LittReelle*>(&l);
    if(ent!=0){
        auto temp = LittRationnelle(num / ent->getParam(), den);
        temp.simplifier();
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getNumerateur(), temp.getDenominateur());
    }
    else if(rat != 0){
        auto temp =LittRationnelle(num * rat->getDenominateur(), den * rat->getNumerateur());
        temp.simplifier();
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getNumerateur(), temp.getDenominateur());
    }
    else if(ree != 0){
        auto temp = LittReelle(this->getVal() / ree->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    return result;
};

// ********************************************************
// Définition des opérateurs pour la classe LittReelle
// ********************************************************

std::shared_ptr<LittNumerique> LittReelle::operator+(LittNumerique& l){
    std::shared_ptr<LittNumerique> result = nullptr;
    LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
    LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
    LittReelle* ree = dynamic_cast<LittReelle*>(&l);
    if(rat !=0){
        // comme a+b = b+a et que cette opération est déja définie, pas besoin de le refaire
        result = (*rat)+(*this);
        return result;
    }
    else if (ent !=0){
        auto temp = LittReelle(this->getParam() + ent->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    else if (ree !=0){
        auto temp = LittReelle(this->getParam() + ree->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    return result;
}

std::shared_ptr<LittNumerique> LittReelle::operator-(LittNumerique& l){
    std::shared_ptr<LittNumerique> result = nullptr;
    LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
    LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
    LittReelle* ree = dynamic_cast<LittReelle*>(&l);
    if(rat !=0){
        // comme a+b = b+a et que cette opération est déja définie, pas besoin de le refaire
        result = (*rat)-(*this);
        return result;
    }
    else if (ent !=0){
        auto temp = LittReelle(this->getParam() - ent->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    else if (ree !=0){
        auto temp = LittReelle(this->getParam() - ree->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    return result;
}

std::shared_ptr<LittNumerique> LittReelle::operator*(LittNumerique& l){
    std::shared_ptr<LittNumerique> result = nullptr;
    LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
    LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
    LittReelle* ree = dynamic_cast<LittReelle*>(&l);
    if(rat !=0){
        // comme a+b = b+a et que cette opération est déja définie, pas besoin de le refaire
        result = (*rat)*(*this);
        return result;
    }
    else if (ent !=0){
        auto temp = LittReelle(this->getParam() * ent->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    else if (ree !=0){
        auto temp = LittReelle(this->getParam() * ree->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    return result;
}

std::shared_ptr<LittNumerique> LittReelle::operator/(LittNumerique& l){
    std::shared_ptr<LittNumerique> result = nullptr;
    LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
    LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
    LittReelle* ree = dynamic_cast<LittReelle*>(&l);
    if(rat !=0){
        // comme a+b = b+a et que cette opération est déja définie, pas besoin de le refaire
        result = (*rat)/(*this);
        return result;
    }
    else if (ent !=0){
        auto temp =  LittReelle(this->getParam() / ent->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    else if (ree !=0){
        auto temp =  LittReelle(this->getParam() / ree->getParam());
        return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
    }
    return result;
}

// *********************************************************
// Définition des opérateurs pour la classe LittEntiere
// *********************************************************

std::shared_ptr<LittNumerique> LittEntiere::operator+(LittNumerique& l){
        std::shared_ptr<LittNumerique> result = nullptr;
        LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
        LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
        LittReelle* ree = dynamic_cast<LittReelle*>(&l);
        if(rat !=0){
            // comme a+b = b+a et que cette opération est déja définie, pas besoin de le refaire
            result = (*rat)+(*this);
            return result;
        }
        else if (ent !=0){
            auto temp = LittEntiere(this->getParam() + ent->getParam());
            return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
        }
        else if (ree !=0){
            result = (*ree)+(*this);
            return result;
        }
        return result;
    }

std::shared_ptr<LittNumerique> LittEntiere::operator-(LittNumerique& l){
        std::shared_ptr<LittNumerique> result = nullptr;
        LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
        LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
        LittReelle* ree = dynamic_cast<LittReelle*>(&l);
        if(rat !=0){
            // comme a+b = b+a et que cette opération est déja définie, pas besoin de le refaire
            result = (*rat)-(*this);
            return result;
        }
        else if (ent !=0){
            auto temp = LittEntiere(this->getParam() - ent->getParam());
            return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
        }
        else if (ree !=0){
            auto temp =  LittReelle(this->getParam() - ree->getParam());
            return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
        }
        return result;
    }

std::shared_ptr<LittNumerique> LittEntiere::operator*(LittNumerique& l){
        std::shared_ptr<LittNumerique> result = nullptr;
        LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
        LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
        LittReelle* ree = dynamic_cast<LittReelle*>(&l);
        if(rat !=0){
            // comme a+b = b+a et que cette opération est déja définie, pas besoin de le refaire
            result = (*rat)*(*this);
            return result;
        }
        else if (ent !=0){
            auto temp = LittReelle(this->getParam() * ent->getParam());
            return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
        }
        else if (ree !=0){
            result = (*ree)*(*this);
            return result;
        }
        return result;
    }

std::shared_ptr<LittNumerique> LittEntiere::operator/(LittNumerique& l){
        std::shared_ptr<LittNumerique> result = nullptr;
        LittRationnelle* rat = dynamic_cast<LittRationnelle*>(&l);
        LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
        LittReelle* ree = dynamic_cast<LittReelle*>(&l);
        if(rat !=0){
            // comme a+b = b+a et que cette opération est déja définie, pas besoin de le refaire
            result = (*rat)/(*this);
            return result;
        }
        else if (ent !=0){
            auto temp= LittRationnelle(this->getParam(),ent->getParam());
            return FabriqueLitterale::donneInstance().makeLitterale(temp.getNumerateur(), temp.getDenominateur());
        }
        else if (ree !=0){
            auto temp= LittReelle(this->getParam() / ree->getParam());
            return FabriqueLitterale::donneInstance().makeLitterale(temp.getParam());
        }
        return result;
    }

// ***************************
// définition des méthodes neg
// ***************************

void LittRationnelle::neg(){
    num = -num;
}
void LittReelle::neg(){
    val = -val;
}

void LittEntiere::neg(){
    val = -val;
}

// ***********************************************************
// définition des méthodes div et mod pour la division entiere
// ***********************************************************

std::shared_ptr<LittNumerique> LittEntiere::mod(LittNumerique& l){
    LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
    //return LittEntiere(this->getParam() % e.getParam());
    if(ent !=0){
        int reste = this->getParam() % ent->getParam();
        return FabriqueLitterale::donneInstance().makeLitterale(reste);
    }
    else{
        std::shared_ptr<LittNumerique> res = nullptr;
        return res;
    }

}

std::shared_ptr<LittNumerique> LittEntiere::div(LittNumerique& l){
    // conversion implicite vers un entier soit le quotient de la divion entière
    LittEntiere* ent = dynamic_cast<LittEntiere*>(&l);
    if(ent !=0){
        int quotient = this->getParam() / ent->getParam();
        return FabriqueLitterale::donneInstance().makeLitterale(quotient);
    }
    else{
        std::shared_ptr<LittNumerique> res = nullptr;
        return res;
    }
}

double LittEntiere::getVal()const{
    return getParam();
}
double LittRationnelle::getVal()const{
    auto n = static_cast<double>(num);
    auto d = static_cast<double>(den);
    return n/d;
}
double LittReelle::getVal()const{
    return getParam();
}

std::shared_ptr<LittNumerique> LittNumerique::operator==(LittNumerique& l){
    if(this->getVal() == l.getVal())
        return FabriqueLitterale::donneInstance().makeLitterale(1);
    else
        return FabriqueLitterale::donneInstance().makeLitterale(0);
}

std::shared_ptr<LittNumerique> LittNumerique::operator!=(LittNumerique& l){
    if(this->getVal() != l.getVal())
        return FabriqueLitterale::donneInstance().makeLitterale(1);
    else
        return FabriqueLitterale::donneInstance().makeLitterale(0);
}
std::shared_ptr<LittNumerique> LittNumerique::operator<(LittNumerique& l){
    if(this->getVal() < l.getVal())
        return FabriqueLitterale::donneInstance().makeLitterale(1);
    else
        return FabriqueLitterale::donneInstance().makeLitterale(0);
}

std::shared_ptr<LittNumerique> LittNumerique::operator>(LittNumerique& l){
    if(this->getVal() > l.getVal())
        return FabriqueLitterale::donneInstance().makeLitterale(1);
    else
        return FabriqueLitterale::donneInstance().makeLitterale(0);
}

std::shared_ptr<LittNumerique> LittNumerique::operator>=(LittNumerique& l){
    if(this->getVal() >= l.getVal())
        return FabriqueLitterale::donneInstance().makeLitterale(1);
    else
        return FabriqueLitterale::donneInstance().makeLitterale(0);
}

std::shared_ptr<LittNumerique> LittNumerique::operator<=(LittNumerique& l){
    if(this->getVal() <= l.getVal())
        return FabriqueLitterale::donneInstance().makeLitterale(1);
    else
        return FabriqueLitterale::donneInstance().makeLitterale(0);
}

std::shared_ptr<LittNumerique> LittNumerique::NOT(){
    if(this->getVal() !=0)
        return FabriqueLitterale::donneInstance().makeLitterale(0);
    else
        return FabriqueLitterale::donneInstance().makeLitterale(1);
}
std::shared_ptr<LittNumerique> LittNumerique::AND(LittNumerique& l){
    if((this->getVal() * l.getVal()) != 0)
        return FabriqueLitterale::donneInstance().makeLitterale(1);
    else
        return FabriqueLitterale::donneInstance().makeLitterale(0);
}
std::shared_ptr<LittNumerique> LittNumerique::OR(LittNumerique& l){
    if((this->getVal() + l.getVal()) != 0)
        return FabriqueLitterale::donneInstance().makeLitterale(1);
    else
        return FabriqueLitterale::donneInstance().makeLitterale(0);
}
