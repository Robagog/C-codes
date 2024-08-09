#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int GetMaxCut(const vector<int>& wires, int k, int maxLength) {
    int left = 1, right = maxLength;
    int maxCut = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int segments = 0;
        for (const auto& wire : wires) {
            segments += wire / mid; 
        }
        if (segments >= k) {
            maxCut = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
       
    }

    return maxCut;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> wires(n);
    cin >> wires[0];
    int maxLength = wires[0];
    for (int i = 1; i < n; i++) {
        cin >> wires[i];
        if (maxLength < wires[i]) {
            maxLength = wires[i];
        }
    }
    int result = GetMaxCut(wires, k, maxLength);
    cout << result << endl;

    return 0;
}