#include "bike_network.hpp"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
    // assert проверяет условие. Если оно неверно, тест останавливается.
    BikeNetwork network;
    network.add_station({"Парк", 10, 5, 5});         // станция 0
    network.add_station({"Метро", 10, 5, 5});        // станция 1
    network.add_station({"Университет", 10, 5, 5});  // станция 2
    network.add_station({"Стадион", 10, 5, 5});      // станция 3

    // 1. Дорога от парка до метро имеет длину 2 и работает в обе стороны.
    network.add_road(0, 1, 2);
    std::vector<Route> routes = network.shortest_routes_from(0);
    std::vector<size_t> expected = {0, 1};
    assert(routes.size() == 1);
    assert(routes[0].distance == 2);
    assert(routes[0].stops == expected);

    routes = network.shortest_routes_from(1);
    expected = {1, 0};
    assert(routes.size() == 1);
    assert(routes[0].distance == 2);
    assert(routes[0].stops == expected);

    // 2. До университета через метро 2 + 1 = 3 км, напрямую 5 км.
    network.add_road(1, 2, 1);
    network.add_road(0, 2, 5);
    routes = network.shortest_routes_from(0);
    assert(routes.size() == 2);
    // routes[0] ведёт к метро, routes[1] — к университету.
    expected = {0, 1};
    assert(routes[0].distance == 2);
    assert(routes[0].stops == expected);
    expected = {0, 1, 2};
    assert(routes[1].distance == 3);
    assert(routes[1].stops == expected);

    // 3. Добавляем прямую дорогу длиной 3 км. Оба пути одинаково короткие.
    network.add_road(0, 2, 3);
    routes = network.shortest_routes_from(0);
    std::vector<size_t> direct = {0, 2};
    assert(routes.size() == 2);
    assert(routes[1].distance == 3);
    assert(routes[1].stops == expected || routes[1].stops == direct);

    // 4. Новая прямая дорога длиной 1 км стала самым коротким путём.
    network.add_road(0, 2, 1);
    network.add_road(0, 2, 5); // Между теми же станциями есть и более длинная дорога.
    routes = network.shortest_routes_from(0);
    assert(routes.size() == 2);
    assert(routes[1].distance == 1);
    assert(routes[1].stops == direct);

    // 5. К стадиону дорог нет. Из него тоже нельзя никуда доехать.
    assert(network.shortest_routes_from(3).empty());

    // Для проверок перевозок создаём сеть с избытком и нехваткой велосипедов.
    BikeNetwork city;
    city.add_station({"Парк", 10, 8, 4});         // станция 0, лишних 4
    city.add_station({"Метро", 8, 1, 4});         // станция 1, не хватает 3
    city.add_station({"Университет", 8, 2, 5});   // станция 2, не хватает 3
    city.add_station({"Стадион", 6, 5, 4});       // станция 3, лишний 1
    city.add_road(0, 1, 2);
    city.add_road(1, 2, 1);
    city.add_road(0, 2, 5);
    city.add_road(3, 2, 1);

    // 6. Всего не хватает 6 велосипедов, а лишних только 5.
    BikeNetwork morning = city; // Копируем сеть для расчёта.
    std::vector<Transfer> transfers = morning.rebalance();
    assert(transfers.size() == 3);

    // Сначала везём 1 велосипед со стадиона в университет.
    expected = {3, 2};
    assert(transfers[0].route.stops == expected);
    assert(transfers[0].route.distance == 1);
    assert(transfers[0].bikes == 1);

    // Затем 3 велосипеда из парка к метро.
    expected = {0, 1};
    assert(transfers[1].route.stops == expected);
    assert(transfers[1].route.distance == 2);
    assert(transfers[1].bikes == 3);

    // Оставшийся велосипед из парка везём в университет через метро.
    expected = {0, 1, 2};
    assert(transfers[2].route.stops == expected);
    assert(transfers[2].route.distance == 3);
    assert(transfers[2].bikes == 1);

    assert(morning.get_stations().size() == 4);
    for (Station station : morning.get_stations()) {
        assert(station.get_bikes() == 4);
    }
    assert(morning.get_stations()[2].get_diff() == 1);

    // Расчёт плана меняет копию станций.
    assert(city.get_stations()[0].get_bikes() == 8);
    assert(city.get_stations()[1].get_bikes() == 1);
    assert(city.get_stations()[2].get_bikes() == 2);
    assert(city.get_stations()[3].get_bikes() == 5);
    assert(morning.rebalance().empty()); // Все возможные перевозки уже выполнены.

    // 7. У вокзала есть лишние велосипеды, но дорог от него нет.
    city.add_station({"Вокзал", 10, 8, 4}); // станция 4
    morning = city;
    transfers = morning.rebalance();
    assert(transfers.size() == 3);
    assert(morning.get_stations().size() == 5);
    assert(morning.get_stations()[4].get_bikes() == 8);
    assert(morning.get_stations()[2].get_diff() == 1);

    std::cout << "Все 7 тестов пройдены.\n";
}
