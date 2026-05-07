#include <iostream>
#include <string>
#include <sstream>
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
    ll p, q, e;
    cout << "Enter prime p: ";
    cin >> p;
    cout << "Enter prime q: ";
    cin >> q;

    ll n = p * q, phi = (p - 1) * (q - 1), d = 1;
    cout << "Enter public exponent e (coprime to " << phi << "): ";
    cin >> e;
    while (d < phi && (d * e) % phi != 1) ++d;
    if (d == phi) return 0;

    cout << "\nPublic key:  (e=" << e << ", n=" << n << ")\n";
    cout << "Private key: (d=" << d << ", n=" << n << ")\n\n";

    int mode;
    cout << "1=Encrypt 2=Decrypt: ";
    cin >> mode;
    cin.ignore();

    if (mode == 1) {
        string text;
        cout << "Plaintext: ";
        getline(cin, text);
        cout << "Encrypted: ";
        for (size_t i = 0; i < text.size(); ++i) {
            cout << mod_pow((unsigned char)text[i], e, n);
            if (i + 1 < text.size()) cout << " ";
        }
        cout << "\n";
    } else {
        string line;
        cout << "Ciphertext (space-separated numbers): ";
        getline(cin, line);
        stringstream ss(line);
        ll x;
        cout << "Decrypted: ";
        while (ss >> x) cout << char(mod_pow(x, d, n));
        cout << "\n";
    }
}
