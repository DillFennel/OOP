#include "../logger.hpp"

int main () {
    Logger logger1;
    Logger logger2;
    logger1 = logger2;
    logger1 = std::move(logger2);
}