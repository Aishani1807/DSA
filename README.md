# Problem Statement:
Managing a dynamic product inventory requires a system that handles frequent updates (additions/deletions) while maintaining sorted order. The primary challenge is to support efficient range queries (finding products between two price points) and fast search (by ID) simultaneously as the inventory fluctuates.

# Objective:
To design and implement a robust inventory management system that: Maintains a sorted collection of products by Price and Product ID. 
Achieves logarithmic time complexity (O(log n)) for search, insertion, and deletion.Supports efficient range-based filtering for price-sensitive queries.

# Data Fields:
The system utilizes a Product structure:
int id: Unique identifier.
string name: Product name.
double price: The cost used for range queries.

# Data Structures Used:
To optimize different types of access, we use two complementary structures:
1) map<int, Product>: A Red-Black Tree implementation for Search by ID. It ensures O(log n) time for lookups and updates.
2) multimap<double, int>: A Red-Black Tree for Price Sorting. We use a multimap because multiple products might share the same price. This enables O(log n) range discovery.

# Algorithm Design:
Insertion: The product is inserted into the idMap. Then, the price and ID pair is inserted into the priceMap.
Search by ID: Perform a standard map lookup using the Product ID.
Range Query: Use the lower_bound and upper_bound functions of the multimap to find the iterators for the price range, then iterate through them.
Update: To update a price, the old entry must be removed from the priceMap and re-inserted to maintain the sorted order.

# Optimization Techniques:
1) Red-Black Tree vs. Array: A naive array would require O(n) for insertions and O(nlogn) for re-sorting. Using map ensures the system is always sorted with O(log n) overhead.
2) Memory Efficiency: Instead of storing the full Product object in both maps, the priceMap only stores the id, acting as an index to the main idMap.
