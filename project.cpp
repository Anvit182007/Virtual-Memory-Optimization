#include <bits/stdc++.h>
using namespace std;

/******************************
     SEGMENTATION MODULE
*******************************/
class Segmentation
{
public:
    struct Segment
    {
        int base;
        int limit;
    };

    vector<Segment> segments;

    void createSegments(int n)
    {
        segments.resize(n);
        cout << "\nEnter base and limit for each segment:\n";
        for (int i = 0; i < n; i++)
        {
            cout << "Segment " << i << " base: ";
            cin >> segments[i].base;
            cout << "Segment " << i << " limit: ";
            cin >> segments[i].limit;
        }
    }

    void translateAddress()
    {
        int seg, offset;
        cout << "Enter segment number: ";
        cin >> seg;
        cout << "Enter offset: ";
        cin >> offset;

        if (seg >= segments.size())
        {
            cout << "Invalid segment!\n";
            return;
        }

        if (offset > segments[seg].limit)
        {
            cout << "Segmentation Fault!\n";
            return;
        }

        cout << "Physical address = " << segments[seg].base + offset << "\n";
    }
};

int main()
{
    cout << "\n=== Virtual Memory Management Simulator ===\n";

    while (true)
    {
        cout << "\n1. Segmentation\n";
        cout << "2. Paging\n";
        cout << "3. Memory Fragmentation\n";
        cout << "4. Exit\n";
        cout << "Choose option: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            Segmentation s;
            int n;
            cout << "Enter number of segments: ";
            cin >> n;
            s.createSegments(n);
            s.translateAddress();
        }
        else if (choice == 4)
        {
            cout << "Exiting simulator...\n";
            break;
        }
        else
        {
            cout << "Feature under development.\n";
        }
    }

    return 0;
}
