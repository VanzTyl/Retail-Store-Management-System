#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib> // For system("clear") / system("cls")
#include <iomanip> // For setprecision

using namespace std;

// ANSI color codes for terminal text
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string BLUE = "\033[34m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";

struct Product {
    string name;
    string category;
    double price;
    int stock;
};

class RetailSystem {
private:
    vector<Product> products;

    // Helper function for safe integer input
    int getIntInput(const string& prompt) {
        int input;
        cout << YELLOW << prompt << RESET;
        while (!(cin >> input)) {
            cout << RED << "Invalid input. Please enter a number: " << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear rest of line
        return input;
    }

    // Helper function for safe double input
    double getDoubleInput(const string& prompt) {
        double input;
        cout << YELLOW << prompt << RESET;
        while (!(cin >> input)) {
            cout << RED << "Invalid input. Please enter a numerical value: " << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear rest of line
        return input;
    }

public:
    RetailSystem() {
        // Initialize PC hardware store products
        products.push_back({"Intel Core i5-14600K", "CPU", 320.00, 15});
        products.push_back({"AMD Ryzen 7 7800X3D", "CPU", 450.00, 10});
        products.push_back({"NVIDIA RTX 4070 Ti", "GPU", 799.99, 8});
        products.push_back({"AMD Radeon RX 7900 XT", "GPU", 899.99, 5});
        products.push_back({"ASUS ROG Strix B650-E", "Motherboard", 299.99, 12});
        products.push_back({"MSI MPG Z790 Carbon", "Motherboard", 399.99, 7});
        products.push_back({"Corsair Vengeance DDR5 32GB", "RAM", 149.99, 25});
        products.push_back({"G.Skill Trident Z5 DDR5 32GB", "RAM", 169.99, 20});
        products.push_back({"Noctua NH-D15", "Cooler", 99.99, 18});
        products.push_back({"be quiet! Dark Rock Pro 5", "Cooler", 109.99, 15});
        products.push_back({"Corsair RM850x 850W", "Power Supply", 139.99, 10});
        products.push_back({"Seasonic Focus GX-750 750W", "Power Supply", 129.99, 8});
        products.push_back({"NZXT H710", "PC Case", 169.99, 6});
        products.push_back({"Fractal Design Meshify 2", "PC Case", 159.99, 7});
    }

    // Displays categories and returns the list of unique category names
    vector<string> getUniqueCategories() {
        vector<string> categories;
        for (const auto& product : products) {
            bool found = false;
            for (const auto& cat : categories) {
                if (cat == product.category) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                categories.push_back(product.category);
            }
        }
        return categories;
    }

    void displayCategories() {
        cout << BLUE << "\nAvailable Categories:\n" << RESET;
        vector<string> categories = getUniqueCategories();
        for (int i = 0; i < categories.size(); ++i) {
            cout << i + 1 << ". " << categories[i] << endl;
        }
        cout << "0. Back/Checkout\n";
    }

    // Displays products in a category using their global index
    vector<int> displayProductsByCategory(const string& category) {
        cout << CYAN << BOLD << "\n--- Products in " << category << " ---\n" << RESET;
        vector<int> indices_in_category;

        for (int i = 0; i < products.size(); ++i) {
            if (products[i].category == category) {
                // Store the actual product index (i + 1) for later selection
                indices_in_category.push_back(i + 1); 
                
                cout << BLUE << i + 1 << ". " << RESET << products[i].name
                      << " - Price: $" << products[i].price
                      << " | Stock: " << products[i].stock << endl;
            }
        }
        if (indices_in_category.empty()) {
             cout << RED << "No products found in this category.\n" << RESET;
        }
        return indices_in_category;
    }

    void displayProducts() {
        cout << CYAN << BOLD << "\n--- Full Product Catalog ---\n" << RESET;
        if (products.empty()) {
             cout << RED << "The product catalog is currently empty.\n" << RESET;
             return;
        }
        for (int i = 0; i < products.size(); ++i) {
            cout << BLUE << i + 1 << ". " << RESET << products[i].name
                  << " (" << products[i].category << ")"
                  << " - Price: $" << products[i].price
                  << " | Stock: " << products[i].stock << endl;
        }
    }

    void displayCart(vector<Product>& cart) {
        if (cart.empty()) {
            cout << RED << "Your cart is empty.\n" << RESET;
            return;
        }

        cout << CYAN << BOLD << "\n--- Your Cart ---\n" << RESET;
        for (const auto& item : cart) {
            cout << GREEN << item.name << RESET
                  << " | Quantity: " << item.stock
                  << " | Unit Price: $" << item.price << endl;
        }
    }

    void customerActions() {
        vector<Product> cart;
        int categoryChoice, productChoice, quantity;
        vector<string> categories = getUniqueCategories();

        while (true) {
            displayCategories();
            cout << YELLOW << "\nEnter the category number to browse or 0 to checkout: " << RESET;
            categoryChoice = getIntInput("");

            this->clearScreen();

            if (categoryChoice == 0) {
                break;
            } else if (categoryChoice < 1 || categoryChoice > categories.size()) {
                cout << RED << "Invalid category number.\n" << RESET;
                continue;
            }

            string selected_category = categories[categoryChoice - 1];
            
            // Display products in the selected category using their global indices
            vector<int> availableIndices = displayProductsByCategory(selected_category);

            if (availableIndices.empty()) {
                cout << RED << "\nReturning to category menu.\n" << RESET;
                continue;
            }

            cout << YELLOW << "\nEnter the product number to add to cart (0 to go back): " << RESET;
            productChoice = getIntInput("");

            this->clearScreen();

            if (productChoice == 0) {
                continue;
            }

            // Find the actual product index (0-based)
            int actual_index = -1;
            for (int index : availableIndices) {
                if (index == productChoice) {
                    actual_index = productChoice - 1;
                    break;
                }
            }

            if (actual_index == -1) {
                cout << RED << "Invalid product number for the selected category.\n" << RESET;
                continue;
            }

            // Final check on the selected product
            if (products[actual_index].category != selected_category) {
                cout << RED << "Error: Product index mismatch. Please try again.\n" << RESET;
                continue;
            }

            cout << YELLOW << "Enter the quantity: " << RESET;
            quantity = getIntInput("");

            this->clearScreen();

            if (quantity <= 0 || quantity > products[actual_index].stock) {
                cout << RED << "Invalid quantity or insufficient stock. Available: " << products[actual_index].stock << "\n" << RESET;
                continue;
            }

            // Add item to the cart
            Product selectedProduct = products[actual_index];
            selectedProduct.stock = quantity; // Store quantity in the stock field for cart item
            cart.push_back(selectedProduct);

            // Deduct the stock
            products[actual_index].stock -= quantity;

            cout << GREEN << quantity << " " << products[actual_index].name << "(s) added to cart.\n" << RESET;

            displayCart(cart); // Show current cart

            cout << YELLOW << "\nDo you want to add more items? (1 for Yes, 0 for Checkout): " << RESET;
            int addMore = getIntInput("");

            if (addMore == 0) {
                break;
            }

            this->clearScreen();
        }

        checkout(cart);
    }

    void checkout(vector<Product>& cart) {
        if (cart.empty()) {
            cout << RED << "\nYour cart is empty. Returning to the main menu.\n" << RESET;
            return;
        }

        double total = 0;

        // Display the receipt
        cout << CYAN << BOLD << "\n--- Final Receipt ---\n" << RESET;
        for (const auto& item : cart) {
            double lineTotal = item.price * item.stock;
            cout << left << setw(35) << item.name
                 << right << "Qty: " << setw(3) << item.stock
                 << " @ $" << fixed << setprecision(2) << setw(8) << item.price
                 << " | Subtotal: $" << fixed << setprecision(2) << setw(9) << lineTotal << endl;
            total += lineTotal;
        }
        cout << string(68, '-') << endl;
        cout << BOLD << left << setw(58) << "TOTAL AMOUNT DUE:" << right << "$ " << fixed << setprecision(2) << setw(9) << total << RESET << endl;
        
        cout << GREEN << "\nThank you for your purchase!\n" << RESET;

        int choice;
        cout << YELLOW << "\n\nDo you want to go back to the main menu or exit?\n1. Return to Main Menu\n2. Exit Program\n" << RESET;
        choice = getIntInput("");

        this->clearScreen();

        if (choice == 1) {
            return;
        } else {
            cout << GREEN << "Exiting the system. Goodbye!\n" << RESET;
            exit(0);
        }
    }

    bool staffLogin() {
        string username, password;

        cout << CYAN << BOLD << "\n--- Staff Login ---\n" << RESET;
        cout << YELLOW << "Enter staff username: " << RESET;
        getline(cin, username);
        cout << YELLOW << "Enter staff password: " << RESET;
        getline(cin, password);

        if (username == "staff" && password == "staff123") {
            cout << GREEN << "Login successful. Welcome!\n" << RESET;
            return true;
        } else {
            cout << RED << "Invalid credentials. Please try again.\n" << RESET;
            return false;
        }
    }

    // --- NEW FUNCTIONALITY: Add Product ---
    void addProduct() {
        clearScreen();
        cout << CYAN << BOLD << "\n--- Add New Product ---\n" << RESET;

        Product newProduct;
        cout << YELLOW << "Enter Product Name: " << RESET;
        getline(cin, newProduct.name);

        cout << YELLOW << "Enter Product Category (e.g., SSD, Monitor): " << RESET;
        getline(cin, newProduct.category);
        
        newProduct.price = getDoubleInput("Enter Product Price: $");
        if (newProduct.price <= 0) {
             cout << RED << "Price must be positive. Product addition failed.\n" << RESET;
             return;
        }

        newProduct.stock = getIntInput("Enter Initial Stock Quantity: ");
        if (newProduct.stock < 0) {
             cout << RED << "Stock cannot be negative. Product addition failed.\n" << RESET;
             return;
        }

        products.push_back(newProduct);
        cout << GREEN << "\nSuccessfully added new product: " << newProduct.name 
             << " to category: " << newProduct.category << ".\n" << RESET;
        cout << "\nPress ENTER to continue...";
        cin.get(); // Wait for user confirmation
    }

    void staffActions() {
        // Clear cin buffer just in case
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (!staffLogin()) {
            cout << "\nPress ENTER to return to the main menu...";
            cin.get();
            clearScreen();
            return;
        }

        int staffChoice;

        while (true) {
            clearScreen();
            cout << CYAN << BOLD << "\n--- Staff Management Menu ---\n" << RESET;
            cout << "1. Manage Existing Product Stock (Add/Decrease)\n";
            cout << "2. Add New Product (and New Category if applicable)\n";
            cout << "0. Logout / Return to Main Menu\n";
            cout << YELLOW << "Choose action: " << RESET;
            staffChoice = getIntInput("");

            if (staffChoice == 0) {
                clearScreen();
                break;
            } else if (staffChoice == 1) {
                manageStock();
            } else if (staffChoice == 2) {
                addProduct();
            } else {
                cout << RED << "Invalid choice.\n" << RESET;
                cout << "\nPress ENTER to continue...";
                cin.get();
            }
        }
    }

    void manageStock() {
        int choice, quantityChange;
        int action;

        while (true) {
            clearScreen();
            displayProducts();
            cout << YELLOW << "\nEnter the product number to modify stock (0 to go back): " << RESET;
            choice = getIntInput("");

            if (choice == 0) {
                clearScreen();
                break;
            } else if (choice < 1 || choice > products.size()) {
                cout << RED << "Invalid product number.\n" << RESET;
                continue;
            }

            cout << YELLOW << "Product: " << products[choice - 1].name 
                 << " | Current Stock: " << products[choice - 1].stock << RESET << endl;
            cout << YELLOW << "Enter 1 to Add stock or 2 to Decrease stock (0 to cancel): " << RESET;
            action = getIntInput("");

            if (action == 0) continue;

            if (action != 1 && action != 2) {
                cout << RED << "Invalid action. Please try again.\n" << RESET;
                continue;
            }

            cout << YELLOW << "Enter the quantity: " << RESET;
            quantityChange = getIntInput("");

            if (quantityChange <= 0) {
                cout << RED << "Invalid quantity. Please enter a positive number.\n" << RESET;
                continue;
            }

            if (action == 1) {
                // Add stock
                products[choice - 1].stock += quantityChange;
                cout << GREEN << "Stock for " << products[choice - 1].name << " increased by " << quantityChange << ".\n" << RESET;
            } else {
                // Decrease stock
                if (quantityChange > products[choice - 1].stock) {
                    cout << RED << "Error: You cannot decrease more stock than what is available. Current stock: "
                          << products[choice - 1].stock << ".\n" << RESET;
                    cout << "\nPress ENTER to continue...";
                    cin.get();
                    continue;
                }
                products[choice - 1].stock -= quantityChange;
                cout << GREEN << "Stock for " << products[choice - 1].name << " decreased by " << quantityChange << ".\n" << RESET;
            }

            cout << "\nPress ENTER to continue...";
            cin.get();
        }
    }


    // Function to clear the terminal screen (cross-platform)
    void clearScreen() {
        // For Unix-like systems
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
};

int main() {
    // Set output precision globally for currency display
    cout << fixed << setprecision(2);

    RetailSystem system;
    int role;

    while (true) {
        system.clearScreen();
        cout << BLUE << BOLD << "\n=== Welcome to the PC Hardware Store! ===\n" << RESET;
        cout << "1. Customer\n2. Staff\n3. Exit\n";
        cout << YELLOW << "Choose your role: " << RESET;
        
        // Input validation for role
        if (!(cin >> role)) {
            cout << RED << "Invalid input. Please enter a number.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (role == 1) {
            system.customerActions();
        } else if (role == 2) {
            system.staffActions();
        } else if (role == 3) {
            cout << GREEN << "Exiting the system. Goodbye!\n" << RESET;
            break;
        } else {
            cout << RED << "Invalid choice. Please try again.\n" << RESET;
        }
    }

    // Ensure the terminal color is reset when the program ends
    cout << RESET;
    return 0;
}
