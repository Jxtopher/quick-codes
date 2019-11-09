/// 
/// @file sparseTimeSerie.hpp
/// @author Jxtopher
/// @brief 
/// @version 0.1
/// @date 2019-11-09
/// 
/// @copyright Copyright (c) 2019
/// 
///

#include <iostream>
#include <map>

#include "timeSerie.hpp"

template <typename TYPE_VALUES>
class SparseTimeSerie : public TimeSerie {
public:
    SparseTimeSerie(unsigned int size, TYPE_VALUES defaultValue) : _size(size) {
        _values[0] = defaultValue;
    }

    TYPE_VALUES operator()(const unsigned int t) const {
        if (_size < t) {
            std::cout<<"_size < t"<<std::endl;
            exit(0);
        }

        if (_values.find(t) != _values.end()) { // Key found
            return _values.at(t);
        } else { // Key not found
            unsigned int index = 0;

            if (_values.size() == 1) return _values.at(0);

            for (typename std::map<unsigned int, TYPE_VALUES>::const_iterator it=_values.begin(); it!=_values.end(); ++it)
                if (t < it->first) return _values.at((--it)->first);
                
            return (--_values.end())->second;
        }
    }

    void operator()(const unsigned int t, const TYPE_VALUES value) {
        if (_values.find(t) == _values.end()) { // Key found
            TYPE_VALUES tmp = this->operator()(t);

            _values[t] = value;
            if (_values.find(t+1) == _values.end())// Key not found 
                _values[t+1] = tmp;
        } else// Key not found
            _values[t] = value;
    }

    unsigned int size() const {
        return _size;
    }

    friend std::ostream& operator<<(std::ostream& os, const SparseTimeSerie<TYPE_VALUES>& sparseTimeSerie) {
        for (typename std::map<unsigned int, TYPE_VALUES>::const_iterator it = sparseTimeSerie._values.begin(); it != sparseTimeSerie._values.end(); ++it) 
            os << it->first << " => " << it->second << '\n';
        return os;
    }


private:
    std::map<unsigned int, TYPE_VALUES> _values;
    unsigned int _size;
};
