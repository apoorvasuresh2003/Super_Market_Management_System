#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Product structure
struct Product {
    int productNumber;
    string name;
    double price;
    int quantity;
    double discount; // Discount for the product (in percentage)

    // Constructor
    Product(int num, const string& n, double p, int q, double d)
        : productNumber(num), name(n), price(p), quantity(q), discount(d) {}
};

// Supermarket class
class Supermarket {
private:
    vector<Product> inventory;

public:
    // Add a product to the inventory
    void addProduct(const Product& product) {
        inventory.push_back(product);
        cout << "Product added to the inventory.\n";
    }

    // Remove a product from the inventory
    void removeProduct(int productNumber) {
        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if (it->productNumber == productNumber) {
                inventory.erase(it);
                cout << "Product removed from the inventory.\n";
                return;
            }
        }
        cout << "Product not found in inventory.\n";
    }

    // Display all products in the inventory
    void displayInventory() {
        if (inventory.empty()) {
            cout << "Inventory is empty.\n";
            return;
        }

        cout << "Inventory:\n";
        cout << setw(10) << left << "Product #" << setw(15) << "Product Name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(10) << "Discount (%)\n";
        cout << "------------------------------------------------------------\n";
        for (const auto& product : inventory) {
            cout << setw(10) << product.productNumber << setw(15) << product.name << setw(10) << product.price << setw(10) << product.quantity << setw(10) << product.discount << endl;
        }
        cout << endl;
    }

    // Process a sale
    double processSale(const vector<pair<int, int>>& items) {
        double totalAmount = 0;
        for (const auto& item : items) {
            int productNumber = item.first;
            int quantity = item.second;

            for (auto& product : inventory) {
                if (product.productNumber == productNumber) {
                    if (product.quantity >= quantity) {
                        double itemAmount = product.price * quantity;
                        itemAmount -= itemAmount * (product.discount / 100.0);
                        product.quantity -= quantity;
                        totalAmount += itemAmount;
                        break;
                    } else {
                        cout << "Insufficient quantity for product #" << productNumber << " in stock.\n";
                        break;
                    }
                }
            }
        }
        return totalAmount;
    }

    // Set discount for a product
    void setDiscount(int productNumber, double discount) {
        for (auto& product : inventory) {
            if (product.productNumber == productNumber) {
                product.discount = discount;
                cout << "Discount set for the product.\n";
                return;
            }
        }
        cout << "Product not found in inventory.\n";
    }

    // Modify a product in the inventory
    void modifyProduct(int productNumber) {
        for (auto& product : inventory) {
            if (product.productNumber == productNumber) {
                int option;
                cout << "Select attribute to modify:\n";
                cout << "1. Product Name\n";
                cout << "2. Price\n";
                cout << "3. Quantity\n";
                cout << "4. Discount\n";
                cout << "Enter your choice: ";
                cin >> option;

                switch (option) {
                    case 1: {
                        string newName;
                        cout << "Enter new product name: ";
                        cin.ignore();
                        getline(cin, newName);
                        product.name = newName;
                        cout << "Product name modified.\n";
                        break;
                    }
                    case 2: {
                        double newPrice;
                        cout << "Enter new price: ";
                        cin >> newPrice;
                        product.price = newPrice;
                        cout << "Price modified.\n";
                        break;
                    }
                    case 3: {
                        int newQuantity;
                        cout << "Enter new quantity: ";
                        cin >> newQuantity;
                        product.quantity = newQuantity;
                        cout << "Quantity modified.\n";
                        break;
                    }
                    case 4: {
                        double newDiscount;
                        cout << "Enter new discount (%): ";
                        cin >> newDiscount;
                        product.discount = newDiscount;
                        cout << "Discount modified.\n";
                        break;
                    }
                    default:
                        cout << "Invalid option.\n";
                }

                return;
            }
        }
        cout << "Product not found in inventory.\n";
    }

    // Get the inventory vector
    vector<Product>& getInventory() {
        return inventory;
    }
};

