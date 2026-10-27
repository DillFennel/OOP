#include "../logger.hpp"

int main () {
    Logger logger1;
    Logger logger2(std::move(logger1));
    return 0;
}