#include <iostream>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

string caesar(const string& text, int shift, bool encrypt) {
    string out;
    shift = ((shift % 26) + 26) % 26;
    if (!encrypt) shift = (26 - shift) % 26;
    for (char ch : text) {
        if (!isalpha((unsigned char)ch)) { out += ch; continue; }
        char b = isupper((unsigned char)ch) ? 'A' : 'a';
        out += char(b + (ch - b + shift) % 26);
    }
    return out;
}

struct Playfair {
    char g[5][5];
    int r[26] = {}, c[26] = {};

    static char norm(char ch) {
        if (!isalpha((unsigned char)ch)) return '\0';
        ch = char(toupper((unsigned char)ch));
        return ch == 'J' ? 'I' : ch;
    }

    static string clean(const string& text) {
        string s;
        for (char ch : text) {
            char n = norm(ch);
            if (n) s += n;
        }
        return s;
    }

    void build(const string& key) {
        bool used[26] = {};
        used['J' - 'A'] = true;
        string seq;
        for (char ch : key) {
            char n = norm(ch);
            if (n && !used[n - 'A']) used[n - 'A'] = true, seq += n;
        }
        for (char ch = 'A'; ch <= 'Z'; ch++) if (!used[ch - 'A']) seq += ch;
        for (int i = 0; i < 25; i++) g[i / 5][i % 5] = seq[i], r[seq[i] - 'A'] = i / 5, c[seq[i] - 'A'] = i % 5;
    }

    string prep(const string& text, bool encrypt) {
        string s = clean(text), out;
        if (!encrypt) {
            if (s.size() % 2) s += 'X';
            return s;
        }
        for (size_t i = 0; i < s.size();) {
            char a = s[i], b = (i + 1 < s.size()) ? s[i + 1] : 'X';
            if (a == b) out += a, out += 'X', i += 1;
            else out += a, out += b, i += 2;
        }
        if (out.size() % 2) out += 'X';
        return out;
    }

    string run(const string& text, bool encrypt) {
        string p = prep(text, encrypt), out;
        int d = encrypt ? 1 : 4;
        for (size_t i = 0; i < p.size(); i += 2) {
            int r1 = r[p[i] - 'A'], c1 = c[p[i] - 'A'];
            int r2 = r[p[i + 1] - 'A'], c2 = c[p[i + 1] - 'A'];
            if (r1 == r2) out += g[r1][(c1 + d) % 5], out += g[r2][(c2 + d) % 5];
            else if (c1 == c2) out += g[(r1 + d) % 5][c1], out += g[(r2 + d) % 5][c2];
            else out += g[r1][c2], out += g[r2][c1];
        }
        return out;
    }
};

int main() {
    int ch, mode;
    string text;
    cout << "1. Caesar 2. Playfair: ";
    if (!(cin >> ch) || (ch != 1 && ch != 2)) return 1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Text: "; getline(cin, text);
    cout << "1 = Encrypt 2 = Decrypt: ";
    if (!(cin >> mode) || (mode != 1 && mode != 2)) return 1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (ch == 1) {
        int shift;
        cout << "Shift: ";
        if (!(cin >> shift)) return 1;
        cout << caesar(text, shift, mode == 1) << "\n";
    } else {
        string key;
        cout << "Key: "; getline(cin, key);
        Playfair pf; pf.build(key);
        cout << pf.run(text, mode == 1) << "\n";
    }
}