int main() {
    Supermarket supermarket;

    int userType;
    bool isRunning = true;

    while (isRunning) {
        cout << "Select User Type:\n";
        cout << "1. Admin\n";
        cout << "2. Customer\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> userType;

        if (userType == 1) {
            // Admin operations
            string username, password;
            cout << "Admin Login\n";
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            // Check admin credentials
            if (username == "admin" && password == "admin123") {
                int adminOption;
                while (true) {
                    cout << "\nAdmin Operations\n";
                    cout << "1. Add Product\n";
                    cout << "2. Remove Product\n";
                    cout << "3. Display Inventory\n";
                    cout << "4. Set Discount\n";
                    cout << "5. Modify Product\n";
                    cout << "6. Exit\n";
                    cout << "Enter your option: ";
                    cin >> adminOption;

                    switch (adminOption) {
                        case 1: {
                            int productNumber;
                            string productName;
                            double price;
                            int quantity;
                            double discount;
                            cout << "Enter product number: ";
                            cin >> productNumber;
                            cout << "Enter product name: ";
                            cin.ignore(); // Ignore the newline character in the input buffer
                            getline(cin, productName);
                            cout << "Enter product price: ";
                            cin >> price;
                            cout << "Enter product quantity: ";
                            cin >> quantity;
                            cout << "Enter product discount (%): ";
                            cin >> discount;
                            supermarket.addProduct(Product(productNumber, productName, price, quantity, discount));
                            break;
                        }
                        case 2: {
                            int productNumber;
                            cout << "Enter product number: ";
                            cin >> productNumber;
                            supermarket.removeProduct(productNumber);
                            break;
                        }
                        case 3:
                            supermarket.displayInventory();
                            break;
                        case 4: {
                            int productNumber;
                            double discount;
                            cout << "Enter product number: ";
                            cin >> productNumber;
                            cout << "Enter product discount (%): ";
                            cin >> discount;
                            supermarket.setDiscount(productNumber, discount);
                            break;
                        }
                        case 5: {
                            int productNumber;
                            cout << "Enter product number: ";
                            cin >> productNumber;
                            supermarket.modifyProduct(productNumber);
                            break;
                        }
                        case 6:
                            cout << "Exiting admin operations...\n";
                            break;
                        default:
                            cout << "Invalid option. Please try again.\n";
                    }

                    if (adminOption == 6)
                        break;
                }
            } else {
                cout << "Invalid username or password.\n";
            }
        } else if (userType == 2) {
            // Customer operations
            int customerOption;
            vector<pair<int, int>> cart; // Pair of product number and quantity

            while (true) {
                cout << "\nCustomer Operations\n";
                cout << "1. Display Inventory\n";
                cout << "2. Add Product to Cart\n";
                cout << "3. Remove Product from Cart\n";
                cout << "4. View Cart\n";
                cout << "5. Process Sale\n";
                cout << "6. Exit\n";
                cout << "Enter your option: ";
                cin >> customerOption;

                switch (customerOption) {
                    case 1:
                        supermarket.displayInventory();
                        break;
                    case 2: {
                        int productNumber;
                        int quantity;
                        cout << "Enter product number: ";
                        cin >> productNumber;
                        cout << "Enter quantity: ";
                        cin >> quantity;
                        cart.push_back(make_pair(productNumber, quantity));
                        cout << "Product added to cart.\n";
                        break;
                    }
                    case 3: {
                        int productNumber;
                        cout << "Enter product number: ";
                        cin >> productNumber;
                        for (auto it = cart.begin(); it != cart.end(); ++it) {
                            if (it->first == productNumber) {
                                cart.erase(it);
                                cout << "Product removed from cart.\n";
                                break;
                            }
                        }
                        break;
                    }
                    case 4: {
                        cout << "Cart:\n";
                        cout << setw(10) << left << "Product #" << setw(15) << "Product Name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(10) << "Discount (%)\n";
                        cout << "------------------------------------------------------------\n";
                        for (const auto& item : cart) {
                            int productNumber = item.first;
                            int quantity = item.second;

                            for (const auto& product : supermarket.getInventory()) {
                                if (product.productNumber == productNumber) {
                                    cout << setw(10) << product.productNumber << setw(15) << product.name << setw(10) << product.price << setw(10) << quantity << setw(10) << product.discount << endl;
                                    break;
                                }
                            }
                        }
                        cout << endl;
                        break;
                    }
                    case 5: {
                        double totalAmount = supermarket.processSale(cart);
                        cout << "Total amount: $" << fixed << setprecision(2) << totalAmount << endl;
                        cart.clear(); // Clear the cart after processing the sale
                        break;
                    }
                    case 6:
                        cout << "Exiting customer operations...\n";
                        break;
                    default:
                        cout << "Invalid option. Please try again.\n";
                }

                if (customerOption == 6)
                    break;
            }
        } else if (userType == 3) {
            cout << "Exiting the program...\n";
            isRunning = false;
        } else {
            cout << "Invalid user type.\n";
        }
    }

    return 0;
}