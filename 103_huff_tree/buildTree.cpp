#include "node.h"

Node *  buildTree(uint64_t * counts) {
  priority_queue_t pq;
  for (int i = 0; i < 257; i++) {
    if (counts[i] > 0) {
      Node * node = new Node(i, counts[i]);
      pq.push(node);
    }
  }
  while (pq.size() > 1) {
    Node * left = pq.top();
    pq.pop();
    Node * right = pq.top();
    pq.pop();
    Node * node = new Node(left, right);
    pq.push(node);
  }
  return pq.top();
}  
