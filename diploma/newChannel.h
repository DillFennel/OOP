#pragma once
#include <deque>
#include <unordered_set>
#include <iostream>
#include "channel.h"
#include "message.h"

class NewChannel : public Channel {
    std::deque<Message> queue;
    std::unordered_set<int> process;
public:
    void publish(const Message& message) override {
        queue.push_back(message);
        count_published();
    }
    bool try_receive(Message& out) override {
        if (queue.empty()) return false;
        out = queue.front();
        process.insert(out.GetId());
        return true;
    }
    void commit(const Message& message) override {
        process.erase(message.GetId());
        if (!queue.empty() && queue.front().GetId() == message.GetId()) {
            queue.pop_front();
        }
        std::cout << "NewChannel: сообщение " << message.GetId() << " обработано" << std::endl;
    }
    std::size_t get_size() const override { return queue.size(); }
    std::size_t get_process_size() const { return process.size(); }
};