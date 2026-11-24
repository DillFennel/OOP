#pragma once

#include <queue>
#include <string>
#include <iostream>
#include "message.h"

class Channel {
    std::size_t published_count = 0;
protected:
    void count_published() { ++published_count; }
public:
    virtual ~Channel() = default;

    virtual void publish(const Message& message) = 0;

    virtual bool try_receive(Message& out) = 0;
    virtual std::size_t get_size() const = 0;
    virtual void commit(const Message& message) = 0;

    std::size_t get_published_count() const { return published_count; }
};