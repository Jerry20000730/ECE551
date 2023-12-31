#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <algorithm>
#include <iostream>

class IndexOutOfBounds : public std::exception {
public:
    const char * what() const throw() { 
        return "[EXCEPTION] Index Out of Bounds!"; 
    }
};

template<typename T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        Node * next;
        Node * prev;
        Node(T d) : data(d), next(NULL), prev(NULL){};
    };
    Node * head;
    Node * tail;
    int size;
public:
    LinkedList() : head(NULL), tail(NULL), size(0) {}
    LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
        Node * ptr = rhs.head;
        while (ptr != NULL) {
            addBack(ptr->data);
            ptr = ptr->next;
        }
    }
    LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
        LinkedList l(rhs);
        std::swap(l.head, head);
        std::swap(l.tail, tail);
        std::swap(l.size, size);
    }
    return *this;
    }
    ~LinkedList() {
        Node * traverse = head;
        Node * temp = NULL;
        while (traverse != NULL) {
            temp = traverse->next;
            delete traverse;
            traverse = temp;
        }
    }
    void addFront(const T & item) {
        Node * n = new Node(item);
        if (head != NULL) {
            n->next = head;
            head->prev = n;
        } else {
            tail = n;
        }
        head = n;
        size++;
    }
    void addBack(const T & item) {
        Node * n = new Node(item);
        if (tail != NULL) {
            tail->next = n;
            n->prev = tail;
        } else {
            head = n;
        }
        tail = n;
        size++;
    }
    bool remove(const T & item) {
        Node * traverse = head;
        while (traverse != NULL && traverse->data != item) {
            traverse = traverse->next;
        }
        if (traverse == NULL) {
            return false;
        }
        Node * nextN = traverse->next;
        Node * prevN = traverse->prev;
        if (nextN != NULL) {
            nextN->prev = prevN;
        } else {
            tail = prevN;
        }
        if (prevN != NULL) {
            prevN->next = nextN;
        } else {
            head = nextN;
        }
        size -= 1;
        delete traverse;
        return true;
    }
    T & operator[](int index) {
        try {
            if (index < 0 || index > size - 1) {
                throw IndexOutOfBounds();
            }
        } catch (IndexOutOfBounds & e) {
            std::cerr << e.what() << std::endl;
        }
        Node * ptr = head;
        for (int i = 0; i < index; i++) {
            ptr = ptr->next;
        }
        return ptr->data;
    }
    T & operator[](int index) const {
        try {
            if (index < 0 || index > size - 1) {
                throw IndexOutOfBounds();
            }
        } catch (IndexOutOfBounds & e) {
            std::cerr << e.what() << std::endl;
        }
        Node * ptr = head;
        for (int i = 0; i < index; i++) {
            ptr = ptr->next;
        }
        return ptr->data;
    }
    int find(const T & item) {
        for (int i = 0; i < size; i++) {
        if ((*this)[i] == item) {
            return i;
        }
    }
    return -1;
  }
    int getSize() const { return size; }
};

#endif
