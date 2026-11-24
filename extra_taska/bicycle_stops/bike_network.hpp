#pragma once

#include "station.hpp"

#include <cstddef>
#include <stdexcept>
#include <vector>

struct Route {
    std::vector<size_t> stops;
    long long distance = -1; // -1 означает, что путь пока не найден.
};

struct Transfer {
    Route route;
    int bikes;
};

class BikeNetwork {
    std::vector<Station> stations;
    std::vector<std::vector<int>> roads; // roads[from][to] — длина дороги, 0 — дороги нет.
public:
    size_t add_station(const Station& station) {
        stations.push_back(station);
        // Добавляем строку и столбец для новой станции.
        roads.resize(stations.size());
        for (size_t i = 0; i < roads.size(); i++) {
            roads[i].resize(stations.size(), 0);
        }
        return stations.size() - 1;
    }

    void add_road(size_t from, size_t to, int distance) {
        if (from >= stations.size() || to >= stations.size() || distance <= 0) {
            throw std::invalid_argument("ERROR: Укажите существующие станции и положительную длину дороги");
        }
        // Если между станциями несколько дорог, запоминаем самую короткую.
        if (roads[from][to] == 0 || distance < roads[from][to]) {
            roads[from][to] = distance;
            roads[to][from] = distance;
        }
    }

    const std::vector<Station>& get_stations() const { return stations; }

    std::vector<Route> shortest_routes_from(size_t start) const {
        size_t count = stations.size();
        std::vector<Route> best(count);
        std::vector<bool> visited(count, false);
        best.at(start).stops.push_back(start);
        best[start].distance = 0;

        while (true) {
            // Ищем ближайшую станцию, которую ещё не обработали.
            size_t current = count; // Номер count означает, что станция не выбрана.
            for (size_t i = 0; i < count; i++) {
                if (visited[i] || best[i].distance == -1) continue;
                if (current == count || best[i].distance < best[current].distance) {
                    current = i;
                }
            }
            if (current == count) break;
            visited[current] = true;

            // Проверяем, станет ли путь до соседей короче через эту станцию.
            for (size_t to = 0; to < count; to++) {
                if (roads[current][to] == 0) continue;
                long long distance = best[current].distance + roads[current][to];
                if (best[to].distance == -1 || distance < best[to].distance) {
                    best[to] = best[current];
                    best[to].stops.push_back(to);
                    best[to].distance = distance;
                }
            }
        }

        // Возвращаем пути до других станций в порядке добавления станций.
        std::vector<Route> routes;
        for (Route route : best) {
            if (route.stops.size() > 1) routes.push_back(route);
        }
        return routes;
    }

    // Рассчитывает перевозки и меняет количество велосипедов на станциях.
    std::vector<Transfer> rebalance() {
        std::vector<Transfer> transfers;

        while (true) {
            Route nearest;

            // Ищем ближайшую пару, где один может отдать, а другому нужно.
            for (size_t from = 0; from < stations.size(); from++) {
                if (stations[from].get_diff() >= 0) continue;

                for (Route route : shortest_routes_from(from)) {
                    size_t to = route.stops.back();
                    if (stations[to].get_diff() <= 0) continue;

                    if (nearest.distance == -1 || route.distance < nearest.distance) {
                        nearest = route;
                    }
                }
            }
            if (nearest.distance == -1) break;

            // Перевозим велосипеды и записываем результат.
            size_t from = nearest.stops.front();
            size_t to = nearest.stops.back();
            Transfer transfer;
            transfer.route = nearest;
            transfer.bikes = stations[from].transfer_to(stations[to]);
            transfers.push_back(transfer);
        }
        return transfers;
    }
};
