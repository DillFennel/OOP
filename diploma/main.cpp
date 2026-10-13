#include <iostream>
#include <queue>
#include <string>

#include "message.h"
#include "producer.h"
#include "consumer.h"

int main() {
    std::queue<Message> channel;

    Producer producer(channel);
    Consumer consumer(channel);

    producer.Publish(Message(1, "Первое сообщение"));
    producer.Publish(Message(2, "Второе сообщение"));

    int counter = 0;
    while (consumer.ProcessNext()) {
        counter++;
        std::cout << "Обработано сообщений: " << counter << std::endl;
        std::cout << "Осталось сообщений: " << channel.size() << std::endl;
    }

    std::cout << "Все сообщения обработаны.\n";
    return 0;
}
