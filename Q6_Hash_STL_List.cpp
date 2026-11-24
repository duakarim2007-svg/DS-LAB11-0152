// Q6: Hash class (separate chaining) using std::list for each bucket
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Hash {
    int buckets;
    vector< list<int> > table;

    int hashFn(int key) const { return ((key % buckets) + buckets) % buckets; }
public:
    Hash(int b) : buckets(b), table(b) {}

    void insert(int key) {
        list<int>& chain = table[hashFn(key)];
        if (find(chain.begin(), chain.end(), key) != chain.end()) {
            cout << key << " already exists.\n";
            return;
        }
        chain.push_back(key);
        cout << key << " inserted at index " << hashFn(key) << ".\n";
    }

    void deleteKey(int key) {
        list<int>& chain = table[hashFn(key)];
        list<int>::iterator it = find(chain.begin(), chain.end(), key);
        if (it == chain.end()) { cout << key << " not found.\n"; return; }
        chain.erase(it);
        cout << key << " deleted.\n";
    }

    bool search(int key) const {
        const list<int>& chain = table[hashFn(key)];
        bool found = find(chain.begin(), chain.end(), key) != chain.end();
        if (found) cout << key << " found at index " << hashFn(key) << ".\n";
        else       cout << key << " not found.\n";
        return found;
    }

    void display() const {
        for (int i = 0; i < buckets; i++) {
            cout << i;
            for (list<int>::const_iterator it = table[i].begin(); it != table[i].end(); ++it)
                cout << " --> " << *it;
            cout << "\n";
        }
    }
};

int main() {
    Hash h(7);
    int choice, key;
    do {
        cout << "\n--- Hash Menu ---\n"
             << "1. Insert\n2. Delete\n3. Search\n4. Display\n0. Exit\nChoice: ";
        if (!(cin >> choice)) break;
        switch (choice) {
            case 1: cout << "Key: "; cin >> key; h.insert(key); break;
            case 2: cout << "Key: "; cin >> key; h.deleteKey(key); break;
            case 3: cout << "Key: "; cin >> key; h.search(key); break;
            case 4: h.display(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
