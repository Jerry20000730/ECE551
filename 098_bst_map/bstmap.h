#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
private:
    class Node {
    public:
        K key;
        V value;
        Node * left;
        Node * right;
        Node() : left(NULL), right(NULL) {}
        Node(const K & key, const V & value) : key(key), value(value), left(NULL), right(NULL) {}   
    };
    Node * root;
public:
    BstMap() : root(NULL) {}
    BstMap(const BstMap & rhs) {
        root = copyTree(rhs.root);
    }
    BstMap & operator=(const BstMap & rhs) {
        if (this != &rhs) {
            deleteHelper(root);
            root = copyTree(rhs.root);
        }
        return (*this);
    }
    Node * addHelper(Node * cur, const K & key, const V & value) {
        if (cur == NULL) {
            Node * newNode = new Node(key, value);
            return newNode;
        }
        if (key == cur->key) {
            cur->value = value;
            return cur;
        } else if (key > cur->key) {
            cur->right = addHelper(cur->right, key, value);
        } else {
            cur->left = addHelper(cur->left, key, value);
        }
        return cur;
    }
    virtual void add(const K & key, const V & value) {
        root = addHelper(root, key, value);
    }
    virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
        if (root == NULL) {
            throw std::invalid_argument("tree is empty");
        }
        Node * ptr = root;
        bool isFound = false;
        while (ptr != NULL) {
            if (key == ptr->key) {
                isFound = true;
                break;
            } else if (key > ptr->key) {
                ptr = ptr->right;
            } else {
                ptr = ptr->left;
            }
        }
        if (!isFound) {
            throw std::invalid_argument("key is not found");
        } else {
            return ptr->value;
        }
    }
    Node * removeHelper(Node * cur, const K & key) {
        if (cur == NULL) {
            return cur;
        }
        if (cur->key == key) {
            if (cur->left == NULL) {
                Node * temp = cur->right;
                delete cur;
                return temp;
            } else if (cur->right == NULL) {
                Node * temp = cur->left;
                delete cur;
                return temp;
            } else {
                Node * temp = cur->right;
                while (temp->left != NULL) {
                    temp = temp->left;
                }
                cur->key = temp->key;
                cur->value = temp->value;
                cur->right = removeHelper(cur->right, temp->key);
                return cur;
            }
        } else if (key > cur->key) {
            cur->right = removeHelper(cur->right, key);
            return cur;
        } else {
            cur->left = removeHelper(cur->left, key);
            return cur;
        }
    }
    virtual void remove(const K & key) {
        root = removeHelper(root, key);
    }
    void deleteHelper(Node * root) {
        if (root == NULL) {
            return;
        }
        deleteHelper(root->left);
        deleteHelper(root->right);
        delete(root);
    }
    virtual ~BstMap() {
        deleteHelper(root);
    }
    Node * copyTree(Node * root) {
        if (root == NULL) {
            return NULL;
        }
        Node * newNode = new Node(root->key, root->value);
        newNode->left = copyTree(root->left);
        newNode->right = copyTree(root->right);
        return newNode;
    }
};

#endif