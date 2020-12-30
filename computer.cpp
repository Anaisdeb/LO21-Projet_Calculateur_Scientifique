/*#include "computer.h"
#include <algorithm>

ExpressionManager::Handler ExpressionManager::handler;

ExpressionManager& ExpressionManager::getInstance(){
    if (handler.instance==nullptr) handler.instance=new ExpressionManager;
    return *handler.instance;
}

void ExpressionManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
}


QString Expression::toString() const {
    return QString::number(value);
}

void ExpressionManager::agrandissementCapacite() {
    Expression** newtab=new Expression*[(nbMax+1)*2];
    for(size_t i=0; i<nb; i++) newtab[i]=exps[i];
    Expression**  old=exps;
    exps=newtab;
    nbMax=(nbMax+1)*2;
    delete old;
}

Expression& ExpressionManager::addExpression(int v){
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Expression(v);
    return *exps[nb-1];
}

void ExpressionManager::removeExpression(Expression& e){
    size_t i=0;
    while(i<nb && exps[i]!=&e) i++;
    if (i==nb) throw ComputerException("elimination d'une Expression inexistante");
    delete exps[i];
    i++;
    while(i<nb) { exps[i-1]=exps[i]; i++; }
    nb--;
}

ExpressionManager::~ExpressionManager(){
    for(size_t i=0; i<nb; i++) delete exps[i];
    delete[] exps;
}

Expression& Item::getExpression() const {
        if (exp==nullptr) throw ComputerException("Item : tentative d'acces a une expression inexistante");
        return *exp;
}


void Pile::agrandissementCapacite() {
    Item* newtab=new Item[(nbMax+1)*2];
    for(size_t i=0; i<nb; i++) newtab[i]=items[i];
    Item*  old=items;
    items=newtab;
    nbMax=(nbMax+1)*2;
    delete[] old;
}

void Pile::push(Expression& e){
    if (nb==nbMax) agrandissementCapacite();
    items[nb].setExpression(e);
    nb++;
    modificationEtat();
}

void Pile::pop(){
    nb--;
    items[nb].raz();
    modificationEtat();
}

void Pile::affiche(QTextStream& f) const{
    f<<"********************************************* \n";
    f<<"M : "<<message<<"\n";
    f<<"---------------------------------------------\n";
    for(size_t i=nbAffiche; i>0; i--) {
        if (i<=nb) f<<i<<": "<<items[nb-i].getExpression().toString()<<"\n";
        else f<<i<<": \n";
    }
    f<<"---------------------------------------------\n";
}


Pile::~Pile(){
    delete[] items;
}

void Pile::Undo() {
    if (this->estVide()) {
        //throw exception
    }
    Expression& save = this->top();
    this->pop();
}



void Pile::Redo() {

}



Expression& Pile::top() const {
    if (nb==0) throw ComputerException("aucune expression sur la pile");
    return items[nb-1].getExpression();
}

bool estUnOperateur(const QString s){
    if (s=="+") return true;
    if (s=="-") return true;
    if (s=="*" || s=="\303\227") return true;
    if (s=="/" || s=="\303\267") return true;
    return false;
}

bool estUnNombre(const QString s){
   bool ok=false;
   s.toInt(&ok);
   return ok;
}


void Controleur::commande(const QString& c){
    if (estUnNombre(c)){
        expAff.push(expMng.addExpression(c.toInt()));
    } else {
        if (estUnOperateur(c)) {
            if (expAff.taille()>=2) {
                int v2=expAff.top().getValue();
                expMng.removeExpression(expAff.top());
                expAff.pop();
                int v1=expAff.top().getValue();
                expMng.removeExpression(expAff.top());
                expAff.pop();
                int res;
                if (c=="+") res=v1+v2;
                if (c=="-") res=v1-v2;
                if (c=="*" || c=="\303\227") res=v1*v2;
                if (c=="/" || c=="\303\267") {
                    if (v2!=0) res=v1/v2;
                    else {
                        expAff.setMessage("Erreur : division par zéro");
                        res=v1;
                    }
                }
                Expression& e=expMng.addExpression(res);
                expAff.push(e);
            }else{
                expAff.setMessage("Erreur : pas assez d'arguments");
            }
        } else expAff.setMessage("Erreur : commande inconnue");
    }
}
*/
