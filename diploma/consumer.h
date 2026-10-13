#include <iostream>
#include <queue>
#include <string>
#include "message.h"

class Consumer {
public:
    explicit Consumer(std::queue<Message>& channel) : channel_(channel) {}

    bool ProcessNext() {
        if (channel_.empty()) { return false; }

        const Message& message = channel_.front();
        const int id = message.GetId();

        std::cout << "Consumer: обработка сообщения " << id << ": " << message.GetText() << std::endl;

        channel_.pop();
        std::cout << "Consumer: обработка сообщения " << id << " подтверждена" << std::endl;
        return true;
    }

private:
    std::queue<Message>& channel_;
};