//!
//! \file pile.h
//! \author *
//! \version *
//! \date *
//! \brief Définir une classe Pile avec les fonction push, pop, isEmpty, size
//!        Mettre en place une gestion dynamique de la mémoire
//!        Définir les constructeurs de copie et l'opérateur égale
//!

#ifndef JXTOPHER_PILE_H
#define JXTOPHER_PILE_H

#include <cstdlib>
#include <cassert>
#include <iostream>

#include "macro.h"

using namespace std;

namespace jxtopher {

template<class TYPE>
//!
//! \class Pile
//! \brief Définition de la structure pile
//!
class Pile {
    public:
    Pile() {
        data = new TYPE[0];
        nbElementMax = 0;
        nbElement = 0;
        delta = 30;
    }

    virtual ~Pile() {
        delete data;
    }

    Pile(Pile const &p) {
        nbElementMax = p.nbElementMax;
        nbElement = p.nbElement;
        delta = p.delta;
        data = new TYPE[nbElementMax];
        for (unsigned int i = 0 ; i < nbElementMax ; i++) {
            data[i] = p.data[i];
        }
    }

    Pile & operator=(const Pile  &p) {
        if (nbElementMax != p.nbElementMax)
            data = static_cast<TYPE *>( realloc (data, p.nbElementMax * sizeof(TYPE)));
       
        nbElementMax = p.nbElementMax;
        nbElement = p.nbElement;
        delta = p.delta;
        for (unsigned int i = 0 ; i < nbElementMax ; i++) {
            data[i] = p.data[i];
        }
    }

    bool operator==(const Pile  &p) const {
        if (p.size() != size())
            return false;
        
        for (unsigned int i = 0 ; i < size() ; i++) {
            if (p.data[i] != data[i])
                return false;
        }
        return true;
    }

    /*!
     *  \brief Comparer deux piles
     *
     *  Méthode qui permet de comparer deux piles
     *
     *  \param p : une pile
     *  \return true si la pile A est differant a la pile B,
     *  false sinon
     */
    bool operator!=(const Pile &p) const {
        return not(operator==(p));
    }

    void push(TYPE element) {
        if (nbElement == nbElementMax) {
            nbElementMax += 10;
            data = static_cast<TYPE *>( realloc (data, nbElementMax * sizeof(TYPE)));
            data[nbElement] = element;
            nbElement++;
        } else {
            data[nbElement] = element;
            nbElement++;
        }
    }

    TYPE pop() {
        if (nbElement == 0) {
            THROW("nbElement == 0")
        }
        if (delta < (nbElementMax - nbElement)) {
            // Liberation de la mémoire
            nbElementMax -= 10;
            data = static_cast<TYPE *>( realloc (data, nbElementMax * sizeof(TYPE)));
        }
        nbElement--;
        return data[nbElement];
    }

    bool isEmpty() const {
        if (nbElement == 0)
            return true;
        else 
            return false;
    }

    unsigned int size() const {
        return nbElement;
    }

    protected:
    unsigned int nbElementMax;  //!< Maximum number of elements in the stack 
    unsigned int nbElement;     //!< Number of elements in the stack 
    unsigned int delta;         //!< Size of the stack enlargement
    TYPE *data;                 //!< stack data
};

#endif

}
