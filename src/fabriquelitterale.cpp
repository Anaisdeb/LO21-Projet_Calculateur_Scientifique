#include "fabriquelitterale.h"
#include <memory>
#include <vector>




const FabriqueLitterale& FabriqueLitterale::donneInstance() {
     static FabriqueLitterale instance; //Libérée automatiquement
     return instance;
}

std::shared_ptr<LittNumerique> FabriqueLitterale::makeLitterale(int n) const{
    return std::make_shared<LittEntiere>(n);
}

std::shared_ptr<LittNumerique> FabriqueLitterale::makeLitterale(int num, int den) const{
    auto temp = LittRationnelle(num,den); // permet d'utiliser la simplification réalisée à la construction de l'objet
    int d = temp.getDenominateur();
    int n = temp.getNumerateur();
    if(d == 1){
        return std::make_shared<LittEntiere>(n);
    }
    else {
        return  std::make_shared<LittRationnelle>(n, d);
    }
}

std::shared_ptr<LittNumerique> FabriqueLitterale::makeLitterale(double v) const{
    int p_ent = static_cast<int>(v);
    if(v-p_ent == 0){
        return std::make_shared<LittEntiere>(p_ent);
    }
    else {
        return std::make_shared<LittReelle>(v);
    }
}

std::shared_ptr<LittExpression> FabriqueLitterale::makeLitteraleExpression(const std::string& s) const{
    return std::make_shared<LittExpression>(s.substr(1, s.length()-2));
}

std::shared_ptr<LittProgramme> FabriqueLitterale::makeLitteraleProgramme(const std::string& s) const{
    return std::make_shared<LittProgramme>(s);
}
