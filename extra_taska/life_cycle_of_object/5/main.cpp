#include "../logger.hpp"

void make_loggers(int n) {
    if (n <= 0) {
        return;
    }
    Logger logger;
    make_loggers(n - 1);
}

int main () {
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;
    make_loggers(n);
    return 0;
}