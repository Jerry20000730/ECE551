#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(1);
    assert(il.getSize() == 1 && il.head == il.tail && il.head != NULL && il.head->data == 1 && il.head->next == NULL && il.tail->prev == NULL);
    il.addFront(2);
    assert(il.getSize() == 2 && il.head->data == 2 && il.tail->data == 1 && il.head->next == il.tail && il.tail->prev == il.head && il.head->prev == NULL && il.tail->next == NULL);
  }
  // many more tester methods

  void testAddBack() {
    IntList il;
    il.addBack(1);
    assert(il.getSize() == 1 && il.head == il.tail && il.head != NULL && il.head->data == 1 && il.head->next == NULL && il.tail->prev == NULL);
    il.addBack(2);
    assert(il.getSize() == 2 && il.head->data == 1 && il.tail->data == 2 && il.head->next == il.tail && il.tail->prev == il.head && il.head->prev == NULL && il.tail->next == NULL);
    il.addFront(3);
    assert(il.getSize() == 3 && il.head->data == 3 && il.head->next->data == 1 && il.tail->data == 2 && il.head->next->next == il.tail && il.tail->prev->prev == il.head && il.head->prev == NULL && il.tail->next == NULL);
  }

  void testAllocating() {
    IntList il1;
    IntList * il4 = new IntList();
    il4->addFront(1);
    il4->addBack(2);
    assert(il4->getSize() == 2 && il4->head->data == 1 && il4->tail->data == 2 && il4->head->next == il4->tail && il4->tail->prev == il4->head && il4->head->prev == NULL && il4->tail->next == NULL);
    IntList * il3 = new IntList[4]();
    il1.addFront(1);
    il1.addBack(2);
    IntList il2(il1);
    assert(il2.getSize() == il1.getSize() && il2.head->data == 1 && il2.tail->data == 2 && il2.head->next == il2.tail && il2.head->prev == NULL && il2.tail->prev == il2.head && il2.tail->next == NULL);
    il3[0] = il1;
    assert(il3[0].head->data == 1 && il3[0].tail->data == 2);
    delete[] il3;
    delete il4;
  }

  void testAllocating2() {
    IntList il1;
    il1.addFront(1);
    IntList il2;
    il2 = il1;
    assert(il2.head != il1.head && il2.tail != il1.tail);
    IntList* il3 = new IntList(il1);
    il3->addFront(1);
    IntList* il4 = new IntList(*il3);
    assert(il3->head != il4->head && il3->tail != il4->tail && il3->getSize() == il4->getSize());
    delete il3;
    delete il4;
  }

  void testShallowCopy() {
    IntList il1;
    il1.addFront(1);
    il1.addBack(2);
    il1.addBack(3);
    IntList il2(il1);
    IntList::Node *il2_it = il2.head, *il1_it = il1.head;
    for (int i = 0; i < il1.getSize(); i++) {
      assert(il2_it != NULL && il1_it != NULL && il2_it != il1_it);
      il2_it = il2_it->next;
      il1_it = il1_it->next;
    }
  }

  void testRemoveAndCopy() {
    IntList *il1 = new IntList();
    il1->addFront(1);
    il1->remove(1);
    IntList *il2 = new IntList(*il1);
    delete il1;
    assert(il2->head == NULL && il2->tail == NULL && il2->getSize() == 0);
    delete il2;
  }

  void testCopying() {
    IntList il1;
    il1.addFront(1);
    il1.addFront(2);
    IntList* il3 = new IntList(il1);
    assert(il1.getSize() == il3->getSize());
    for (int i = 0; i < il1.getSize(); i++) {
      assert(il1[i] == (*il3)[i]);
    }
    delete il3;
    // [2 , 1]
    IntList il2;
    il2 = il1;
    assert(il2.getSize() == 2 && il2.head->data == 2 && il2.tail->data == 1 && il2.head->next->data == 1 && il2.tail->prev->data == 2 && il2.head->prev == NULL && il2.tail->next == NULL);

    IntList il5;
    il5.addBack(1);
    il5.addBack(2);
    il5.addBack(3);
    IntList ilcopy2 = il5; // 1 2 3
    assert(ilcopy2.getSize() == 3);
    assert(ilcopy2[0] == 1);
    assert(ilcopy2[1] == 2);
    assert(ilcopy2[2] == 3);
    IntList::Node * copy_cur = ilcopy2.head; 
    IntList::Node * cur = il5.head;
    for (int i = 0; i < il5.getSize(); i++) {
      assert(copy_cur != NULL && cur != NULL && copy_cur != cur);
      copy_cur = copy_cur->next;
      cur = cur->next;
    }
  }

  void testDeallocation() {
    IntList * il1 = new IntList();
    IntList * il2 = new IntList[4]();
    il1->addFront(1);
    il1->addFront(2);
    delete il1;
    delete[] il2;

    IntList *il5 = new IntList();
    il5->addFront(1);
    il5->remove(1);
    IntList *il6 = new IntList(*il5);
    delete il5;
    assert(il6->head == NULL && il6->tail == NULL && il6->getSize() == 0);
    delete il6;
  }

  void testCombination() {
    IntList il1;
    il1.addFront(1);
    IntList il2;
    il2.addBack(2);
    il2 = il1;
    IntList* il3 = new IntList(il1);
    il3->addFront(1);
    IntList* il4 = new IntList(*il3);
    assert(il3->head != il4->head && il3->tail != il4->tail);
    delete il3;
    delete il4;
  }

  void testRemove1() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);
    il.addBack(4);
    assert(il.remove(3) == true && il.head != NULL && il.tail != NULL);
    assert(il.remove(5) == false);
    assert(il[0] == 1);
    assert(il[1] == 2);
    assert(il[2] == 4);
  }

  void testRemove2() {
    IntList * il1 = new IntList();
    assert(il1->remove(1) == false);
    il1->addBack(1);
    il1->addBack(2);
    il1->addBack(3);
    assert(il1->remove(1) == true && il1->getSize() == 2 && il1->head != NULL && il1->head->data == 2 && il1->tail != NULL && il1->tail->data == 3);
    assert(il1->remove(1) == false && il1->getSize() == 2 && il1->head != NULL && il1->head->data == 2 && il1->tail != NULL && il1->tail->data == 3);
    assert(il1->remove(2) == true && il1->getSize() == 1 && il1->head != NULL && il1->head->data == 3 && il1->tail != NULL && il1->tail->data == 3 && il1->head == il1->tail);
    assert(il1->remove(2) == false);
    assert(il1->remove(3) == true && il1->getSize() == 0 && il1->head == NULL && il1->tail == NULL);  
    delete il1;
  }

  void testRemove3() {
    IntList il;
    il.addFront(1);
    il.addBack(2);
    il.addBack(3);
    il.addBack(4);
    IntList::Node * head_ptr = il.head->next;
    IntList::Node * tail_ptr = il.tail->prev;
    assert(il.remove(1) == true && il.getSize() == 3 && il.head->data == 2 && il.head == head_ptr);
    assert(il.remove(1) == false && il.getSize() == 3 && il.head->data == 2 && il.head == head_ptr);
    assert(il.remove(4) == true && il.getSize() == 2 && il.tail == tail_ptr);
  }

  void testRemove4() {
    IntList il1;
    il1.addBack(2);
    il1.addBack(1);
    il1.addBack(3);
    IntList* il2 = new IntList(il1);
    assert(il2->remove(1) == true && il2->head != NULL && il2->tail != NULL && (*il2)[0] == 2 && (*il2)[1] == 3 && il2->head->next == il2->tail && il2->tail->prev == il2->head && il2->head->prev == NULL && il2->tail->next == NULL);
    assert(il2->remove(1) == false && il2->head != NULL && il2->tail != NULL && (*il2)[0] == 2 && (*il2)[1] == 3 && il2->head->next == il2->tail && il2->tail->prev == il2->head && il2->getSize() == 2 && il2->head->prev == NULL && il2->tail->next == NULL);
    assert(il2->remove(2) == true && il2->head != NULL && il2->tail != NULL && (*il2)[0] == 3 && il2->tail == il2->head && il2->head->prev == NULL && il2->tail->next == NULL);
    assert(il2->remove(2) == false && il2->head != NULL && il2->tail != NULL && (*il2)[0] == 3 && il2->tail == il2->head && il2->head->prev == NULL && il2->tail->next == NULL);
    assert(il2->remove(3) == true && il2->head == NULL && il2->tail == NULL);
    assert(il2->remove(3) == false);
    delete il2;
  }

  void someFunction(IntList & il) {
    // randomly do some task
    il.addFront(3);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testAllocating();
  t.testAllocating2();
  t.testCopying();
  t.testDeallocation();
  t.testShallowCopy();
  t.testRemoveAndCopy();
  t.testCombination();
  t.testRemove1();
  t.testRemove2();
  t.testRemove3();
  t.testRemove4();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
