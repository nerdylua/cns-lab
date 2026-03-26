#include <iostream>
using namespace std;

int main() {
    int bucketSize, outputRate, bucket = 0;

    cout << "Enter output rate: ";
    cin >> outputRate;
    cout << "Enter bucket size: ";
    cin >> bucketSize;

    while (true) {
        int incoming;
        cout << "Incoming packet: ";
        cin >> incoming;

        if (incoming == 0) {
            cout << "Transmission left: 0" << endl;
            int next;
            cout << "Next packet will come at: ";
            cin >> next;
            continue;
        }

        // Overflow check
        if (bucket + incoming > bucketSize) {
            cout << "Packet dropped! Overflow. Accepting only: " << bucketSize - bucket << endl;
            incoming = bucketSize - bucket;
        }

        bucket += incoming;
        cout << "Transmission left: " << bucket << endl;

        int timeLeft;
        cout << "Next packet will come at: ";
        cin >> timeLeft;

        // Countdown from timeLeft
        while (timeLeft > 0) {
            if (bucket > 0) {
                bucket -= outputRate;
                if (bucket < 0) bucket = 0;
                cout << "Time left " << timeLeft << "--------No packets to transmit!! Transmitted" << endl;
                cout << "Bytes remaining: " << bucket << endl;
            } else {
                cout << "Time left " << timeLeft << "--------No packets to transmit!!" << endl;
            }
            timeLeft--;
        }
    }

    return 0;
}