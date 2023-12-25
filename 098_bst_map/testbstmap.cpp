#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>

#include "bstmap.h"

int main(void) {
    BstMap<int, int> map;
    std::cout << "program starts" << std::endl;
    BstMap<int, int> map10;
    map10 = map;

    map.add(15, 1);
    std::cout << "add (15, 1)" << std::endl;
    map.add(7, 2);
    std::cout << "add (7, 2)" << std::endl;
    map.add(18, 3);
    std::cout << "add (18, 3)" << std::endl;
    map.add(1, 4);
    std::cout << "add (1, 4)" << std::endl;
    map.add(39, 5);
    std::cout << "add (39, 5)" << std::endl;
    map.add(60, 6);
    std::cout << "add (60, 6)" << std::endl;
    map.add(5, 7);
    std::cout << "add (5, 7)" << std::endl;
    map.add(40, 8);
    std::cout << "add (40, 8)" << std::endl;
    map.add(36, 9);
    std::cout << "add (36, 10)" << std::endl;
    map.add(100, 10);
    std::cout << "add (100, 10)" << std::endl;
    map.add(15, 11);
    std::cout << "update (15, 11)" << std::endl;

    std::cout << "trying to find 40" << std::endl;
    int ans1 = map.lookup(40);
    std::cout << "trying to find 39" << std::endl;
    int ans2 = map.lookup(39);
    std::cout << "trying to find 15" << std::endl;
    int ans3 = map.lookup(15);
    std::cout << "remove 15" << std::endl;
    map.remove(15);
    std::cout << "trying to find 5" << std::endl;
    int ans4 = map.lookup(5);

    assert(ans1 == 8);
    assert(ans2 == 5);
    assert(ans3 == 11);
    assert(ans4 == 7);

    BstMap<int, int> map2(map);
    std::cout << "trying to find 40 in second map" << std::endl;
    int ans5 = map2.lookup(40);
    std::cout << "trying to find 39 in second map" << std::endl;
    int ans6 = map2.lookup(39);
    std::cout << "trying to find 5 in second map" << std::endl;
    int ans7 = map2.lookup(5);

    assert(ans5 == 8);
    assert(ans6 == 5);
    assert(ans7 == 7);

    std::cout << "remove 60 in second map" << std::endl;
    map2.remove(60);

    BstMap<int, int> map3;
    map3 = map;
    std::cout << "trying to find 40 in third map" << std::endl;
    int ans8 = map3.lookup(40);
    std::cout << "trying to find 39 in third map" << std::endl;
    int ans9 = map3.lookup(39);
    std::cout << "trying to find 5 in third map" << std::endl;
    int ans10 = map3.lookup(5);

    assert(ans8 == 8);
    assert(ans9 == 5);
    assert(ans10 == 7);

    std::cout << "remove 39 in third map" << std::endl;
    map2.remove(39);

    std::cout << "trying to find 60 in first map" << std::endl;
    int ans11 = map.lookup(60);
    std::cout << "trying to find 39 in first map" << std::endl;
    int ans12 = map.lookup(39);
    assert(ans11 == 6);
    assert(ans12 == 5);

    return EXIT_SUCCESS;
}