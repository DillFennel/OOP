#include "bike_network.hpp"

#include <iostream>
#include <vector>

int main() {
    BikeNetwork network;
    // Для каждой станции задаём вместимость, число велосипедов и цель к утру.
    size_t park = network.add_station({"Парк", 10, 8, 4});
    size_t metro = network.add_station({"Метро", 8, 1, 4});
    size_t university = network.add_station({"Университет", 8, 2, 5});
    size_t stadium = network.add_station({"Стадион", 6, 5, 4});

    network.add_road(park, metro, 2);
    network.add_road(metro, university, 1);
    network.add_road(park, university, 5);
    network.add_road(stadium, university, 1);

    std::vector<Station> stations = network.get_stations();
    std::cout << "Станции вечером\n";
    for (Station station : stations) {
        std::cout << station.get_name() << ": велосипедов " << station.get_bikes()
            << " из " << station.get_capacity() << " мест, цель " << station.get_target()
            << ", требуется изменить кол-во велосипедов на: " << station.get_diff() << '\n';
    }

    BikeNetwork morning = network; // Моделируем перевозки на копии сети.
    std::vector<Transfer> transfers = morning.rebalance();
    std::cout << "\nПлан перевозок\n";
    if (transfers.empty()) std::cout << "Перевозок нет.\n";
    for (Transfer transfer : transfers) {
        for (size_t i = 0; i < transfer.route.stops.size(); i++) {
            if (i > 0) std::cout << " → ";
            size_t stop = transfer.route.stops[i];
            std::cout << stations[stop].get_name();
        }
        std::cout << " | " << transfer.route.distance << " км | велосипедов: " << transfer.bikes << '\n';
    }

    std::cout << "\nПосле перевозок\n";
    int remaining_shortage = 0;
    for (Station station : morning.get_stations()) {
        std::cout << station.get_name() << ": " << station.get_bikes() << " при цели " << station.get_target();
        int shortage = station.get_diff();
        if (shortage > 0) {
            std::cout << ", не хватает " << shortage;
            remaining_shortage += shortage;
        }
        std::cout << '\n';
    }
    std::cout << "Общий оставшийся дефицит: " << remaining_shortage << '\n';
}
