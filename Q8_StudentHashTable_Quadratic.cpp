// Q8: StudentHashTable (size 15) with quadratic probing: (index + attempt^2) % 15
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class StudentHashTable {
    static const int SIZE = 15;
    struct Record {
        int roll;
        string name;
        bool occupied;
        Record() : roll(0), occupied(false) {}
    };
    Record table[SIZE];

    int hashFn(int roll) const { return roll % SIZE; }
public:
    void InsertRecord(int roll, const string& name) {
        int index = hashFn(roll);
        for (int attempt = 0; attempt < SIZE; attempt++) {
            int pos = (index + attempt * attempt) % SIZE;
            if (!table[pos].occupied) {
                table[pos].roll = roll;
                table[pos].name = name;
                table[pos].occupied = true;
                cout << "Inserted roll " << roll << " (" << name << ") at index " << pos << "\n";
                return;
            }
            if (table[pos].roll == roll) {
                cout << "Roll " << roll << " already exists at index " << pos << "\n";
                return;
            }
        }
        cout << "Could not insert roll " << roll << ": no free slot found by quadratic probing.\n";
    }

    void SearchRecord(int roll) const {
        int index = hashFn(roll);
        for (int attempt = 0; attempt < SIZE; attempt++) {
            int pos = (index + attempt * attempt) % SIZE;
            if (!table[pos].occupied) break;           // empty slot -> not in table
            if (table[pos].roll == roll) {
                cout << "Roll " << roll << ": " << table[pos].name << "\n";
                return;
            }
        }
        cout << "Record not found\n";
    }
};

int main() {
    StudentHashTable ht;
    int choice, roll;
    string name;
    do {
        cout << "\n--- Student Hash Table ---\n"
             << "1. Insert Record\n2. Search Record\n0. Exit\nChoice: ";
        if (!(cin >> choice)) break;
        switch (choice) {
            case 1:
                cout << "Roll number: "; cin >> roll;
                cout << "Name: "; cin >> ws; getline(cin, name);
                ht.InsertRecord(roll, name);
                break;
            case 2:
                cout << "Roll number: "; cin >> roll;
                ht.SearchRecord(roll);
                break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
