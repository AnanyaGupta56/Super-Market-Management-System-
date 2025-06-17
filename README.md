# Supermarket Management System

A comprehensive C++ application for managing supermarket operations, including inventory management, employee management, sales tracking, and reporting.

## Features

### Product Management
- Add new products with details (name, price, quantity, category, supplier)
- Update product information
- Remove products
- Track inventory levels
- Apply discounts to products
- Categorize products

### Employee Management
- Add new employees with details (name, position, salary, contact)
- Update employee information
- Remove employees
- Track employee join dates
- Manage employee positions and salaries

### Sales Management
- Process sales transactions
- Track multiple items per sale
- Apply discounts to sales
- Support different payment methods
- Maintain sales history
- Track daily and monthly revenue

### Reporting System
- Generate inventory reports
- Generate sales reports
- Generate employee reports
- Track revenue statistics
- View transaction history

## Prerequisites

- C++ compiler (supporting C++11 or later)
- Standard C++ libraries
- File system access for data persistence

## Compilation

To compile the project, use the following command:

```bash
g++ -std=c++11 supermarket.cpp -o supermarket
```

## Usage

1. Run the compiled program:
```bash
./supermarket
```

2. Main Menu Options:
   - 1: Product Management
   - 2: Employee Management
   - 3: Sales Management
   - 4: Reports
   - 5: Exit

### Product Management
- Add new products
- Update existing products
- Remove products
- View product inventory

### Employee Management
- Add new employees
- Update employee information
- Remove employees
- View employee list

### Sales Management
- Create new sales
- Add items to sale
- Apply discounts
- Process payments
- Complete transactions

### Reports
- View inventory status
- Check sales statistics
- View employee information
- Track revenue

## Data Structure

The system uses the following main classes:
- `Product`: Manages product information and inventory
- `Employee`: Handles employee data and management
- `Sale`: Processes sales transactions
- `Supermarket`: Main class coordinating all operations

## Error Handling

The system includes error handling for:
- Invalid input
- Insufficient stock
- Invalid product/employee IDs
- File I/O operations

## Future Improvements

Potential enhancements for future versions:
1. Database integration
2. User authentication system
3. Barcode scanning support
4. Supplier management
5. Customer loyalty program
6. Online ordering system
7. Advanced reporting features
8. Multi-branch support
9. Inventory alerts
10. Employee attendance tracking

## Contributing

Feel free to contribute to this project by:
1. Forking the repository
2. Creating a feature branch
3. Committing your changes
4. Pushing to the branch
5. Creating a Pull Request

## Acknowledgments

- Standard C++ libraries
- C++ community for best practices and guidelines 
