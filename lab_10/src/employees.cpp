#include <iostream>
#include <fstream>
#include <cassert>
#include "employees.h"

enum EmployeeType {
    DEVELOPER = 1,
    SALES_MANAGER = 2
};

void read_str_from_file(std::ifstream &in, std::string &string) {
    char next;
    while (in.get(next)) {
        if (in.fail()) {
            std::cerr << "Couldn't find 0 in the file";
            exit(0);
        }
        if (next == '\0') break;
        string += next;
    }
}

Employee::Employee(std::string name, const int32_t base_salary)
        : _name(name), _base_salary(base_salary){}

SalesManager::SalesManager(std::string name, int base_salary, int sold_nm, int price)
        : Employee(name, base_salary), _sold_nm(sold_nm), _price(price) {}

Developer::Developer(std::string name, int base_salary, bool has_bonus)
        : Employee(name, base_salary), _has_bonus(has_bonus) {}

std::istream &operator>>(std::istream &in, Developer *&dev) {
    if (!(in >> dev->_name >> dev->_base_salary >> dev->_has_bonus)) {
        std::cerr << "Couldn't read DEVELOPER fields from the stdin";
        return in;
    }

    return in;
}

std::ifstream &operator>>(std::ifstream &in, Developer *&dev) {
    read_str_from_file(in, dev->_name);
    in.read(reinterpret_cast<char *>(&dev->_base_salary), sizeof(dev->_base_salary));
    in.read(reinterpret_cast<char *>(&dev->_has_bonus), sizeof(dev->_has_bonus));
    if (in.fail()) {
        std::cerr << "Couldn't read DEVELOPER from the file";
        exit(EXIT_FAILURE);
    }
    return in;
}

std::istream &operator>>(std::istream &in, SalesManager *&sal_man) {
    if (!(in >> sal_man->_name >> sal_man->_base_salary >> sal_man->_sold_nm >> sal_man->_price)) {
        std::cerr << "Couldn't read SALES_MANAGER fields from the stdin";
    }
    return in;
}

std::ifstream &operator>>(std::ifstream &in, SalesManager *&sal_man) {
    read_str_from_file(in, sal_man->_name);
    in.read(reinterpret_cast<char *>(&sal_man->_base_salary), sizeof(sal_man->_base_salary));
    in.read(reinterpret_cast<char *>(&sal_man->_sold_nm), sizeof(sal_man->_sold_nm));
    in.read(reinterpret_cast<char *>(&sal_man->_price), sizeof(sal_man->_price));
    if (in.fail()) {
        std::cerr << "Couldn't read SALES_MANAGER from the file";
        exit(EXIT_FAILURE);
    }
    return in;
}


void Employee::read_employee(std::istream &in, Employee *&employee) {
    int type;
    if (!(in >> type)) {
        std::cerr << "Couldn't read employee type the stdin";
        return;
    }
    switch (type) {
        case EmployeeType::DEVELOPER: {
            auto new_dev = new Developer();
            in >> new_dev;
            employee = new_dev;
            return;
        }
        case EmployeeType::SALES_MANAGER: {
            auto new_sal_man = new SalesManager();
            in >> new_sal_man;
            employee = new_sal_man;
            return;
        }
        default:
            assert("Wrong employee type");
            return;

    }
}

void Employee::read_employee(std::ifstream &in, Employee *&employee) {
    int type;

    if (!(in.read(reinterpret_cast<char *>(&type), sizeof(type)))) {
        if (in.eof())
            return;
        std::cerr << "Couldn't read employee type from the file";
        return;
    }
    switch (type) {
        case EmployeeType::DEVELOPER: {
            auto new_dev = new Developer();
            in >> new_dev;
            employee = new_dev;
            return;
        }
        case EmployeeType::SALES_MANAGER: {
            auto new_sal_man = new SalesManager();
            in >> new_sal_man;
            employee = new_sal_man;
            return;
        }
        default:
            assert("Wrong employee type");
            return;
    }
}

std::ostream & Employee::print(std::ostream &out) const {
    if (!(out << "Name: " << _name << '\n')) {
        std::cerr << "Couldn't write name field to the stdin";
        return out;
    }
    if (!(out << "Base Salary: " << _base_salary << '\n'))
        std::cerr << "Couldn't write base_salary field to the stdin";
    return out;
}

