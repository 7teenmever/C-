#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Product {
    int id;
    string name;
    string category;
    double price;
    int quantity;
};

struct Inventory {
    Product products[200];
    int productCount;
    const string filename = "inventory.txt";

    Inventory() : productCount(0) {}

    void addProduct() {
        if (productCount >= 200) {
            cout << "Inventory is full." << endl;
            return;
        }

        Product p;
        cout << "Enter product ID: ";
        cin >> p.id;
        cin.ignore();

        cout << "Enter product name: ";
        getline(cin, p.name);

        cout << "Enter category: ";
        getline(cin, p.category);

        cout << "Enter price: ";
        cin >> p.price;

        cout << "Enter quantity: ";
        cin >> p.quantity;

        products[productCount++] = p;
    }

    void addProduct(const Product& p) {
        if (productCount >= 200) {
            cout << "Inventory is full." << endl;
            return;
        }
        products[productCount++] = p;
    }

    void displayProducts() {
        if (productCount == 0) {
            cout << "No products in inventory." << endl;
            return;
        }

        for (int i = 0; i < productCount; ++i) {
            cout << products[i].id << " | " << products[i].name
                 << " | " << products[i].category
                 << " | Price: " << products[i].price
                 << " | Qty: " << products[i].quantity << endl;
        }
    }

    Product* findProduct(int id) {
        for (int i = 0; i < productCount; ++i) {
            if (products[i].id == id) {
                return &products[i];
            }
        }
        return nullptr;
    }

    void updateStock(int id, int quantity) {
        Product* p = findProduct(id);
        if (p == nullptr) {
            cout << "Product not found." << endl;
            return;
        }
        p->quantity = quantity;
        cout << "Stock updated for " << p->name << endl;
    }

    void generateReport() {
        double totalValue = 0.0;
        int totalUnits = 0;

        for (int i = 0; i < productCount; ++i) {
            totalValue += products[i].price * products[i].quantity;
            totalUnits += products[i].quantity;
        }

        cout << "Total products: " << productCount << endl;
        cout << "Total units: " << totalUnits << endl;
        cout << "Total inventory value: " << totalValue << endl;
    }

    void saveInventory() {
        ofstream out(filename);
        if (!out) {
            cout << "Could not save inventory." << endl;
            return;
        }

        for (int i = 0; i < productCount; ++i) {
            out << products[i].id << ","
                << products[i].name << ","
                << products[i].category << ","
                << products[i].price << ","
                << products[i].quantity << "\n";
        }
    }

    void loadInventory() {
        ifstream in(filename);
        if (!in) {
            cout << "No saved inventory file found." << endl;
            return;
        }

        productCount = 0;
        string line;
        while (getline(in, line) && productCount < 200) {
            if (line.empty()) {
                continue;
            }

            stringstream ss(line);
            string idStr;
            string name;
            string category;
            string priceStr;
            string quantityStr;

            if (!getline(ss, idStr, ',')) {
                continue;
            }
            if (!getline(ss, name, ',')) {
                continue;
            }
            if (!getline(ss, category, ',')) {
                continue;
            }
            if (!getline(ss, priceStr, ',')) {
                continue;
            }
            if (!getline(ss, quantityStr)) {
                continue;
            }

            products[productCount].id = stoi(idStr);
            products[productCount].name = name;
            products[productCount].category = category;
            products[productCount].price = stod(priceStr);
            products[productCount].quantity = stoi(quantityStr);
            ++productCount;
        }
    }
};

int main() {
    Inventory inv;

    inv.addProduct({101, "Laptop", "Electronics", 1200.0, 10});
    inv.addProduct({102, "Notebook", "Stationery", 2.5, 200});
    inv.addProduct({103, "Headphones", "Electronics", 80.0, 25});

    cout << "Current inventory:" << endl;
    inv.displayProducts();

    cout << "\nUpdating stock for ID 103" << endl;
    inv.updateStock(103, 30);

    cout << "\nInventory report:" << endl;
    inv.generateReport();

    inv.saveInventory();

    Inventory loaded;
    loaded.loadInventory();
    cout << "\nLoaded inventory:" << endl;
    loaded.displayProducts();

    return 0;
}
