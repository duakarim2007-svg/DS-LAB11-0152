// Q1: Insert a parcel with urgency 2 into an existing binary min-heap
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

class MinHeap {
    vector<int> h;
public:
    MinHeap(const vector<int>& init) : h(init) {}

    void insert(int val) {
        h.push_back(val);
        int i = (int)h.size() - 1;
        while (i > 0) {                       // sift up
            int p = (i - 1) / 2;
            if (h[i] < h[p]) { swap(h[i], h[p]); i = p; }
            else break;
        }
    }

    void print() const {
        cout << "Array form : ";
        for (size_t k = 0; k < h.size(); k++) cout << h[k] << " ";
        cout << "\nTree form  :\n";
        int n = (int)h.size(), level = 0, i = 0;
        while (i < n) {
            int cnt = 1 << level;
            cout << "  Level " << level << ": ";
            for (int k = 0; k < cnt && i < n; k++, i++) cout << h[i] << " ";
            cout << "\n";
            level++;
        }
    }
};

int main() {
    // Existing valid min-heap of urgency ratings (1 = most urgent)
    int init[] = {1, 3, 1, 4, 3, 5, 2, 5};
    vector<int> start(init, init + 8);
    MinHeap heap(start);

    cout << "Initial min-heap:\n";
    heap.print();

    cout << "\nInserting new parcel with urgency 2...\n\n";
    heap.insert(2);

    cout << "Heap after insertion:\n";
    heap.print();

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
