#include "../logger.hpp"

int main () {
    Logger* logger1 = new Logger();
    Logger* logger2 = new Logger();
    Logger* logger3 = new Logger();

    
    delete logger2;
    delete logger3;
    delete logger1;
}