#include <iostream>
#include <queue>
#include <string>
#include <memory>

#include "message.h"
#include "producer.h"
#include "consumer.h"

#include "simpleChannel.h"
#include "newChannel.h"

int main(int argc, char** argv) {
    const bool use_new_channel = (argc > 1 && std::string(argv[1]) == "--new_channel");

    std::unique_ptr<Channel> channel;
    if (use_new_channel) {
        channel = std::make_unique<NewChannel>("topic/messages");
    } else {
        channel = std::make_unique<SimpleChannel>();
    }

    Producer producer(*channel);
    Consumer consumer(*channel);

    producer.Publish(Message(1, "Первое сообщение"));
    producer.Publish(Message(2, "Второе сообщение"));

    int counter = 0;
    while (consumer.ProcessNext()) {
        counter++;
        std::cout << "Обработано сообщений: " << counter << std::endl;
        std::cout << "Осталось сообщений: " << channel->Size() << std::endl;
    }
    std::cout << "Всего опубликовано: " << channel->PublishedCount() << std::endl;
    std::cout << "Все сообщения обработаны.\n";
    return 0;
}
