## 🛒 PC Hardware Store Retail System (C++)

This command-line application simulates a basic retail management system for a PC hardware store, allowing users to interact as either a **Customer** (for shopping and checkout) or **Staff** (for inventory management).

-----

## ✨ Features

  * **User Roles:** Separate menus and authentication for **Customer** and **Staff**.
  * **Category Browsing:** Customers can filter products by categories (e.g., CPU, GPU, Motherboard).
  * **Safe Input:** Robust input validation ensures the program doesn't crash on invalid data (e.g., entering text when a number is expected).
  * **Inventory Management:** Staff can add new products and manage the stock levels of existing items.
  * **Checkout & Receipt:** Calculates the total, deducts purchased items from inventory, and prints a formatted receipt.
  * **Colored Terminal Output:** Uses ANSI escape codes for a visually appealing and organized interface.

-----

## 🛠️ How to Compile and Run

This project requires a C++ compiler (like g++ or Clang) that supports the C++11 standard or newer.

1.  **Save the Code:** Save the provided code as a file named `retail_system.cpp`.

2.  **Compile:** Open your terminal or command prompt and run the following command:

    ```bash
    g++ main.cpp -o Retail_Store
    ```

3.  **Run:** Execute the compiled program:

    ```bash
    ./retail_system
    ```

    *(Use `retail_system.exe` on Windows)*

-----

## 💻 Code Structure and Key Concepts

The system is built around the `RetailSystem` class, managing the core inventory logic.

### 1\. Data Structures

| Element | Type | Purpose |
| :--- | :--- | :--- |
| **`Product`** | `struct` | Bundles related product data (Name, Category, Price, Stock) into a single unit. |
| **`products`** | `std::vector<Product>` | The dynamic array holding the entire store inventory. |

### 2\. Core Functions

| Function Group | Key Functions | Description |
| :--- | :--- | :--- |
| **Customer Interface** | `customerActions()`, `checkout()` | Guides the user through category selection, adding items to the cart, and finalizing the purchase. |
| **Staff Management** | `staffLogin()`, `manageStock()`, `addProduct()` | Handles staff login (`Username: staff`, `Password: staff123`), updates product stock levels, and adds new items to the catalog. |
| **Display/Utility** | `getUniqueCategories()`, `clearScreen()` | Finds all distinct categories in the current inventory; clears the terminal screen for a cleaner user experience. |
| **Input Helpers** | `getIntInput()`, `getDoubleInput()` | **Crucial for robust error handling.** These functions ensure that the user only enters valid numerical data and prevent stream errors (flushing the input buffer after numeric input). |

### 3\. Intermediate C++ Techniques

  * **`std::vector`:** Used extensively for dynamic memory management, allowing the inventory to grow or shrink without needing to pre-define array sizes.
  * **Input Handling (`<limits>`, `cin.ignore`):** Prevents common bugs where a numerical input leaves a newline character in the buffer, causing subsequent string inputs (`getline`) to be skipped.
    ```cpp
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    ```
  * **Formatting (`<iomanip>`):** Used in the `checkout()` function to generate a neat receipt by controlling spacing and precision:
      * `fixed` and `setprecision(2)` ensure currency is displayed with two decimal places (e.g., `$15.00`).
      * `setw(n)` aligns text and numbers into clean columns.
  * **ANSI Escape Codes:** The `\033` strings are used to change text colors (RED, GREEN, BLUE, etc.) directly in the terminal output.

-----

## 👤 Staff Credentials

| Role | Username | Password |
| :--- | :--- | :--- |
| **Staff** | `staff` | `staff123` |
