/// 
/// @file binarySearchTrees.hpp
/// @author Jxtopher
/// @brief En cours...
/// @version 0.1
/// @date 2020-02-22
/// 
/// @copyright Copyright (c) 2020
/// 
///
#ifndef BINARYSEARCHTREES_H
#define BINARYSEARCHTREES_H

#include <iostream>
#include <memory>

#include "node.hpp"

template <typename KEY_TYPE, typename VALUE_TYPE>
class BinarySearchTrees {
    public:
    BinarySearchTrees() : _root(nullptr) {
        
    }

    virtual ~BinarySearchTrees() {

    }

    /// 
    /// @brief retourne True si l'arbre est vide et False sinon
    ///
    bool empty() const {
        return _root == nullptr;
    }

    /// 
    /// @brief insère la key dans a si elle n y figure pas avec ca valeur et ne fait rien sinon
    ///
    void insert(KEY_TYPE key, VALUE_TYPE value) {
        if(empty()) {
            _root = std::make_shared<Node<KEY_TYPE, VALUE_TYPE>>(key, value);
        } else {
            while(true) {
                std::shared_ptr<Node<KEY_TYPE, VALUE_TYPE>> node = _root;
                if (key < node->key()) {
                    if (node->left() != nullptr)
                        node = node->left();
                    else {
                        node->left(std::make_shared<Node<KEY_TYPE, VALUE_TYPE>>(key, value));
                        break;
                    }
                        
                } else {
                    if (node->right() != nullptr)
                        node = node->right();
                    else {
                        node->right(std::make_shared<Node<KEY_TYPE, VALUE_TYPE>>(key, value));
                        break;
                    }
                }
            }
        }
    }

    /// 
    /// @brief 
    ///
    VALUE_TYPE search(KEY_TYPE key) {

    }


    /// 
    /// @brief 
    /// 
    void del(KEY_TYPE key) {

    }

    private:
        std::shared_ptr<Node<KEY_TYPE, VALUE_TYPE>> _root;
};

#endif

