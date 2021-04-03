#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#include <iosfwd>
#include <vector>



class Employee {
public:

    Employee(std::string name, int32_t base_salary);
    ~Employee() {}

    virtual int salary() const { return 0; }

    virtual std::ostream & print(std::ostream &out) const;
    virtual std::ofstream & print(std::ofstream &out) const;
    static void read_employee(std::istream &in, Employee *&employee);
    static void read_employee(std::ifstream &in, Employee *&employee);

    friend std::istream& operator>>(std::istream&, Employee*&);
    friend std::ifstream& operator>>(std::ifstream&, Employee*&);

    friend std::ofstream& operator<<(std::ofstream&, const Employee&);
    friend std::ostream& operator<<(std::ostream&, const Employee&);
protected:
    std::string _name;
    int32_t _base_salary;

};


class Developer : public Employee {
public:
    explicit Developer(std::string name = "", int base_salary = 0, bool has_bonus = 0);

    int salary() const override {
        int salary = _base_salary;
        if (_has_bonus) { salary += 1000; }
        return salary;
    }

    std::ostream & print(std::ostream &out) const override;
    std::ofstream & print(std::ofstream &out) const override;

    friend std::istream& operator>>(std::istream&, Developer*&);
    friend std::ifstream& operator>>(std::ifstream&, Developer*&);

private:
    bool _has_bonus;
};

class SalesManager : public Employee {
public:
    explicit SalesManager(std::string name = "", int base_salary = 0, int sold_nm = 0, int price = 0);

    int salary() const override {
        return _base_salary + _sold_nm * _price * 0.01;
    }

    std::ostream & print(std::ostream &out) const override;
    std::ofstream & print(std::ofstream &out) const override;

    friend std::istream& operator>>(std::istream&, SalesManager*&);
    friend std::ifstream& operator>>(std::ifstream&, SalesManager*&);

private:
    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    EmployeesArray() = default;
    ~EmployeesArray();
    void add(Employee *e);

    int total_salary() const;


    friend std::ostream& operator<<(std::ostream&, const EmployeesArray&);
    friend std::ofstream& operator<<(std::ofstream&, const EmployeesArray&);
    friend std::ifstream& operator>>(std::ifstream&, EmployeesArray&);

private:
    std::vector<Employee *>_employees;
};



#endif
