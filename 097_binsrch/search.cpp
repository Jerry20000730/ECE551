#include <iostream>
 
#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
    // base case
    if (low == high || low + 1 == high) {
        return low;
    }
    int mid = low + (high - low) / 2;
    int res = f->invoke(mid);
    if (res == 0) {
        return mid;
    } else if (res > 0) {
        return binarySearchForZero(f, low, mid);
    } else {
        return binarySearchForZero(f, mid, high);
    }
}