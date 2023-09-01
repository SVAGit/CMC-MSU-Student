#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

bool is_boring(const vector<int>& v) {
    unordered_map<int, int> freq;
    for (int x : v) {
        freq[x]++;
    }
    int min_freq = n, max_freq = 0;
    for (const auto& p : freq) {
        min_freq = min(min_freq, p.second);
        max_freq = max(max_freq, p.second);
    }
    return (max_freq - min_freq) <= 1;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 1;
    for (int l = n; l >= 2; l--) {
        if (is_boring(vector<int>(a.begin(), a.begin() + l))) {
            ans = l;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}

