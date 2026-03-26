#include <iostream>
#include <string>
using namespace std;

string poly = "10001000000100001"; // CRC-CCITT polynomial

string xorOp(string a, string b) {
    string result = "";
    for (int i = 0; i < (int)b.length(); i++)
        result += (a[i] == b[i]) ? '0' : '1';
    return result;
}

string crcDivide(string data) {
    int plen = poly.length();
    string rem = data.substr(0, plen);

    for (int i = plen; i <= (int)data.length(); i++) {
        if (rem[0] == '1')
            rem = xorOp(rem, poly);
        else
            rem = xorOp(rem, string(plen, '0'));

        if (i < (int)data.length())
            rem = rem.substr(1) + data[i];
        else
            rem = rem.substr(1);
    }
    return rem;
}

int main() {
    string data;
    cout << "Enter data: ";
    cin >> data;

    // Pad 16 zeros
    string padded = data + string(poly.length() - 1, '0');
    cout << "Modified data  : " << padded << endl;

    // Get checksum
    string checksum = crcDivide(padded);
    cout << "Checksum       : " << checksum << endl;

    // Final codeword
    string codeword = data + checksum;
    cout << "Final codeword : " << codeword << endl;

    // Error detection test
    int choice;
    cout << "\nTest error detection? 0(yes) 1(no): ";
    cin >> choice;

    if (choice == 0) {
        int pos;
        cout << "Enter error position (1-indexed): ";
        cin >> pos;
        codeword[pos - 1] = (codeword[pos - 1] == '0') ? '1' : '0';
        cout << "Erroneous data : " << codeword << endl;
    }

    // Check for error
    string remainder = crcDivide(codeword);
    bool error = (remainder.find('1') != string::npos);
    cout << (error ? "Error detected" : "No error detected") << endl;

    return 0;
}