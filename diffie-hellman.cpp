#include <iostream>
using namespace std;
using ll = long long;

ll mod_pow(ll b, ll e, ll m) {
    ll r = 1;
    for (b %= m; e; e >>= 1) {
        if (e & 1) r = r * b % m;
        b = b * b % m;
    }
    return r;
}

int main() {
    ll p, g, a, b;
    cout << "Enter prime (p): ";
    cin >> p;
    cout << "Enter generator (g): ";
    cin >> g;
    cout << "Alice's private key (a): ";
    cin >> a;
    cout << "Bob's private key (b): ";
    cin >> b;

    ll A = mod_pow(g, a, p);
    ll B = mod_pow(g, b, p);
    ll ka = mod_pow(B, a, p), kb = mod_pow(A, b, p);

    cout << "\nAlice sends: A = g^a mod p = " << A << "\n";
    cout << "Bob sends:   B = g^b mod p = " << B << "\n";
    cout << "\nAlice computes: B^a mod p = " << ka << "\n";
    cout << "Bob computes:   A^b mod p = " << kb << "\n";

    if (ka == kb) cout << "\nShared secret: " << ka << "\n";
    else cout << "\nError: keys don't match!\n";
}
