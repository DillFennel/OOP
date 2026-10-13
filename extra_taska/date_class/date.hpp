#include <iostream>
#include <stdexcept>

class Date {
private:
    int day_, month_, year_;

    static bool IsLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    static int DaysInMonth(int month, int year) {
        static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && IsLeapYear(year))
            return 29;
        return days[month - 1];
    }

    bool IsValidDate(int day, int month, int year) const {
        if (year < 1970 || year > 2099)
            return false;
        if (month < 1 || month > 12)
            return false;
        if (day < 1 || day > DaysInMonth(month, year))
            return false;
        return true;
    }

public:
    int ToDays() const {
        int total_days = 0;
        for (int y = 1970; y < year_; ++y) {
            total_days += IsLeapYear(y) ? 366 : 365;
        }
        for (int m = 1; m < month_; ++m) {
            total_days += DaysInMonth(m, year_);
        }
        total_days += day_ - 1;
        return total_days;
    }

    void FromDays(int days) {
        day_ = 1;
        month_ = 1;
        year_ = 1970;

        while (days > 0) {
            int days_in_year = IsLeapYear(year_) ? 366 : 365;
            if (days >= days_in_year) {
                days -= days_in_year;
                year_++;
            } else {
                break;
            }
        }

        while (days > 0) {
            int days_in_month = DaysInMonth(month_, year_);
            if (days >= days_in_month) {
                days -= days_in_month;
                month_++;
            } else {
                break;
            }
        }

        day_ += days;
    }

    Date() {
        std::cout << "Вызван коснструктор по умолчанию" << std::endl;
        day_ = 1;
        month_ = 1;
        year_ = 1970;
    }

    Date(int day, int month, int year) {
        std::cout << "Вызван коснструктор с параметрами" << std::endl;
        if (IsValidDate(day, month, year)) {
            day_ = day;
            month_ = month;
            year_ = year;
        } else {
            day_ = 1;
            month_ = 1;
            year_ = 1970; 
        }
    }

    Date(const Date& other) { // Используем константную lvalue ссылку. Показывает, что передается именнованный объект, который нужно оставить прежним
        std::cout << "Вызван коснструктор копирования" << std::endl;
        day_ = other.day_;
        month_ = other.month_;
        year_ = other.year_;
    }

    Date(Date&& other) noexcept { // Используем rvalue ссылку. Показывает, что передается временный объект, у которого можем все забрать и изменить его состояние
        std::cout << "Вызван коснструктор перемещения" << std::endl;
        day_ = other.day_;
        month_ = other.month_;
        year_ = other.year_;
        
        other.day_ = 1;
        other.month_ = 1;
        other.year_ = 1970;
    }

    ~Date() {
        std::cout << "Вызван деструктор для даты " << day_ << "." << month_ << "." << year_ << "" << std::endl;
    }

    int GetDay() const { return day_; }
    int GetMonth() const { return month_; }
    int GetYear() const { return year_; }

    Date operator+(int days) const {
        std::cout << "Вызвана перегрузка оператора +" << std::endl;
        Date result = *this;
        result.FromDays(result.ToDays() + days);
        if (!result.IsValidDate(result.day_, result.month_, result.year_)) {
            throw std::invalid_argument("При сложении получилась невалидная дата!"); 
        }
        return result;
    }

    Date operator-(int days) const {
        std::cout << "Вызвана перегрузка оператора - с int" << std::endl;
        Date result = *this;
        result.FromDays(result.ToDays() - days);
        if (!result.IsValidDate(result.day_, result.month_, result.year_)) {
            throw std::invalid_argument("При вычитании получилась невалидная дата!"); 
        }
        return result;
    }

    int operator-(const Date& other) const {
        // Date передается через ссылку, чтобы избежать копирования
        std::cout << "Вызвана перегрузка оператора - с Date&" << std::endl;
        return this->ToDays() - other.ToDays();
    }
};