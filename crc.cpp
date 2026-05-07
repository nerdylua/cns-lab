#include <iostream>
#include <string>
using namespace std;

const string POLY = "10001000000100001"; // CRC-CCITT

string crcRemainder(string bits) {
    string r = bits;
    for (size_t i = 0; i + POLY.size() <= r.size(); ++i) {
        if (r[i] == '1') {
            for (size_t j = 0; j < POLY.size(); ++j)
                r[i + j] = (r[i + j] == POLY[j]) ? '0' : '1';
        }
    }
    return r.substr(r.size() - (POLY.size() - 1));
}

int main() {
    string data;
    cout << "Enter data: ";
    cin >> data;

    string modified = data + string(POLY.size() - 1, '0');
    string checksum = crcRemainder(modified);
    string codeword = data + checksum;

    cout << "Modified data  : " << modified << "\n";
    cout << "Checksum       : " << checksum << "\n";
    cout << "Final codeword : " << codeword << "\n";

    int choice;
    cout << "\nTest error detection? 0(yes) 1(no): ";
    cin >> choice;
    if (choice == 0) {
        int pos;
        cout << "Enter error position (1-indexed): ";
        cin >> pos;
        if (pos >= 1 && pos <= (int)codeword.size()) codeword[pos - 1] ^= 1;
        cout << "Erroneous data : " << codeword << "\n";
    }

    cout << (crcRemainder(codeword) == string(POLY.size() - 1, '0') ? "No error detected" : "Error detected") << "\n";
}
