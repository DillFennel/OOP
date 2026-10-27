#include <iostream>
#include <queue>
#include <string>
#include "message.h"
#include "channel.h"

class Consumer {
public:
    explicit Consumer(Channel& channel) : channel_(channel) {}

    bool ProcessNext() {
        Message message(0, "");
        if (!channel_.TryPop(message)) return false;

        std::cout << "Consumer: обработка сообщения " << message.GetId()
                  << ": " << message.GetText() << std::endl;

        channel_.Commit(message);
        return true;
    }

private:
    Channel& channel_;
};