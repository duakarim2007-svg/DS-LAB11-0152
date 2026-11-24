// Q5: ASCII-based dictionary; hash = (sum of ASCII) MOD 100; separate chaining
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <cstdlib>
using namespace std;

const int TABLE_SIZE = 100;

typedef pair<string, string> Entry;

class Dictionary {
    list<Entry> table[TABLE_SIZE];

    int hashFn(const string& key) const {
        int sum = 0;
        for (size_t i = 0; i < key.size(); i++) sum += (unsigned char)key[i];
        return sum % TABLE_SIZE;
    }
public:
    void Add_Record(const string& key, const string& meaning) {
        list<Entry>& chain = table[hashFn(key)];
        for (list<Entry>::iterator it = chain.begin(); it != chain.end(); ++it)
            if (it->first == key) { it->second = meaning; cout << "Record updated.\n"; return; }
        chain.push_back(Entry(key, meaning));
        cout << "Record added at index " << hashFn(key) << ".\n";
    }

    void Word_Search(const string& key) const {
        const list<Entry>& chain = table[hashFn(key)];
        for (list<Entry>::const_iterator it = chain.begin(); it != chain.end(); ++it)
            if (it->first == key) { cout << "search key " << key << ": " << it->second << "\n"; return; }
        cout << "Error: key " << key << " not found!\n";
    }

    void Delete_Record(const string& key) {
        list<Entry>& chain = table[hashFn(key)];
        for (list<Entry>::iterator it = chain.begin(); it != chain.end(); ++it)
            if (it->first == key) {
                chain.erase(it);
                cout << "key " << key << " deleted successfully !\n";
                return;
            }
        cout << "Error: key " << key << " not found!\n";
    }

    void Print_Dictionary() const {
        bool empty = true;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].empty()) continue;
            empty = false;
            cout << "index " << i << ": ";
            bool first = true;
            for (list<Entry>::const_iterator it = table[i].begin(); it != table[i].end(); ++it) {
                if (!first) cout << " -> ";
                cout << "(" << it->first << ", " << it->second << ")";
                first = false;
            }
            cout << "\n";
        }
        if (empty) cout << "Dictionary is empty.\n";
    }
};

int main() {
    Dictionary d;
    int choice;
    do {
        cout << "\n--- Dictionary Menu ---\n"
             << "1. Add Record\n2. Search Word\n3. Delete Record\n4. Print Dictionary\n0. Exit\n"
             << "Choice: ";
        if (!(cin >> choice)) break;
        string key, meaning;
        switch (choice) {
            case 1:
                cout << "Enter word: "; cin >> key;
                cout << "Enter meaning: ";
                cin >> ws; getline(cin, meaning);
                d.Add_Record(key, meaning);
                break;
            case 2:
                cout << "Enter word to search: "; cin >> key;
                d.Word_Search(key);
                break;
            case 3:
                cout << "Enter word to delete: "; cin >> key;
                d.Delete_Record(key);
                break;
            case 4:
                d.Print_Dictionary();
                break;
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
