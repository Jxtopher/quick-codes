/// 
/// @file node.hpp
/// @author Jxtopher
/// @brief 
/// @version 0.1
/// @date 2020-02-22
/// 
/// @copyright Copyright (c) 2020
/// 
///

#ifndef NODE_H
#define NODE_H

template <typename KEY_TYPE, typename VALUE_TYPE>
class Node {
    public:
    Node() : _node_left(nullptr),  _node_right(nullptr) {
    }

    Node(KEY_TYPE key, VALUE_TYPE value) : _key(key), _value(value), _node_left(nullptr),  _node_right(nullptr) {

    }

    virtual ~Node() {
        
    }

    void left(std::shared_ptr<Node> node_left) {
        _node_left = node_left;
    }

    std::shared_ptr<Node> left() {
        return _node_left;
    }

    void right(std::shared_ptr<Node> node_right) {
        _node_right = node_right;
    }

    std::shared_ptr<Node> right() {
        return _node_right;
    }

    void value(VALUE_TYPE v) {
        _value = v;
    }

    VALUE_TYPE value() const {
        return _value;
    }

    void key(KEY_TYPE k) {
        _key = k;
    }

    KEY_TYPE key() const {
        return _key;
    }

    private:
    KEY_TYPE _key;
    VALUE_TYPE _value;
    std::shared_ptr<Node> _node_left;
    std::shared_ptr<Node> _node_right;
};


#endif