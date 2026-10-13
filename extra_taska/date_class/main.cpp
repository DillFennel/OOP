#include <iostream>

#include "date.hpp"

int main() {
    // Проверим конструктор с параметрами
    Date date1(4, 11, 2005);
    // Проверим методы GetDay(), GetMonth(), GetYear()
    std::cout << "Первая дата (конструктор с параметрами): " << date1.GetDay() << "." << date1.GetMonth() << "." << date1.GetYear() << std::endl;
    std::cout << "В днях: " << date1.ToDays() << std::endl;
    std::cout << std::endl;

    // Проверим перегрузки - и + с int
    Date date_plus_one = date1 + 1;
    Date date_minus_one = date1 - 1;
    std::cout << "Первая дата + 1: " << date_plus_one.GetDay() << "." << date_plus_one.GetMonth() << "." << date_plus_one.GetYear() << std::endl;
    std::cout << "В днях: " << date_plus_one.ToDays() << std::endl;
    std::cout << "Первая дата - 1: " << date_minus_one.GetDay() << "." << date_minus_one.GetMonth() << "." << date_minus_one.GetYear() << std::endl;
    std::cout << "В днях:" << date_minus_one.ToDays() << std::endl;
    std::cout << std::endl;

    // Проверим конструктор по умолчанию
    Date date2;
    std::cout << "Вторая дата (конструктор по умолчанию): " << date2.GetDay() << "." << date2.GetMonth() << "." << date2.GetYear() << std::endl;
    std::cout << std::endl;

    // Проверим конструктор копирования
    Date date3 = Date(6, 11, 2005);
    std::cout << "Третья дата (конструктор копирования): " << date3.GetDay() << "." << date3.GetMonth() << "." << date3.GetYear() << std::endl;
    std::cout << std::endl;

    // Проверим перегрузку для - с Date
    int date_diff = date3 - date1;
    std::cout << "Результат вычитания первой даты из третьей: " << date_diff << std::endl;
    std::cout << std::endl;

    // Проверим конструктор перемещения
    Date date4 = std::move(date3);
    std::cout << "Четвая дата (конструктор перемещения): " << date4.GetDay() << "." << date4.GetMonth() << "." << date4.GetYear() << std::endl;
    std::cout << "Третья дата (после перемещения в четвертую дату): " << date3.GetDay() << "." << date3.GetMonth() << "." << date3.GetYear() << std::endl;
    std::cout << std::endl;
    
    // Должны вызваться деструкторы для всех дат
    std::cout << "Сейчас будут вызваны деструкторы для всех дат, причем в обратном порядке, как мы их создавали. Это демонстрирует, как они хранятся на стеке" << std::endl;
    return 0;
}