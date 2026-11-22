
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// PRODUCT STRUCTURE
struct Product
{
    int id;
    string name;
    int qty;
    float price;
};
// PRODUCT LINKED LIST NODE
struct Node
{
    Product data;
    Node *next;
};
// TRANSACTION STRUCTURE
struct Transaction
{
    int transId;
    int productId;
    string productName;
    string type;
    int qty;
};
// TRANSACTION LINKED LIST NODE
struct TNode
{
    Transaction data;
    TNode *next;
};
// GLOBAL VARIABLES
Node *head = NULL;
TNode *thead = NULL;
int nextTransId = 1;
// FUNCTION DECLARATIONS
void saveAll();
void addProduct();
void displayProducts();
void searchProduct();
void updateProduct();
void deleteProduct();
void stockIn();
void stockOut();
void showTransactions();
void sortProducts();
void inventoryReport();
void lowStockReport();
void stockSummary();
void loadProducts();
void loadTransactions();
void freeAll();
// CLEAR INVALID INPUT
void clearInput()
{
    cin.clear();
    cin.ignore(1000, '\n');
}
// FIND PRODUCT USING LINEAR SEARCH
Node* findProduct(int id)
{
    Node *temp = head;

    while (temp != NULL)
    {
        if (temp->data.id == id)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}
// INSERT PRODUCT AT END
void addToList(Product p)
{
    Node *newNode = new Node;

    newNode->data = p;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}
// 1. ADD PRODUCT
void addProduct()
{
    Product p;

    cout << "\nEnter Product ID: ";
    cin >> p.id;

    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }

    if (p.id < 1 || p.id > 999)
    {
        cout << "Invalid Product ID! Enter 1 to 999.\n";
        return;
    }

    if (findProduct(p.id) != NULL)
    {
        cout << "Product ID already exists!\n";
        return;
    }

    cout << "Enter Product Name: ";
    cin >> p.name;

    cout << "Enter Quantity: ";
    cin >> p.qty;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    if (p.qty < 0 || p.qty > 500)
    {
        cout << "Invalid Quantity! Enter 0 to 500.\n";
        return;
    }
    cout << "Enter Price: ";
    cin >> p.price;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    if (p.price < 0 || p.price > 100000)
    {
        cout << "Invalid Price! Enter 0 to 100000.\n";
        return;
    }
    addToList(p);
    saveAll();
    cout << "Product added successfully.\n";
}
// 2. DISPLAY ALL PRODUCTS
void displayProducts()
{
    if (head == NULL)
    {
        cout << "\nNo products available.\n";
        return;
    }
    Node *temp = head;
    cout << "\n========== ALL PRODUCTS ==========\n";
    while (temp != NULL)
    {
        cout << "\nProduct ID: " << temp->data.id;
        cout << "\nProduct Name: " << temp->data.name;
        cout << "\nQuantity: " << temp->data.qty;
        cout << "\nPrice: Rs. " << temp->data.price;
        cout << "\n-----------------------------\n";
        temp = temp->next;
    }
}
// 3. SEARCH PRODUCT
void searchProduct()
{
    int id;
    cout << "\nEnter Product ID to search: ";
    cin >> id;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    Node *temp = findProduct(id);
    if (temp == NULL)
    {
        cout << "Product not found.\n";
    }
    else
    {
        cout << "\nProduct Found!";
        cout << "\nProduct ID: " << temp->data.id;
        cout << "\nProduct Name: " << temp->data.name;
        cout << "\nQuantity: " << temp->data.qty;
        cout << "\nPrice: Rs. " << temp->data.price << endl;
    }
}
// 4. UPDATE PRODUCT
void updateProduct()
{
    int id, newQty;
    float newPrice;
    string newName;
    cout << "\nEnter Product ID to update: ";
    cin >> id;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    Node *temp = findProduct(id);
    if (temp == NULL)
    {
        cout << "Product not found.\n";
        return;
    }
    cout << "Enter New Product Name: ";
    cin >> newName;
    cout << "Enter New Quantity: ";
    cin >> newQty;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    if (newQty < 0 || newQty > 500)
    {
        cout << "Invalid Quantity! Enter 0 to 500.\n";
        return;
    }
    cout << "Enter New Price: ";
    cin >> newPrice;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    if (newPrice < 0 || newPrice > 100000)
    {
        cout << "Invalid Price! Enter 0 to 100000.\n";
        return;
    }
    temp->data.name = newName;
    temp->data.qty = newQty;
    temp->data.price = newPrice;
    saveAll();
    cout << "Product updated successfully.\n";
}
// 5. DELETE PRODUCT
void deleteProduct()
{
    int id;
    cout << "\nEnter Product ID to delete: ";
    cin >> id;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    Node *temp = head;
    Node *prev = NULL;
    while (temp != NULL && temp->data.id != id)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        cout << "Product not found.\n";
        return;
    }
    if (prev == NULL)
    {
        head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }
    delete temp;
    saveAll();
    cout << "Product deleted successfully.\n";
}
// ADD TRANSACTION
void addTransaction(int id, string name,
                    string type, int qty)
{
    TNode *newNode = new TNode;
    newNode->data.transId = nextTransId;
    newNode->data.productId = id;
    newNode->data.productName = name;
    newNode->data.type = type;
    newNode->data.qty = qty;
    newNode->next = NULL;
    nextTransId++;
    if (thead == NULL)
    {
        thead = newNode;
    }
    else
    {
        TNode *temp = thead;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
// 6. STOCK IN
void stockIn()
{
    int id, qty;
    cout << "\nEnter Product ID: ";
    cin >> id;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    if (id < 1 || id > 999)
    {
        cout << "Invalid Product ID!\n";
        return;
    }
    Node *temp = findProduct(id);
    if (temp == NULL)
    {
        cout << "Product not found.\n";
        return;
    }
    cout << "Enter Quantity to Add: ";
    cin >> qty;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    if (qty < 1 || qty > 500)
    {
        cout << "Quantity must be between 1 and 500.\n";
        return;
    }
    if (temp->data.qty + qty > 500)
    {
        cout << "Maximum stock limit is 500!\n";
        return;
    }
    temp->data.qty = temp->data.qty + qty;
    addTransaction(id, temp->data.name, "IN", qty);
    saveAll();
    cout << "Stock added successfully.\n";
}
// 7. STOCK OUT
void stockOut()
{
    int id, qty;
    cout << "\nEnter Product ID: ";
    cin >> id;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    if (id < 1 || id > 999)
    {
        cout << "Invalid Product ID!\n";
        return;
    }
    Node *temp = findProduct(id);
    if (temp == NULL)
    {
        cout << "Product not found.\n";
        return;
    }
    cout << "Enter Quantity to Remove: ";
    cin >> qty;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    if (qty < 1 || qty > 500)
    {
        cout << "Quantity must be between 1 and 500.\n";
        return;
    }
    if (qty > temp->data.qty)
    {
        cout << "Insufficient stock!\n";
        return;
    }
    temp->data.qty = temp->data.qty - qty;
    addTransaction(id, temp->data.name, "OUT", qty);
    saveAll();
    cout << "Stock removed successfully.\n";
}
// 8. DISPLAY TRANSACTION HISTORY
void showTransactions()
{
    if (thead == NULL)
    {
        cout << "\nNo transactions available.\n";
        return;
    }
    TNode *temp = thead;
    cout << "\n========== TRANSACTION HISTORY ==========\n";
    while (temp != NULL)
    {
        cout << "\nTransaction ID: " << temp->data.transId;
        cout << "\nProduct ID: " << temp->data.productId;
        cout << "\nProduct Name: " << temp->data.productName;
        cout << "\nType: " << temp->data.type;
        cout << "\nQuantity: " << temp->data.qty;
        cout << "\n-----------------------------\n";
        temp = temp->next;
    }
}
// BUBBLE SORT
void bubbleSort(int choice)
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }
    int swapped;
    do
    {
        swapped = 0;
        Node *temp = head;
        while (temp->next != NULL)
        {
            int condition = 0;
            if (choice == 1)
            {
                if (temp->data.id > temp->next->data.id)
                    condition = 1;
            }
            else if (choice == 2)
            {
                if (temp->data.name > temp->next->data.name)
                    condition = 1;
            }
            else if (choice == 3)
            {
                if (temp->data.qty > temp->next->data.qty)
                    condition = 1;
            }
            if (condition == 1)
            {
                Product t = temp->data;
                temp->data = temp->next->data;
                temp->next->data = t;
                swapped = 1;
            }
            temp = temp->next;
        }
    } while (swapped == 1);
}
// 9. SORT PRODUCTS
void sortProducts()
{
    int choice;
    cout << "\n1. Sort by Product ID";
    cout << "\n2. Sort by Product Name";
    cout << "\n3. Sort by Quantity";
    cout << "\nEnter choice: ";
    cin >> choice;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    if (choice < 1 || choice > 3)
    {
        cout << "Invalid choice!\n";
        return;
    }
    bubbleSort(choice);
    saveAll();
    cout << "\nProducts sorted successfully.\n";
    displayProducts();
}
// 10. INVENTORY REPORT
void inventoryReport()
{
    if (head == NULL)
    {
        cout << "\nNo products available.\n";
        return;
    }
    Node *temp = head;
    float totalValue = 0;
    cout << "\n========== INVENTORY REPORT ==========\n";
    while (temp != NULL)
    {
        cout << "\nProduct ID: " << temp->data.id;
        cout << "\nProduct Name: " << temp->data.name;
        cout << "\nQuantity: " << temp->data.qty;
        cout << "\nPrice: Rs. " << temp->data.price;
        totalValue = totalValue +
                     (temp->data.qty * temp->data.price);
        cout << "\n-----------------------------\n";
        temp = temp->next;
    }
    cout << "\nTotal Inventory Value: Rs. "
         << totalValue << endl;
}
// 11. LOW STOCK REPORT
void lowStockReport()
{
    int limit;
    int found = 0;
    cout << "\nEnter Low Stock Limit: ";
    cin >> limit;
    if (cin.fail())
    {
        cout << "Invalid input!\n";
        clearInput();
        return;
    }
    if (limit < 0 || limit > 500)
    {
        cout << "Invalid limit! Enter 0 to 500.\n";
        return;
    }
    Node *temp = head;
    cout << "\n========== LOW STOCK REPORT ==========\n";
    while (temp != NULL)
    {
        if (temp->data.qty < limit)
        {
            cout << "\nProduct ID: " << temp->data.id;
            cout << "\nProduct Name: " << temp->data.name;
            cout << "\nQuantity: " << temp->data.qty;
            cout << "\nPrice: Rs. " << temp->data.price;
            cout << "\n-----------------------------\n";
            found = 1;
        }
        temp = temp->next;
    }
    if (found == 0)
    {
        cout << "No low stock products found.\n";
    }
}
// 12. STOCK SUMMARY
void stockSummary()
{
    Node *temp = head;
    int totalProducts = 0;
    int totalUnits = 0;
    int lowStockCount = 0;
    float totalValue = 0;
    while (temp != NULL)
    {
        totalProducts++;
        totalUnits = totalUnits + temp->data.qty;
        totalValue = totalValue +
                     (temp->data.qty * temp->data.price);
        if (temp->data.qty < 10)
        {
            lowStockCount++;
        }
        temp = temp->next;
    }
    cout << "\n========== STOCK SUMMARY ==========\n";
    cout << "Total Products: " << totalProducts << endl;
    cout << "Total Units: " << totalUnits << endl;
    cout << "Low Stock Products: " << lowStockCount << endl;
    cout << "Total Inventory Value: Rs. "
         << totalValue << endl;
}
// SAVE DATA TO FILES
void saveAll()
{
    ofstream fout("products.txt");
    if (!fout)
    {
        cout << "Error saving products file!\n";
        return;
    }
    Node *temp = head;
    while (temp != NULL)
    {
        fout << temp->data.id << " "
             << temp->data.name << " "
             << temp->data.qty << " "
             << temp->data.price << endl;
        temp = temp->next;
    }
    fout.close();
    ofstream tout("transactions.txt");
    if (!tout)
    {
        cout << "Error saving transactions file!\n";
        return;
    }
    TNode *t = thead;
    while (t != NULL)
    {
        tout << t->data.transId << " "
             << t->data.productId << " "
             << t->data.productName << " "
             << t->data.type << " "
             << t->data.qty << endl;
        t = t->next;
    }
    tout.close();
}
// LOAD PRODUCTS FROM FILE
void loadProducts()
{
    ifstream fin("products.txt");
    if (!fin)
    {
        return;
    }
    Product p;
    while (fin >> p.id >> p.name >> p.qty >> p.price)
    {
        if (p.id >= 1 && p.id <= 999 &&
            p.qty >= 0 && p.qty <= 500 &&
            p.price >= 0 && p.price <= 100000 &&
            findProduct(p.id) == NULL)
        {
            addToList(p);
        }
    }
    fin.close();
}
// LOAD TRANSACTIONS FROM FILE
void loadTransactions()
{
    ifstream fin("transactions.txt");
    if (!fin)
    {
        return;
    }
    Transaction t;
    while (fin >> t.transId
               >> t.productId
               >> t.productName
               >> t.type
               >> t.qty)
    {
        if (t.transId > 0 &&
            t.productId >= 1 && t.productId <= 999 &&
            t.qty > 0 && t.qty <= 500 &&
            (t.type == "IN" || t.type == "OUT"))
        {
            TNode *newNode = new TNode;
            newNode->data = t;
            newNode->next = NULL;
            if (thead == NULL)
            {
                thead = newNode;
            }
            else
            {
                TNode *temp = thead;

                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = newNode;
            }

            if (t.transId >= nextTransId)
            {
                nextTransId = t.transId + 1;
            }
        }
    }
    fin.close();
}
// FREE MEMORY
void freeAll()
{
    Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    TNode *t;
    while (thead != NULL)
    {
        t = thead;
        thead = thead->next;
        delete t;
    }
}
// MAIN FUNCTION
int main()
{
    loadProducts();
    loadTransactions();
    int choice;
    do
    {
        cout << "\n\n======================================";
        cout << "\n   INVENTORY AND STOCK MANAGEMENT";
        cout << "\n======================================";
        cout << "\n1. Add Product";
        cout << "\n2. Display All Products";
        cout << "\n3. Search Product";
        cout << "\n4. Update Product";
        cout << "\n5. Delete Product";
        cout << "\n6. Stock IN";
        cout << "\n7. Stock OUT";
        cout << "\n8. Display Transaction History";
        cout << "\n9. Sort Products";
        cout << "\n10. Inventory Report";
        cout << "\n11. Low Stock Report";
        cout << "\n12. Stock Summary";
        cout << "\n13. Save Data";
        cout << "\n14. Exit";
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cout << "Invalid menu input!\n";
            clearInput();
            continue;
        }
        switch (choice)
        {
            case 1:
                addProduct();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                updateProduct();
                break;
            case 5:
                deleteProduct();
                break;
            case 6:
                stockIn();
                break;
            case 7:
                stockOut();
                break;
            case 8:
                showTransactions();
                break;
            case 9:
                sortProducts();
                break;
            case 10:
                inventoryReport();
                break;
            case 11:
                lowStockReport();
                break;
            case 12:
                stockSummary();
                break;
            case 13:
                saveAll();
                cout << "Data saved successfully.\n";
                break;
            case 14:
                saveAll();
                cout << "Data saved successfully.\n";
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 14);
    freeAll();
    return 0;
}

