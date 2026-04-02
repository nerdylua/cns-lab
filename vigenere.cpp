#include <iostream>
#include <string>
using namespace std;

string vigenere(const string& text, const string& key, bool encrypt) {
    string out;
    int j = 0;
    for (char ch : text) {
        if (!isalpha(ch)) { out += ch; continue; }
        char b = isupper(ch) ? 'A' : 'a';
        int shift = toupper(key[j % key.size()]) - 'A';
        if (!encrypt) shift = 26 - shift;
        out += char(b + (ch - b + shift) % 26);
        j++;
    }
    return out;
}

int main() {
    int mode;
    string text, key;
    cout << "Text: "; getline(cin, text);
    cout << "Key: "; getline(cin, key);
    cout << "1=Encrypt 2=Decrypt: "; cin >> mode;
    cout << vigenere(text, key, mode == 1) << "\n";
}