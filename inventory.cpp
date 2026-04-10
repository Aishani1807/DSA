#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Product {
    int id;
    string name;
    double price;
};

class InventorySystem {
private:
    map<int, Product> idMap;               // For ID lookups
    multimap<double, int> priceMap;        // For Price range queries

public:
    void addOrUpdateProduct(int id, string name, double price) {
        // If product exists, remove old price mapping first
        if (idMap.count(id)) {
            double oldPrice = idMap[id].price;
            auto range = priceMap.equal_range(oldPrice);
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second == id) {
                    priceMap.erase(it);
                    break;
                }
            }
        }
        
        idMap[id] = {id, name, price};
        priceMap.insert({price, id});
        cout << "Added/Updated Product ID: " << id << " (" << name << ")\n";
    }

    void searchByID(int id) {
        if (idMap.count(id)) {
            Product p = idMap[id];
            cout << "Found: " << p.name << " | Price: $" << p.price << endl;
        } else {
            cout << "Product ID " << id << " not found.\n";
        }
    }

    void getProductsInRange(double minP, double maxP) {
        cout << "Products between $" << minP << " and $" << maxP << ":\n";
        auto itLow = priceMap.lower_bound(minP);
        auto itUp = priceMap.upper_bound(maxP);

        for (auto it = itLow; it != itUp; ++it) {
            Product p = idMap[it->second];
            cout << " - " << p.name << ": $" << p.price << " (ID: " << p.id << ")\n";
        }
    }
};

int main() {
    InventorySystem inv;
    
    // Sample Inputs
    inv.addOrUpdateProduct(1, "Wireless Mouse", 25.50);
    inv.addOrUpdateProduct(2, "Mechanical Keyboard", 85.00);
    inv.addOrUpdateProduct(3, "Gaming Monitor", 300.00);
    inv.addOrUpdateProduct(4, "USB-C Cable", 15.00);
    inv.addOrUpdateProduct(5, "Webcam", 65.00);

    cout << "\n--- Searching ID 3 ---\n";
    inv.searchByID(3);

    cout << "\n--- Range Query ($20 to $100) ---\n";
    inv.getProductsInRange(20.0, 100.0);

    return 0;
}
