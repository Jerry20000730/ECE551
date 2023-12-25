#ifndef __BSTSET_H__
#define __BSTSET_H__

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
private:
    class Node {
    public:
        T key;
        Node * left;
        Node * right;
        Node() : left(NULL), right(NULL) {}
        Node(const T & key) : key(key), left(NULL), right(NULL) {}
    };
    Node * root;
public:
    BstSet() : root(NULL) {}
    BstSet(const BstSet & rhs) {
        root = copyTree(rhs.root);
    }
    ~BstSet() {
        deleteHelper(root);
    }
    virtual void add(const T & key) {
        root = addHelper(root, key);
    }
    virtual bool contains(const T& key) const {
        if (root == NULL) {
            return false;
        }
        Node * ptr = root;
        while (ptr != NULL) {
            if (key == ptr->key) {
                return true;
            } else if (key > ptr->key) {
                ptr = ptr->right;
            } else {
                ptr = ptr->left;
            }
        }
        return false;
    }
    virtual void remove(const T& key) {
        root = removeHelper(root, key);
    }
    BstSet& operator=(const BstSet & rhs) {
        if (this != &rhs) {
            deleteHelper(root);
            root = copyTree(rhs.root);
        }
        return (*this);
    }
    Node * addHelper(Node * cur, const T & key) {
        if (cur == NULL) {
            Node * newNode = new Node(key);
            return newNode;
        }
        if (key == cur->key) {
            return cur;
        } else if (key > cur->key) {
            cur->right = addHelper(cur->right, key);
        } else {
            cur->left = addHelper(cur->left, key);
        }
        return cur;
    }
    Node * removeHelper(Node * cur, const T & key) {
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
    void deleteHelper(Node * root) {
        if (root == NULL) {
            return;
        }
        deleteHelper(root->left);
        deleteHelper(root->right);
        delete(root);
    }
    Node * copyTree(Node * root) {
        if (root == NULL) {
            return NULL;
        }
        Node * newNode = new Node(root->key);
        newNode->left = copyTree(root->left);
        newNode->right = copyTree(root->right);
        return newNode;
    }
};

#endif