#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "\n=== Virtual Memory Management Simulator ===\n";

    while (true) {
        cout << "\n1. Segmentation\n";
        cout << "2. Paging\n";
        cout << "3. Memory Fragmentation\n";
        cout << "4. Exit\n";
        cout << "Choose option: ";

        int choice;
        cin >> choice;

        if (choice == 4) {
            cout << "Exiting simulator...\n";
            break;
        } else {
            cout << "Feature under development.\n";
        }
    }

    return 0;
}
