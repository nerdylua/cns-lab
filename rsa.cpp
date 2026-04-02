#include <iostream>
#include <string>
#include <vector>
using namespace std;

using ll = long long;

ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll mod_inverse(ll e, ll phi) {
    ll t = 0, new_t = 1, r = phi, new_r = e;
    while (new_r != 0) {
        ll q = r / new_r;
        t -= q * new_t; swap(t, new_t);
        r -= q * new_r; swap(r, new_r);
    }
    return t < 0 ? t + phi : t;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ll p, q;
    cout << "Enter prime p: "; cin >> p;
    cout << "Enter prime q: "; cin >> q;

    if (!is_prime(p) || !is_prime(q)) {
        cout << "Both must be prime!\n"; return 1;
    }

    ll n = p * q;
    ll phi = (p - 1) * (q - 1);

    ll e;
    cout << "Enter public exponent e (coprime to " << phi << "): "; cin >> e;

    if (gcd(e, phi) != 1) {
        cout << "e must be coprime to phi!\n"; return 1;
    }

    ll d = mod_inverse(e, phi);

    cout << "\n";
    cout << "Public key:  (e=" << e << ", n=" << n << ")\n";
    cout << "Private key: (d=" << d << ", n=" << n << ")\n\n";

    cin.ignore();
    int mode;
    cout << "1=Encrypt 2=Decrypt: "; cin >> mode; cin.ignore();

    if (mode == 1) {
        string text;
        cout << "Plaintext: "; getline(cin, text);
        cout << "Encrypted: ";
        for (char ch : text)
            cout << mod_pow(ch, e, n) << " ";
        cout << "\n";
    } else {
        string line;
        cout << "Ciphertext (space-separated numbers): ";
        getline(cin, line);
        cout << "Decrypted: ";
        size_t pos = 0;
        while (pos < line.size()) {
            size_t next = line.find(' ', pos);
            if (next == string::npos) next = line.size();
            ll val = stoll(line.substr(pos, next - pos));
            cout << char(mod_pow(val, d, n));
            pos = next + 1;
        }
        cout << "\n";
    }
}