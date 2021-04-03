#include <iostream>
#include <fstream>
#include <employees.h>

int main() {
    EmployeesArray employeesArray;
    std::string next_action;
    while (std::cin >> next_action) {
        if (next_action == "exit") {
            break;
        } else if (next_action == "add") {
            Employee *new_emp;
            std::cin >> new_emp;
            employeesArray.add(new_emp);
        } else if (next_action == "list") {
            std::cout << employeesArray;
        } else if (next_action == "save") {
            std::string filename;
            if (!(std::cin >> filename)) {
                std::cerr << "Couldn't read filename\n";
                continue;
            }
            std::ofstream output;
            output.open(filename, std::ios::out | std::ios_base::binary);
            if (!output.is_open()) {
                std::cerr << "Couldn't open file " << filename << '\n';
                continue;
            }
            output.clear();
            output << employeesArray;
            output.close();
        } else if (next_action == "load") {
            std::string filename;
            if (!(std::cin >> filename)) {
                std::cerr << "Couldn't read filename\n";
                continue;
            }
            std::ifstream input;
            input.open (filename, std::ios::in | std::ios_base::binary);
            if (!input.is_open()) {
                std::cerr << "Couldn't open file " << filename << '\n';
                continue;
            }
            input >> employeesArray;
            input.close();
        } else {
            std::cout << "Wrong action name\n";
        }
    }

    return 0;
}