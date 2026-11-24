#include <iostream>
#include <queue>
#include <string>
#include "message.h"
#include "channel.h"

class Consumer {
    Channel& channel;
public:
    explicit Consumer(Channel& channel_) : channel(channel_) {}

    bool ProcessNext() {
        Message message(0, "");
        if (!channel.try_receive(message)) return false;

        std::cout << "Consumer: обработка сообщения " << message.GetId()
                  << ": " << message.GetText() << std::endl;

        channel.commit(message);
        return true;
    }
};