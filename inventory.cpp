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
    int n;
    int priceRangelow, priceRangehigh;
    string cont = "Yes";
    InventorySystem inv;
    
    // Sample Inputs
    inv.addOrUpdateProduct(1, "Wireless Mouse", 25.50);
    inv.addOrUpdateProduct(2, "Mechanical Keyboard", 85.00);
    inv.addOrUpdateProduct(3, "Gaming Monitor", 300.00);
    inv.addOrUpdateProduct(4, "USB-C Cable", 15.00);
    inv.addOrUpdateProduct(5, "Webcam", 65.00);
    
    while(cont == "Yes") {
    cout<<endl;
    cout<< "Enter the product ID that needs to be searched: ";
    cin >> n;

    cout << "--- Searching ID ---\n";
    inv.searchByID(n);

    cout<<endl;
    cout<< "Enter price range (low, high): ";
    cin >> priceRangelow >> priceRangehigh;

    cout << "--- Range Query  ---\n";
    inv.getProductsInRange(priceRangelow, priceRangehigh);

    cout<<endl;
    cout << "Do you want to continue? (Yes/No): ";
    cin >> cont;

    cout<<endl;
    }
    return 0;
}
