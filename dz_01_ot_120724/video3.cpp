#include <iostream>
#include <string>

int main() {
    int x = 4;
    int y = 5;

    std::cout << (x + y) * (x - y) << "\n";

    if (x == y) {
        std::cout << "equal" << "\n";
    } 
    else {
        std::cout << "not equal" << "\n";
    }

    std::string xs = "abc";
    std::string ys = "def";

    if (xs < ys) { // в данной ситуации выводит меньше, потому что строки сравниваются как в словаре написаны
        std::cout << "less" << "\n";
    } else {
        std::cout << "not less" << "\n";
    }

    return 0;
}