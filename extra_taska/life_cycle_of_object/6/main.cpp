#include "../logger.hpp"
#include <list>

int main () {
    int n;
    std::cin >> n;
    std::list<Logger*> data;
    for (int i=0; i<n; i++) {
        data.push_back(new Logger());
    }
    for (int i=0; i<n; i++) {
        delete data.front();
        data.pop_front();
    }
    return 0;
}