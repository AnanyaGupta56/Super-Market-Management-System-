#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <ctime>
#include <limits>
using namespace std;

// Forward declarations
class Product;
class Employee;
class Sale;

// Product class
class Product {
private:
    int id;
    string name;
    double price;
    int quantity;
    string category;
    string supplier;
    double discount;

public:
    Product(int id, string name, double price, int quantity, string category, string supplier)
        : id(id), name(name), price(price), quantity(quantity), category(category), supplier(supplier), discount(0.0) {}

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    string getCategory() const { return category; }
    string getSupplier() const { return supplier; }
    double getDiscount() const { return discount; }

    // Setters
    void setPrice(double newPrice) { price = newPrice; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setDiscount(double newDiscount) { discount = newDiscount; }

    // Methods
    void updateStock(int amount) { quantity += amount; }
    double getDiscountedPrice() const { return price * (1 - discount); }
    bool isInStock() const { return quantity > 0; }
};

// Employee class
class Employee {
private:
    int id;
    string name;
    string position;
    double salary;
    string contact;
    string joinDate;

public:
    Employee(int id, string name, string position, double salary, string contact)
        : id(id), name(name), position(position), salary(salary), contact(contact) {
        time_t now = time(0);
        joinDate = ctime(&now);
    }

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    string getPosition() const { return position; }
    double getSalary() const { return salary; }
    string getContact() const { return contact; }
    string getJoinDate() const { return joinDate; }

    // Setters
    void setSalary(double newSalary) { salary = newSalary; }
    void setPosition(string newPosition) { position = newPosition; }
};

// Sale class
class Sale {
private:
    int id;
    vector<pair<Product*, int>> items;
    double totalAmount;
    time_t saleDate;
    string paymentMethod;
    double discount;

public:
    Sale(int id) : id(id), totalAmount(0.0), discount(0.0) {
        saleDate = time(0);
    }

    void addItem(Product* product, int quantity) {
        if (product->getQuantity() >= quantity) {
            items.push_back({product, quantity});
            totalAmount += product->getDiscountedPrice() * quantity;
            product->updateStock(-quantity);
        }
    }

    void setPaymentMethod(string method) { paymentMethod = method; }
    void setDiscount(double disc) { discount = disc; }
    double getTotalAmount() const { return totalAmount * (1 - discount); }
    int getId() const { return id; }
    time_t getSaleDate() const { return saleDate; }
    string getPaymentMethod() const { return paymentMethod; }
};

// Supermarket class
class Supermarket {
private:
    map<int, Product*> products;
    map<int, Employee*> employees;
    vector<Sale*> sales;
    int nextProductId;
    int nextEmployeeId;
    int nextSaleId;
    double dailyRevenue;
    double monthlyRevenue;

public:
    Supermarket() : nextProductId(1), nextEmployeeId(1), nextSaleId(1), dailyRevenue(0.0), monthlyRevenue(0.0) {}

    // Product Management
    void addProduct(string name, double price, int quantity, string category, string supplier) {
        Product* product = new Product(nextProductId++, name, price, quantity, category, supplier);
        products[product->getId()] = product;
    }

    void updateProduct(int id, double price, int quantity) {
        if (products.find(id) != products.end()) {
            products[id]->setPrice(price);
            products[id]->setQuantity(quantity);
        }
    }

    void removeProduct(int id) {
        if (products.find(id) != products.end()) {
            delete products[id];
            products.erase(id);
        }
    }

    // Employee Management
    void addEmployee(string name, string position, double salary, string contact) {
        Employee* employee = new Employee(nextEmployeeId++, name, position, salary, contact);
        employees[employee->getId()] = employee;
    }

    void updateEmployee(int id, double salary, string position) {
        if (employees.find(id) != employees.end()) {
            employees[id]->setSalary(salary);
            employees[id]->setPosition(position);
        }
    }

    void removeEmployee(int id) {
        if (employees.find(id) != employees.end()) {
            delete employees[id];
            employees.erase(id);
        }
    }

    // Sales Management
    Sale* createSale() {
        Sale* sale = new Sale(nextSaleId++);
        sales.push_back(sale);
        return sale;
    }

    void addToSale(Sale* sale, int productId, int quantity) {
        if (products.find(productId) != products.end()) {
            sale->addItem(products[productId], quantity);
        }
    }

    void completeSale(Sale* sale, string paymentMethod, double discount = 0.0) {
        sale->setPaymentMethod(paymentMethod);
        sale->setDiscount(discount);
        dailyRevenue += sale->getTotalAmount();
        monthlyRevenue += sale->getTotalAmount();
    }

    // Reporting
    void generateInventoryReport() {
        cout << "\n=== Inventory Report ===" << endl;
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Price" 
             << setw(10) << "Quantity" << setw(15) << "Category" << endl;
        cout << string(60, '-') << endl;

        for (const auto& pair : products) {
            Product* p = pair.second;
            cout << setw(5) << p->getId() << setw(20) << p->getName() 
                 << setw(10) << p->getPrice() << setw(10) << p->getQuantity() 
                 << setw(15) << p->getCategory() << endl;
        }
    }

    void generateSalesReport() {
        cout << "\n=== Sales Report ===" << endl;
        cout << "Daily Revenue: $" << fixed << setprecision(2) << dailyRevenue << endl;
        cout << "Monthly Revenue: $" << monthlyRevenue << endl;
    }

