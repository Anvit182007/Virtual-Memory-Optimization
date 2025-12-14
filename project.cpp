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

/******************************
     PAGING + PAGE FAULT MODULE
*******************************/
class Paging {
public:
    vector<int> frames;
    int frameCount;

    Paging(int f) {
        frameCount = f;
        frames.assign(f, -1);
    }

    void showFrames() {
        cout << "\nCurrent Frames: ";
        for(int f : frames) cout << f << " ";
        cout << "\n";
    }

    // LRU Page Replacement
    int LRU(vector<int>& pages) {
        int pageFaults = 0;
        vector<int> recent(frameCount, -1);

        for(int i = 0; i < pages.size(); i++) {
            int page = pages[i];
            bool hit = false;

            for(int j = 0; j < frameCount; j++) {
                if(frames[j] == page) {
                    hit = true;
                    recent[j] = i;
                }
            }

            if(!hit) {
                pageFaults++;

                int replaceIndex = -1;
                int least = INT_MAX;

                for(int j = 0; j < frameCount; j++) {
                    if(recent[j] < least) {
                        least = recent[j];
                        replaceIndex = j;
                    }
                }

                frames[replaceIndex] = page;
                recent[replaceIndex] = i;
            }

            showFrames();
        }

        return pageFaults;
    }

    // Optimal Page Replacement
    int Optimal(vector<int>& pages) {
        int pageFaults = 0;

        for(int i = 0; i < pages.size(); i++) {
            int page = pages[i];
            bool hit = false;

            for(int f : frames) if(f == page) hit = true;

            if(!hit) {
                pageFaults++;

                int replaceIndex = -1;
                int farthest = -1;

                for(int j = 0; j < frameCount; j++) {
                    int nextUse = INT_MAX;
                    for(int k = i + 1; k < pages.size(); k++) {
                        if(frames[j] == pages[k]) {
                            nextUse = k;
                            break;
                        }
                    }
                    if(nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }

                frames[replaceIndex] = page;
            }

            showFrames();
        }
        return pageFaults;
    }
};

/******************************
     MEMORY FRAGMENTATION
*******************************/
class Fragmentation {
public:
    void simulate() {
        int memorySize;
        cout << "Enter total memory size: ";
        cin >> memorySize;

        int processCount;
        cout << "Enter number of processes: ";
        cin >> processCount;

        vector<int> process(processCount);
        for(int i = 0; i < processCount; i++) {
            cout << "Enter size of process " << i << ": ";
            cin >> process[i];
        }

        int used = 0;
        for(int i = 0; i < processCount;
            i++) {
            if(used + process[i] <= memorySize) {
                used += process[i];
                cout << "Process " << i << " allocated.\n";
            } else {
                cout << "Process " << i << " not allocated (fragmentation)!\n";
            }
        }

        cout << "\nInternal Fragmentation = " 
             << memorySize - used << " units\n";
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
        
        else if(choice == 2) {
            int frameCount;
            cout << "Enter number of frames: ";
            cin >> frameCount;

            Paging p(frameCount);

            int n;
            cout << "Enter number of page references: ";
            cin >> n;

            vector<int> pages(n);
            cout << "Enter pages: ";
            for(int i = 0; i < n; i++) cin >> pages[i];

            cout << "\nChoose Algorithm:\n1. LRU\n2. Optimal\nYour choice: ";
            int algo;
            cin >> algo;

            int faults = 0;
            if(algo == 1)
                faults = p.LRU(pages);
            else
                faults = p.Optimal(pages);

            cout << "\nTotal Page Faults = " << faults << "\n";
        }

        else if(choice == 3) {
            Fragmentation f;
            f.simulate();
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
