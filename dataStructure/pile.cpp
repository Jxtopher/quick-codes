#include <cstdlib>
#include <cassert>
#include <iostream>


// Définir un class Pile avec les fonction push, pop, isEmpty, size
// Mettre en place une gestion dynamique de la mémoire
// Définir les constructeurs de copie et l'opérateur égale

using namespace std;

template<class TYPE>
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
            data = (TYPE *) realloc (data, p.nbElementMax * sizeof(TYPE));
        
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

    bool operator!=(const Pile &p) const {
        return not(operator==(p));
    }

    void push(TYPE element) {
        if (nbElement == nbElementMax) {
            nbElementMax += 10;
            data = (TYPE *) realloc (data, nbElementMax * sizeof(TYPE));
            data[nbElement] = element;
            nbElement++;
        } else {
            data[nbElement] = element;
            nbElement++;
        }
    }

    TYPE pop() {
        if (nbElement == 0) {
            assert(nbElement != 0);
        }
        if (delta < (nbElementMax - nbElement)) {
            // Liberation de la mémoire
            nbElementMax -= 10;
            data = (TYPE *) realloc (data, nbElementMax * sizeof(TYPE));
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
    unsigned int nbElementMax;
    unsigned int nbElement;
    unsigned int delta;
    TYPE *data;
};

class UnitTest_pile  {
    public:
        UnitTest_pile() {
            p = new Pile<unsigned int>;
        }

        virtual ~UnitTest_pile() {
            delete p;
        }

        void run() {
            run1();
            run2(200000);
            run3(200000);
            run4(200000);
        }

        void run1() {
            unsigned int a = 5;
            p->push(a);
            assert(p->isEmpty() == false);

            unsigned int b = p->pop();
            assert(b == a);
        }

        void run2(unsigned int size) {
            for (unsigned int i = 0 ; i < size ; i++)
                p->push(i);
            
            assert(p->size() == size);
            
            for (unsigned int i = size ; 0 < i  ; i--)
                assert(p->pop() == (i - 1));
            
            assert(p->isEmpty() == true);
        }

        void run3(unsigned int size) {
            Pile<unsigned int> p1;
            Pile<unsigned int> p2;

            for (unsigned int i = 0 ; i < size ; i++)
                p1.push(i);

            p2 = p1;
            assert(p2 == p1);
            assert(not(p2 != p1));
            for (unsigned int i = size ; 0 < i  ; i--)
                assert(p1.pop() == p2.pop());
        }

        void run4(unsigned int size) {
            Pile<unsigned int> p1;
            

            for (unsigned int i = 0 ; i < size ; i++)
                p1.push(i);

            Pile<unsigned int> p2(p1);
            assert(p2 == p1);
            for (unsigned int i = size ; 0 < i  ; i--)
                assert(p1.pop() == p2.pop());
        }

    protected:
        Pile<unsigned int> *p;
};


int main() {//int argc, char **argv, char **envp) {
    UnitTest_pile unitTest_pile;
    unitTest_pile.run();

    return EXIT_SUCCESS;
}
