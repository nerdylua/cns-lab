#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string caesar(string s, int k) {
    k = (k % 26 + 26) % 26;
    for (char& ch : s) {
        if (!isalpha((unsigned char)ch)) continue;
        char b = isupper((unsigned char)ch) ? 'A' : 'a';
        ch = char(b + (ch - b + k) % 26);
    }
    return s;
}

char norm(char ch) {
    if (!isalpha((unsigned char)ch)) return 0;
    ch = char(toupper((unsigned char)ch));
    return ch == 'J' ? 'I' : ch;
}

string onlyAZ(const string& s) {
    string out;
    for (char ch : s) {
        char n = norm(ch);
        if (n) out += n;
    }
    return out;
}

void buildSquare(const string& key, char g[5][5], int pos[26]) {
    bool used[26] = {};
    used['J' - 'A'] = true;
    string seq;

    for (char ch : key) {
        char n = norm(ch);
        if (n && !used[n - 'A']) used[n - 'A'] = true, seq += n;
    }
    for (char ch = 'A'; ch <= 'Z'; ++ch) if (!used[ch - 'A']) seq += ch;
    for (int i = 0; i < 25; ++i) g[i / 5][i % 5] = seq[i], pos[seq[i] - 'A'] = i;
}

string prepPlayfair(string s, bool enc) {
    s = onlyAZ(s);
    if (!enc) {
        if (s.size() % 2) s += 'X';
        return s;
    }

    string out;
    for (size_t i = 0; i < s.size();) {
        char a = s[i], b = (i + 1 < s.size()) ? s[i + 1] : 'X';
        if (a == b) out += a, out += 'X', ++i;
        else out += a, out += b, i += 2;
    }
    if (out.size() % 2) out += 'X';
    return out;
}

string playfair(const string& text, const string& key, bool enc) {
    char g[5][5];
    int pos[26] = {};
    buildSquare(key, g, pos);

    string p = prepPlayfair(text, enc), out;
    int d = enc ? 1 : 4;
    for (size_t i = 0; i < p.size(); i += 2) {
        int a = pos[p[i] - 'A'], b = pos[p[i + 1] - 'A'];
        int r1 = a / 5, c1 = a % 5, r2 = b / 5, c2 = b % 5;

        if (r1 == r2) out += g[r1][(c1 + d) % 5], out += g[r2][(c2 + d) % 5];
        else if (c1 == c2) out += g[(r1 + d) % 5][c1], out += g[(r2 + d) % 5][c2];
        else out += g[r1][c2], out += g[r2][c1];
    }
    return out;
}

int main() {
    int algo, mode;
    string text, key;
    cout << "1 Caesar 2 Playfair: ";
    cin >> algo;
    cin.ignore();

    cout << "Text: ";
    getline(cin, text);
    cout << "1 Encrypt 2 Decrypt: ";
    cin >> mode;
    cin.ignore();

    if (algo == 1) {
        int shift;
        cout << "Shift: ";
        cin >> shift;
        cout << caesar(text, mode == 1 ? shift : -shift) << "\n";
    } else {
        cout << "Key: ";
        getline(cin, key);
        cout << playfair(text, key, mode == 1) << "\n";
    }
}
