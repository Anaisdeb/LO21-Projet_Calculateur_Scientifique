#ifndef PROJETEXCEPTION_H
#define PROJETEXCEPTION_H


#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

/**
 * @brief Un objet ProjetException représente une exception générée par qcomputer à tout moment du programme.
 */
class ProjetException : public std::exception {

protected:
    /**
     * @brief Informations sur le motif de l'exception.
     */
    std::string info;

public:
    /**
     * @brief Constructeur explicite (ce n'est pas un constructeur de conversion).
     * @param info Information sur l'exception.
     */
    ProjetException(const std::string& i = "") noexcept :info(i) {}

    /**
     * @brief Retourne les informations de l'expression.
     * @return Chaîne de caractères C.
     */
    const char* what() const noexcept { return info.c_str(); }

    ~ProjetException()noexcept {}
};

#endif // PROJETEXCEPTION_H
