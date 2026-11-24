// Q2: Delete (extract) the root of a binary max-heap
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

class MaxHeap {
    vector<int> h;
    void siftDown(int i) {
        int n = (int)h.size();
        while (true) {
            int l = 2 * i + 1, r = l + 1, big = i;
            if (l < n && h[l] > h[big]) big = l;
            if (r < n && h[r] > h[big]) big = r;
            if (big == i) break;
            swap(h[i], h[big]);
            i = big;
        }
    }
public:
    MaxHeap(const vector<int>& init) : h(init) {}

    bool extractMax(int& out) {
        if (h.empty()) return false;
        out = h[0];
        h[0] = h.back();     // move last element to root
        h.pop_back();
        if (!h.empty()) siftDown(0);
        return true;
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
    int init[] = {90, 80, 70, 50, 60, 40, 30, 20, 10};   // valid max-heap
    vector<int> start(init, init + 9);
    MaxHeap heap(start);

    cout << "Initial max-heap:\n";
    heap.print();

    int item;
    if (heap.extractMax(item)) {
        cout << "\nProcessing highest-priority item: " << item << "\n\n";
    }
    cout << "Heap after deleting root:\n";
    heap.print();

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
