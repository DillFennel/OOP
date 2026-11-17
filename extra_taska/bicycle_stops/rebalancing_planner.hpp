#pragma once

#include "bike_network.hpp"

#include <algorithm>
#include <utility>
#include <vector>

struct Transfer {
    Route route;
    int bikes;
};

struct RebalancingPlan {
    std::vector<Station> final_stations;
    std::vector<Transfer> transfers;
};

class RebalancingPlanner {
public:
    static RebalancingPlan build(const BikeNetwork& network) {
        const auto& stations = network.get_stations();
        std::vector<Route> candidates;
        for (std::size_t from = 0; from < stations.size(); ++from) {
            if (stations[from].get_diff() >= 0) continue;

            for (Route& route : network.shortest_routes_from(from)) {
                if (stations[route.stops.back()].get_diff() > 0) {
                    candidates.push_back(std::move(route));
                }
            }
        }
        std::stable_sort(candidates.begin(), candidates.end(), [](const Route& a, const Route& b) {
            return a.distance < b.distance;
        });

        RebalancingPlan plan{stations, {}};
        for (Route& route : candidates) {
            Station& from = plan.final_stations[route.stops.front()];
            Station& to = plan.final_stations[route.stops.back()];
            int count = from.transfer_to(to);
            if (count > 0) {
                plan.transfers.push_back({std::move(route), count});
            }
        }
        return plan;
    }
};
