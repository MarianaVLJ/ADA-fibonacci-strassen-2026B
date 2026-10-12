#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef long long int ll;
const ll MOD = 1e9 + 7; 

ll fibonacci_On(int n) {
    if (n <= 1) return n;
    ll a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

void multiply(ll F[2][2], ll M[2][2]) {
    ll x = (F[0][0] * M[0][0] + F[0][1] * M[1][0]) % MOD;
    ll y = (F[0][0] * M[0][1] + F[0][1] * M[1][1]) % MOD;
    ll z = (F[1][0] * M[0][0] + F[1][1] * M[1][0]) % MOD;
    ll w = (F[1][0] * M[0][1] + F[1][1] * M[1][1]) % MOD;
    F[0][0] = x; F[0][1] = y; F[1][0] = z; F[1][1] = w;
}

void power(ll F[2][2], int n) {
    if (n == 0 || n == 1) return;
    ll M[2][2] = {{1, 1}, {1, 0}};
    power(F, n / 2);
    multiply(F, F);
    if (n % 2 != 0) multiply(F, M);
}

ll fibonacci_Ologn(int n) {
    if (n == 0) return 0;
    ll F[2][2] = {{1, 1}, {1, 0}};
    power(F, n - 1);
    return F[0][0];
}

int main() {
    vector<int> test_cases = {1000, 10000, 100000, 500000, 1000000};
    
    cout << "--- Analisis Empirico Fibonacci ---\n";
    for (int n : test_cases) {
        cout << "\nN = " << n << "\n";
        
        auto start = high_resolution_clock::now();
        ll res1 = fibonacci_On(n);
        auto stop = high_resolution_clock::now();
        auto duration_On = duration_cast<microseconds>(stop - start);
        cout << "Tiempo O(n): \t" << duration_On.count() << " microsegundos\n";

        start = high_resolution_clock::now();
        ll res2 = fibonacci_Ologn(n);
        stop = high_resolution_clock::now();
        auto duration_Ologn = duration_cast<microseconds>(stop - start);
        cout << "Tiempo O(log n): \t" << duration_Ologn.count() << " microsegundos\n";
    }
    return 0;
}