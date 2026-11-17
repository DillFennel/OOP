#pragma once

#include "station.hpp"

#include <cstddef>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

struct Route {
    std::vector<size_t> stops;
    int distance;
};

class BikeNetwork {
    struct Road {
        size_t to;
        int distance;
    };

    std::vector<Station> stations;
    std::vector<std::vector<Road>> roads;
public:
    size_t add_station(const Station& station) {
        stations.push_back(station);
        roads.emplace_back();
        return stations.size() - 1;
    }

    void add_road(size_t from, size_t to, int distance) {
        if (from >= stations.size() || from < 0 ||
            to >= stations.size() || to < 0 || distance <= 0) {
            throw std::invalid_argument("ERROR: Укажите существующие станции и положительную длину дороги");
        }
        roads[from].push_back({to, distance});
        roads[to].push_back({from, distance});
    }

    const std::vector<Station>& get_stations() const { return stations; }

    std::vector<Route> shortest_routes_from(size_t start) const {
        // Алгоритм Дейкстры
        std::vector<Route> best(stations.size());
        best.at(start) = {{start}, 0};

        std::set<std::pair<int, size_t>> data{{0, start}}; // Пары (расстояние, станция) упорядочены от ближних к дальним
        while (!data.empty()) {
            auto [km, current] = *data.begin();
            data.erase(data.begin());
            if (km > best[current].distance) continue;

            for (const Road& road : roads[current]) {
                int new_distance = km + road.distance;
                Route& route = best[road.to];
                if (route.stops.empty() || new_distance < route.distance) {
                    route.stops = best[current].stops;
                    route.stops.push_back(road.to);
                    route.distance = new_distance;
                    data.emplace(new_distance, road.to);
                }
            }
        }

        std::vector<Route> routes;
        for (const Route& route : best) {
            if (route.stops.size() > 1) routes.push_back(route);
        }
        return routes;
    }
};
