#pragma once
#include <deque>
#include <iostream>
#include "channel.h"
#include "message.h"

class SimpleChannel : public Channel {
    std::queue<Message> queue;
public:
    void publish(const Message& message) override {
        queue.push(message);
        count_published();
    }
    bool try_receive(Message& out) override {
        if (queue.empty()) return false;
        out = queue.front();
        queue.pop();
        return true;
    }
    void commit(const Message& message) override {
        std::cout << "SimpleChannel: сообщение " << message.GetId() << " обработано" << std::endl;
    }
    std::size_t get_size() const override { return queue.size(); }
};