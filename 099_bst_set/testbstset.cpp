#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>

#include "bstset.h"

int main(int argc, char ** argv) {
    BstSet<int> set;
    std::cout << "program starts" << std::endl;

    set.add(0);
    set.add(1);
    set.add(2);

    assert(set.contains(2));

    BstSet<int> set1(set);

    assert(set1.contains(2));

    BstSet<int> set2;
    set2 = set;
    assert(set2.contains(2));

    set2.remove(0);

    assert(set.contains(0));

    return EXIT_SUCCESS;
}