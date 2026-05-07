#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string vigenere(string s, const string& key, bool enc) {
    int j = 0;
    for (char& ch : s) {
        if (!isalpha((unsigned char)ch)) continue;
        char b = isupper((unsigned char)ch) ? 'A' : 'a';
        int sh = toupper((unsigned char)key[j++ % key.size()]) - 'A';
        if (!enc) sh = 26 - sh;
        ch = char(b + (ch - b + sh) % 26);
    }
    return s;
}

int main() {
    int mode;
    string text, key;
    cout << "Text: ";
    getline(cin, text);
    cout << "Key: ";
    getline(cin, key);
    if (key.empty()) return 0;
    cout << "1 Encrypt 2 Decrypt: ";
    cin >> mode;
    cout << vigenere(text, key, mode == 1) << "\n";
}