std::ofstream &Employee::print(std::ofstream &out) const {
    if (!out.write(_name.c_str(), _name.size() * sizeof(char)) || !out.put('\0')) {
        std::cerr << "Couldn't write name to file!";
        return out;
    }
    if (!out.write((char *)&_base_salary, sizeof(_base_salary))) {
        std::cerr << "Couldn't write base_salary to file!";
        return out;
    }
    return out;
}

std::ostream &Developer::print(std::ostream &out) const {
    out << "Developer\n";
    Employee::print(out);
    if (!(out << "Has bonus: " << (_has_bonus ? '+' : '-') << '\n')) {
        std::cerr << "Couldn't write has_bonus field to the stdin";
    }
    return out;
}

std::ofstream &Developer::print(std::ofstream &out) const {
    int current_emp_type = EmployeeType::DEVELOPER; // костыль. Посоветуйте, пожалуйста, как исправить.
    if (!out.write((char *)&current_emp_type, sizeof(current_emp_type))) {
        std::cerr << "Couldn't write emp_type to the file";
        return out;
    }
    Employee::print(out);
    if (!(out.write((char *)&_has_bonus, sizeof(_has_bonus)))) {
        std::cerr << "Couldn't write has_bonus field to the file";
    }
    return out;
}


std::ostream &SalesManager::print(std::ostream &out) const {
    out << "Sales Manager\n";
    Employee::print(out);
    return (out << "Sold items: " << _sold_nm << '\n' <<
                    "Item price: " << _price << '\n');
}
std::ofstream &SalesManager::print(std::ofstream &out) const {
    int current_emp_type = EmployeeType::SALES_MANAGER;
    if (!out.write((char *)&current_emp_type, sizeof(current_emp_type))) {
        std::cerr << "Couldn't write employee type to the file";
        return out;
    }
    Employee::print(out);
    if (!out.write((char *)(&_sold_nm), sizeof(_sold_nm))) {
        std::cerr << "Couldn't write sold_nm to the file";
        return out;
    }
    if (!out.write((char *)(&_price), sizeof(_price))) {
        std::cerr << "Couldn't write price to the file";
        return out;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const Employee &employee) {
    if (!employee.print(out)) {
        std::cerr << "Couldn't show employee\n";
        exit(EXIT_FAILURE);
    }
    return out;
}

std::istream &operator>>(std::istream &in, Employee *&employee) {
    Employee::read_employee(in, employee);

    return in;
}

std::ofstream &operator<<(std::ofstream &out, const Employee &employee) {
    if (!employee.print(out)) {
        std::cerr << "Couldn't write employee\n";
        exit(EXIT_FAILURE);

    }
    return out;
}


std::ifstream &operator>>(std::ifstream &in, Employee *&employee) {
    Employee::read_employee(in, employee);

    return in;
}

std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &employeesArray) {
    int quantity = employeesArray._employees.size();
    out.write((const char *) &quantity, sizeof(quantity));
    for (int i = 0; i < quantity; i++) {
        out << *(employeesArray._employees[i]);
    }
    if (!out) {
        std::cerr << "Couldn't write employees array!";
        exit(EXIT_FAILURE);
    }
    return out;
}
void EmployeesArray::add(Employee *e) {
    _employees.push_back(e);
}

int EmployeesArray::total_salary() const {
    int result = 0;
    for (auto employee : _employees) {
        result += employee->salary();
    }
    return result;
}
std::ostream &operator<<(std::ostream &out, const EmployeesArray &employeesArray) {
    for (int i = 0; i < employeesArray._employees.size(); i++) {
        out << i + 1 << ". ";
        if (!(out << *(employeesArray._employees[i]))) {
            std::cerr << "Couldn't show employee from the array!";
            exit(EXIT_FAILURE);
        }
    }
    if (!(out << "== Total salary: " << employeesArray.total_salary() << "\n\n")) {
        std::cerr << "Couldn't show total salary!";
        exit(EXIT_FAILURE);
    }

    return out;
}

EmployeesArray::~EmployeesArray() {
    while (!_employees.empty()) {
        delete _employees.back();
        _employees.pop_back();
    }
}

std::ifstream &operator>>(std::ifstream &in, EmployeesArray &employeesArray) {
    int quantity;
    in.read((char *) &quantity, sizeof(quantity));

    for (int i = 0; i < quantity; i++) {
        Employee *new_emp;
        in >> new_emp;
        if (!in.eof() && in.bad()) {
            std::cerr << "Couldn't read employee!";
            exit(EXIT_FAILURE);
        }
        employeesArray.add(new_emp);
    }
    return in;
}