#ifndef PARSE_H
#define PARSE_H


#include <iostream>
#include <string>
#include <memory>
#include <vector>

bool isLettreMaj(const char x);
bool isChiffre(const char x);
bool isOperateur(const char x);
std::vector<std::string> tdParse(std::string s);

#endif // PARSE_H
