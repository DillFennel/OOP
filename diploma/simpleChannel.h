#pragma once
#include <deque>
#include <iostream>
#include "channel.h"
#include "message.h"

class SimpleChannel : public Channel {
public:
    void Publish(const Message& m) override {
        queue_.push(m);
        OnPublished();
    }
    bool TryPop(Message& out) override {
        if (queue_.empty()) return false;
        out = queue_.front();
        queue_.pop();
        return true;
    }
    void Commit(const Message&) override {
        // нету
    }
    std::size_t Size() const override { return queue_.size(); }
private:
    std::queue<Message> queue_;
};