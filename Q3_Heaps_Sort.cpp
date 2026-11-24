// Q3: Build Max-Heap / Min-Heap, delete elements, and Heap Sort
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Heap {
    vector<int> a;
    bool isMax;

    bool before(int x, int y) const { return isMax ? x > y : x < y; }

    void siftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (before(a[i], a[p])) { swap(a[i], a[p]); i = p; }
            else break;
        }
    }
    void siftDown(int i, int n) {
        while (true) {
            int l = 2 * i + 1, r = l + 1, b = i;
            if (l < n && before(a[l], a[b])) b = l;
            if (r < n && before(a[r], a[b])) b = r;
            if (b == i) break;
            swap(a[i], a[b]);
            i = b;
        }
    }
public:
    Heap(const vector<int>& arr, bool maxHeap) : a(arr), isMax(maxHeap) {
        for (int i = (int)a.size() / 2 - 1; i >= 0; i--) siftDown(i, (int)a.size());  // bottom-up build
    }

    bool remove(int val) {
        vector<int>::iterator it = find(a.begin(), a.end(), val);
        if (it == a.end()) return false;
        int i = (int)(it - a.begin());
        a[i] = a.back();
        a.pop_back();
        if (i < (int)a.size()) { siftUp(i); siftDown(i, (int)a.size()); }
        return true;
    }

    vector<int> heapSortAscending() const {   // works on a copy; only valid for max-heap
        Heap t = *this;
        for (int end = (int)t.a.size() - 1; end > 0; end--) {
            swap(t.a[0], t.a[end]);
            t.siftDown(0, end);
        }
        return t.a;
    }

    void print(const string& title) const {
        cout << title << "\n  Array: ";
        for (size_t k = 0; k < a.size(); k++) cout << a[k] << " ";
        cout << "\n";
        int n = (int)a.size(), level = 0, i = 0;
        while (i < n) {
            int cnt = 1 << level;
            cout << "  Level " << level << ": ";
            for (int k = 0; k < cnt && i < n; k++, i++) cout << a[i] << " ";
            cout << "\n";
            level++;
        }
        cout << "\n";
    }
};

int main() {
    int init[] = {25, 30, 35, 11, 15, 19, 18, 55, 78, 36};
    vector<int> arr(init, init + 10);

    cout << "Original array: ";
    for (size_t k = 0; k < arr.size(); k++) cout << arr[k] << " ";
    cout << "\n\n";

    // (a) Max-Heap, remove 55
    Heap maxH(arr, true);
    maxH.print("Max-Heap built from array:");
    if (maxH.remove(55)) maxH.print("Max-Heap after removing 55:");
    else cout << "55 not found\n";

    // (b) Min-Heap, remove 18
    Heap minH(arr, false);
    minH.print("Min-Heap built from array:");
    if (minH.remove(18)) minH.print("Min-Heap after removing 18:");
    else cout << "18 not found\n";

    // (c) Heap Sort on the max-heap
    vector<int> sorted = maxH.heapSortAscending();
    cout << "Heap Sort output (ascending, from the max-heap after removing 55):\n  ";
    for (size_t k = 0; k < sorted.size(); k++) cout << sorted[k] << " ";
    cout << "\n";

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
