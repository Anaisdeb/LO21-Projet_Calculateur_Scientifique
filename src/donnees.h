#ifndef DONNEES_H
#define DONNEES_H

/**
* @brief En-têtes nécessaires aux pointeurs intelligents
*/
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include <sstream>
#include <iterator>
#include <typeinfo>

/**
 * @brief Adaptateur de la classe std::vector.
 */
template <typename T>
class Donnees : public std::vector<T> {
public:
    using std::vector<T>::vector; // classe template vector
};

/**
 * @brief Spécialisation de l'adaptateur de vector pour les pointeurs intelligents.
 */
template <typename T>
class Donnees<std::shared_ptr<T>> : public std::vector<std::shared_ptr<T>> {
public:
    using std::vector<std::shared_ptr<T>>::vector;
};

#endif // DONNEES_H



