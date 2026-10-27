#include <iostream>
#include <queue>
#include "message.h"
#include "channel.h"

class Producer {
public:
    explicit Producer(Channel& channel) : channel_(channel) {}

    void Publish(const Message& message) {
        channel_.Publish(message);
    }

private:
    Channel& channel_;
};