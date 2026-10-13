#include <iostream>
#include <queue>
#include "message.h"

class Producer {
public:
    explicit Producer(std::queue<Message>& channel) : channel_(channel) {}

    void Publish(const Message& message) {
        channel_.push(message);
        std::cout << "Producer: отправлено сообщение " << message.GetId() << std::endl;
    }

private:
    std::queue<Message>& channel_;
};