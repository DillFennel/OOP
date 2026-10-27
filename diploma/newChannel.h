#pragma once
#include <deque>
#include <unordered_set>
#include <iostream>
#include "channel.h"
#include "message.h"

class NewChannel : public Channel {
public:
    void Publish(const Message& m) override {
        queue_.push_back(m);
        OnPublished();
    }
    bool TryPop(Message& out) override {
        if (queue_.empty()) return false;
        out = queue_.front();
        in_flight_.insert(out.GetId());
        return true;
    }
    void Commit(const Message& m) override {
        in_flight_.erase(m.GetId());
        if (!queue_.empty() && queue_.front().GetId() == m.GetId())
            queue_.pop_front();
    }
    std::size_t Size() const override { return queue_.size(); }
    std::size_t InFlightCount() const { return in_flight_.size(); }
private:
    std::deque<Message> queue_;
    std::unordered_set<int> in_flight_;
};