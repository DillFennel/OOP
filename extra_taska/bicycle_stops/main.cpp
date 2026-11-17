#include "rebalancing_planner.hpp"

#include <algorithm>
#include <iostream>

int main() {
    BikeNetwork network;
    const auto park = network.add_station({"Парк", 10, 8, 4});
    const auto metro = network.add_station({"Метро", 8, 1, 4});
    const auto university = network.add_station({"Университет", 8, 2, 5});
    const auto stadium = network.add_station({"Стадион", 6, 5, 4});

    network.add_road(park, metro, 2);
    network.add_road(metro, university, 1);
    network.add_road(park, university, 5);
    network.add_road(stadium, university, 1);

    const auto& stations = network.get_stations();
    std::cout << "Станции вечером\n";
    for (const Station& station : stations) {
        std::cout << station.get_name() << ": велосипедов " << station.get_bikes()
            << " из " << station.get_capacity() << " мест, цель " << station.get_target()
            << ", требуется изменить кол-во велосипедов на: " << station.get_diff() << std::endl;
    }

    auto plan = RebalancingPlanner::build(network);
    std::cout << "\nПлан перевозок\n";
    if (plan.transfers.empty()) std::cout << "Перевозок нет.\n";
    for (const Transfer& transfer : plan.transfers) {
        const auto& stops = transfer.route.stops;
        std::cout << stations[stops.front()].get_name();
        for (std::size_t i = 1; i < stops.size(); ++i) {
            std::cout << " → " << stations[stops[i]].get_name();
        }
        std::cout << " | " << transfer.route.distance << " км | велосипедов: " << transfer.bikes << '\n';
    }

    std::cout << "\nПосле перевозок\n";
    int remaining_shortage = 0;
    for (const Station& station : plan.final_stations) {
        std::cout << station.get_name() << ": " << station.get_bikes() << " при цели " << station.get_target();
        int shortage = std::max(0, station.get_diff());
        if (shortage > 0) {
            std::cout << ", не хватает " << shortage;
        }
        std::cout << '\n';
        remaining_shortage += shortage;
    }
    std::cout << "Общий оставшийся дефицит: " << remaining_shortage << '\n';
}
