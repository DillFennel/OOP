#pragma once
#include <string>

class Message {
public:
    Message(int id, const std::string& text) : id_(id), text_(text) {}

    int GetId() const { return id_; }
    const std::string& GetText() const { return text_; }

private:
    int id_;
    std::string text_;
};