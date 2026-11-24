#include <iostream>
#include <queue>
#include "message.h"
#include "channel.h"

class Producer {
    Channel& channel;
public:
    explicit Producer(Channel& channel_) : channel(channel_) {}

    void Publish(const Message& message) {
        channel.publish(message);
    }
};