#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>

#include <vector>

int main(int argc, char ** argv) {
    if (argc == 1) {
        std::string temp;
        std::vector<std::string> strVector;
        while (std::getline(std::cin, temp)) {
            strVector.push_back(temp);
        }
        std::sort(strVector.begin(), strVector.end());
        std::vector<std::string>::iterator it = strVector.begin();
        while (it != strVector.end()) {
            std::cout << *it << std::endl;
            ++it;
        }
    } else {
        for (int i = 1; i < argc; i++) {
            std::ifstream ifs(argv[i]);
            if (ifs.fail()) {
                std::cerr << "[error] file failed to open" << std::endl;
                exit(EXIT_FAILURE);
            }
            std::string temp;
            std::vector<std::string> strVector;
            while (std::getline(ifs, temp)) {
                strVector.push_back(temp);
            }
            std::sort(strVector.begin(), strVector.end());
            std::vector<std::string>::iterator it = strVector.begin();
            while (it != strVector.end()) {
                std::cout << *it << std::endl;
                ++it;
            }
            ifs.close();
        }
    }

    return EXIT_SUCCESS;
}