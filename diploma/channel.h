#pragma once

#include <queue>
#include <string>
#include <iostream>
#include "message.h"

class Channel {
public:
    virtual ~Channel() = default;

    virtual void Publish(const Message& message) = 0;
    virtual bool TryPop(Message& out) = 0;
    virtual std::size_t Size() const = 0;
    virtual void Commit(const Message& message) = 0;

    std::size_t PublishedCount() const { return published_count_; }

protected:
    void OnPublished() { ++published_count_; }

private:
    std::size_t published_count_ = 0;
};