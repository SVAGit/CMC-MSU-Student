#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int is_boring(int* v, int n) {
    int freq[MAXN] = {0};
    for (int i = 0; i < n; i++) {
        freq[v[i]]++;
    }
    int min_freq = n, max_freq = 0;
    for (int i = 0; i < MAXN; i++) {
        if (freq[i] > 0) {
            min_freq = min(min_freq, freq[i]);
            max_freq = max(max_freq, freq[i]);
        }
    }
    return (max_freq - min_freq) <= 1;
}

int main() {
    int n;
    scanf("%d", &n);
    int a[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int ans = 1;
    for (int l = n; l >= 2; l--) {
        if (is_boring(a, l)) {
            ans = l;
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}
