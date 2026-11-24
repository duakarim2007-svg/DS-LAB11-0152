// Q7: Find two pairs (a,b),(c,d) with a+b == c+d using hashing
// Since all elements are distinct, two different pairs with the same sum
// can never share an element (a+b = a+d would force b = d), so all four are distinct.
// Uses std::map as the hash container (works on old compilers; unordered_map needs C++11).
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <cstdlib>
using namespace std;

void findPairs(const vector<int>& arr) {
    map<int, pair<int, int> > sumMap;   // sum -> first pair seen with that sum
    int n = (int)arr.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int s = arr[i] + arr[j];
            map<int, pair<int, int> >::iterator it = sumMap.find(s);
            if (it != sumMap.end()) {
                cout << "(" << it->second.first << ", " << it->second.second << ") and ("
                     << arr[i] << ", " << arr[j] << ")\n";
                return;
            }
            sumMap[s] = make_pair(arr[i], arr[j]);
        }
    }
    cout << "No pairs found\n";
}

void runTest(const int* data, int n) {
    vector<int> t(data, data + n);
    cout << "Input: {";
    for (int i = 0; i < n; i++) cout << t[i] << (i + 1 < n ? ", " : "");
    cout << "}\nOutput: ";
    findPairs(t);
    cout << "\n";
}

int main() {
    int a1[] = {3, 4, 7, 1, 2, 9, 8};
    int a2[] = {3, 4, 7, 1, 12, 9};
    int a3[] = {65, 30, 7, 90, 1, 9, 8};
    runTest(a1, 7);
    runTest(a2, 6);
    runTest(a3, 7);

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