    void generateEmployeeReport() {
        cout << "\n=== Employee Report ===" << endl;
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(15) << "Position" 
             << setw(10) << "Salary" << setw(15) << "Contact" << endl;
        cout << string(65, '-') << endl;

        for (const auto& pair : employees) {
            Employee* e = pair.second;
            cout << setw(5) << e->getId() << setw(20) << e->getName() 
                 << setw(15) << e->getPosition() << setw(10) << e->getSalary() 
                 << setw(15) << e->getContact() << endl;
        }
    }

    // Destructor
    ~Supermarket() {
        for (auto& pair : products) delete pair.second;
        for (auto& pair : employees) delete pair.second;
        for (auto sale : sales) delete sale;
    }
};

// Helper function to get valid input
template<typename T>
T getValidInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again.\n";
    }
}

int main() {
    Supermarket supermarket;
    int choice;

    do {
        cout << "\n=== Supermarket Management System ===" << endl;
        cout << "1. Product Management" << endl;
        cout << "2. Employee Management" << endl;
        cout << "3. Sales Management" << endl;
        cout << "4. Reports" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n=== Product Management ===" << endl;
                cout << "1. Add Product" << endl;
                cout << "2. Update Product" << endl;
                cout << "3. Remove Product" << endl;
                cout << "4. View Products" << endl;
                cout << "Enter your choice: ";
                int subChoice;
                cin >> subChoice;

                switch (subChoice) {
                    case 1: {
                        string name, category, supplier;
                        double price;
                        int quantity;

                        cout << "Enter product name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter price: ";
                        cin >> price;
                        cout << "Enter quantity: ";
                        cin >> quantity;
                        cout << "Enter category: ";
                        cin.ignore();
                        getline(cin, category);
                        cout << "Enter supplier: ";
                        getline(cin, supplier);

                        supermarket.addProduct(name, price, quantity, category, supplier);
                        cout << "Product added successfully!" << endl;
                        break;
                    }
                    case 2: {
                        int id = getValidInput<int>("Enter product ID: ");
                        double price = getValidInput<double>("Enter new price: ");
                        int quantity = getValidInput<int>("Enter new quantity: ");
                        supermarket.updateProduct(id, price, quantity);
                        cout << "Product updated successfully!" << endl;
                        break;
                    }
                    case 3: {
                        int id = getValidInput<int>("Enter product ID: ");
                        supermarket.removeProduct(id);
                        cout << "Product removed successfully!" << endl;
                        break;
                    }
                    case 4:
                        supermarket.generateInventoryReport();
                        break;
                }
                break;
            }
            case 2: {
                cout << "\n=== Employee Management ===" << endl;
                cout << "1. Add Employee" << endl;
                cout << "2. Update Employee" << endl;
                cout << "3. Remove Employee" << endl;
                cout << "4. View Employees" << endl;
                cout << "Enter your choice: ";
                int subChoice;
                cin >> subChoice;

                switch (subChoice) {
                    case 1: {
                        string name, position, contact;
                        double salary;

                        cout << "Enter employee name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter position: ";
                        getline(cin, position);
                        cout << "Enter salary: ";
                        cin >> salary;
                        cout << "Enter contact: ";
                        cin.ignore();
                        getline(cin, contact);

                        supermarket.addEmployee(name, position, salary, contact);
                        cout << "Employee added successfully!" << endl;
                        break;
                    }
                    case 2: {
                        int id = getValidInput<int>("Enter employee ID: ");
                        double salary = getValidInput<double>("Enter new salary: ");
                        string position;
                        cout << "Enter new position: ";
                        cin.ignore();
                        getline(cin, position);
                        supermarket.updateEmployee(id, salary, position);
                        cout << "Employee updated successfully!" << endl;
                        break;
                    }
                    case 3: {
                        int id = getValidInput<int>("Enter employee ID: ");
                        supermarket.removeEmployee(id);
                        cout << "Employee removed successfully!" << endl;
                        break;
                    }
                    case 4:
                        supermarket.generateEmployeeReport();
                        break;
                }
                break;
            }
            case 3: {
                cout << "\n=== Sales Management ===" << endl;
                Sale* sale = supermarket.createSale();
                char addMore;
                do {
                    int productId = getValidInput<int>("Enter product ID: ");
                    int quantity = getValidInput<int>("Enter quantity: ");
                    supermarket.addToSale(sale, productId, quantity);
                    cout << "Add more items? (y/n): ";
                    cin >> addMore;
                } while (addMore == 'y' || addMore == 'Y');

                string paymentMethod;
                cout << "Enter payment method (cash/card): ";
                cin >> paymentMethod;
                double discount = getValidInput<double>("Enter discount (0-1): ");
                supermarket.completeSale(sale, paymentMethod, discount);
                cout << "Sale completed successfully!" << endl;
                break;
            }
            case 4: {
                cout << "\n=== Reports ===" << endl;
                cout << "1. Inventory Report" << endl;
                cout << "2. Sales Report" << endl;
                cout << "3. Employee Report" << endl;
                cout << "Enter your choice: ";
                int subChoice;
                cin >> subChoice;

                switch (subChoice) {
                    case 1:
                        supermarket.generateInventoryReport();
                        break;
                    case 2:
                        supermarket.generateSalesReport();
                        break;
                    case 3:
                        supermarket.generateEmployeeReport();
                        break;
                }
                break;
            }
            case 5:
                cout << "Thank you for using the Supermarket Management System!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
} 
