#include <iostream>
#include <string>
#include <vector>

class Box;

class Ball {
    std::string color;
    Box* owner_box;
public:
    Ball(std::string color_, Box* owner_box_): color(color_), owner_box(owner_box_) {}
    Ball(std::string color_): color(color_), owner_box(nullptr) {}
    std::string get_color() { return color; }
    Box* get_owner_box() { return owner_box; }
    void set_color(std::string color_) { color = color_; }
    void set_owner_box(Box* owner_box_) { owner_box = owner_box_; }
};

class Box {
    double width;
    double length;
    double height;
    std::vector<Ball*> balls;
public:
    Box(double width_, double length_, double height_):
        width(width_),
        length(length_),
        height(height_) {}
    Box(double width_, double length_, double height_, std::vector<Ball*> balls_): 
        width(width_),
        length(length_),
        height(height_),
        balls(balls_)
    {
        for (auto ball : balls) {
            ball->set_owner_box(this);
        }
    }
    double get_volume() { return width * length * height; }
    void add_ball(Ball* ball) {
        balls.push_back(ball);
        ball->set_owner_box(this);
    }
    std::vector<Ball*> get_balls() { return balls; }
    void remove_ball(Ball* ball) {
        for (auto it = balls.begin(); it != balls.end(); ++it) {
            if (*it == ball) {
                balls.erase(it);
                ball->set_owner_box(nullptr);
                break;
            }
        }
    }
    ~Box() {
        for (auto ball : balls) {
            delete ball;
        }
    }
};

int main() {
    Box box1(1, 2, 3);

    Box box2(4, 5, 6,
        {new Ball("red"), new Ball("blue")}
    );

    std::cout << "Адрес первой коробки: " << &box1 << '\n';
    std::cout << "Объем первой коробки: " << box1.get_volume() << '\n';
    std::cout << "Шаров в первой коробке: "
              << box1.get_balls().size() << '\n';

    std::cout << '\n';

    std::cout << "Адрес второй коробки: " << &box2 << '\n';
    std::cout << "Объем второй коробки: " << box2.get_volume() << '\n';
    std::cout << "Шаров во второй коробке: "
              << box2.get_balls().size() << '\n';

    for (auto ball : box2.get_balls()) {
        std::cout << "Цвет шара: " << ball->get_color() << '\n';
        std::cout << "Адрес коробки в шаре: "
                  << ball->get_owner_box() << '\n';
        std::cout << "Объем коробки: "
                  << ball->get_owner_box()->get_volume() << '\n';
    }

    return 0;
}