// Q4: Chain hashing (linked list per bucket); hash = sum of ASCII values % buckets
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct Node {
    string key, value;
    Node* next;
    Node(const string& k, const string& v) : key(k), value(v), next(NULL) {}
};

class HashTable {
    int buckets;
    Node** table;

    int hashFn(const string& key) const {
        int sum = 0;
        for (size_t i = 0; i < key.size(); i++) sum += (unsigned char)key[i];
        return sum % buckets;
    }
public:
    HashTable(int b = 10) : buckets(b) {
        table = new Node*[buckets];
        for (int i = 0; i < buckets; i++) table[i] = NULL;
    }
    ~HashTable() {
        for (int i = 0; i < buckets; i++) {
            Node* cur = table[i];
            while (cur) { Node* t = cur; cur = cur->next; delete t; }
        }
        delete[] table;
    }

    void insert(const string& key, const string& value) {
        int idx = hashFn(key);
        for (Node* cur = table[idx]; cur; cur = cur->next) {
            if (cur->key == key) {            // duplicate key -> update value
                cur->value = value;
                return;
            }
        }
        Node* n = new Node(key, value);       // otherwise insert at head of chain
        n->next = table[idx];
        table[idx] = n;
    }

    bool search(const string& key, string& value) const {
        for (Node* cur = table[hashFn(key)]; cur; cur = cur->next)
            if (cur->key == key) { value = cur->value; return true; }
        return false;
    }

    void display() const {
        for (int i = 0; i < buckets; i++) {
            cout << "Bucket " << i << ": ";
            for (Node* cur = table[i]; cur; cur = cur->next)
                cout << "(" << cur->key << ", " << cur->value << ") -> ";
            cout << "NULL\n";
        }
    }
};

int main() {
    HashTable myhash;
    myhash.insert("A", "aaaaa");
    myhash.insert("B", "bbbbb");
    myhash.insert("C", "ccccc");
    myhash.insert("A", "zzzzz");   // duplicate key A: value updated

    myhash.display();

    string v;
    if (myhash.search("A", v)) cout << "\nValue for key A: " << v << "\n";

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
