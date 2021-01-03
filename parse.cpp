//
//  Parse.cpp
//  train_project
//
//  Created by Thibaut Grall on 04/12/2020.
//  Copyright © 2020 Thibaut Grall. All rights reserved.
//

#include "parse.h"
#include "projetexception.h"
#include <vector>
using namespace std;

bool isLettreMaj(const char x){
    if (x>='A'&& x<='Z')return true;
    else return false;
}

bool isChiffre(const char x){
    if (x>='0'&& x<='9')return true;
    else return false;
}

bool isOperateur(const char x){
    if (x=='+'||x=='-' ||x=='*' ||x=='/')return true;
    else return false;
}


std::vector<std::string> tdParse(std::string s){
    std::vector<std::string> chaineParse;
    // on découpe sur les espaces
    unsigned int eact = 0;
    unsigned int eprec = -1;
    unsigned int i = 0;
    unsigned int nbProg = 0;
    while(i<=s.length()){
        if(s[i]=='['){ // si début de sous programme
            nbProg++;
            eprec = i;
            while(nbProg != 0){
                i++;
                if (i > s.length()) throw ProjetException("erreur");
                if(s[i]==']') nbProg--;
                if(s[i]=='[') nbProg++;
            }
            eact = i;
            chaineParse.push_back(s.substr(eprec+1-1, eact-eprec+1 ));
            eprec = eact;

        }
        else if(s[i]==' '){ // ou que l'on soit
            eact = i;
            if(eact-eprec>1)
            chaineParse.push_back(s.substr(eprec+1, eact-eprec -1 ));
            eprec = eact;
        }
        else if(i==(s.length()-1)){ // si on est à la fin de la chaine
            eact = i;
            chaineParse.push_back(s.substr(eprec+1, eact-eprec));
            eprec = eact;
        }
        i++;
    }
    return chaineParse;
}
