#include <iostream>
#include <string>
#include <map>

class Student {
    std::string name;
    std::map<std::string, int> grades; // предмет -> оценка
public:
    std::string get_name() {
        return name;
    }
    std::map<std::string, int> get_grades() {
        return grades;
    }
    Student(){};
    Student(std::string name_):
        name(name_) {}
    Student(std::string name_, std::map<std::string, int> grades_):
        name(name_),
        grades(grades_) {}
    void set_grade(std::string subject_, int grade_) {
        grades[subject_] = grade_;
    }
    void set_name(std::string name_) {
        name = name_;
    }
};

void print_grades(std::map<std::string, int> grades) {
    for (auto i: grades) {
        std::cout << i.first << ": " << i.second << std::endl;
    }
    std::cout << std::endl;
}

int main() {

    Student s1("Иван");
    std::cout << "Первого студента зовут " << s1.get_name() << std::endl;
    std::cout << "У него вот такие оценки: " << std::endl;
    print_grades(s1.get_grades());

    Student s2("Олег", {{"математика", 4}, {"алгебра", 5}});
    std::cout << "Второго студента зовут " << s2.get_name() << std::endl;
    std::cout << "У него вот такие оценки: " << std::endl;
    print_grades(s2.get_grades());

    std::cout << "Поменяем Олегу имя на Игнат" << std::endl;
    s2.set_name("Игнат");
    std::cout << "Проверим новое имя: " << s2.get_name() << std::endl;
    std::cout << std::endl;

    std::cout << "Добавим оценку 3 по выш. мату " << std::endl;
    s2.set_grade("выш. мат", 3);
    std::cout << "Проверим новые оценки Игната: " << std::endl;
    print_grades(s2.get_grades());
}