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

        if (bucket + incoming > bucketSize) {
            cout << "Packet dropped! Overflow. Accepting only: " << bucketSize - bucket << "\n";
            incoming = bucketSize - bucket;
        }

        bucket += incoming;
        cout << "Transmission left: " << bucket << "\n";

        int nextTime;
        cout << "Next packet will come at: ";
        cin >> nextTime;

        while (nextTime > 0) {
            if (bucket > 0) {
                bucket -= outputRate;
                if (bucket < 0) bucket = 0;
                cout << "Time left " << nextTime << "--------No packets to transmit!! Transmitted\n";
                cout << "Bytes remaining: " << bucket << "\n";
            } else {
                cout << "Time left " << nextTime << "--------No packets to transmit!!\n";
            }
            --nextTime;
        }
    }
}
