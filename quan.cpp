#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Generate a random page-reference string
void generateRandomPageReferences(vector<int>& pageRefs, int numPages)
{
    srand(time(nullptr));
    for (int i = 0; i < numPages; i++) {
        pageRefs.push_back(rand() % 10);
    }
}

// Second-chance page replacement algorithm
int secondChance(const vector<int>& pageRefs, int numFrames)
{
    int numFaults = 0;
    vector<bool> referenced(numFrames, false);
    vector<int> frames(numFrames, -1);
    int hand = 0;

    for (int page : pageRefs) {
        bool found = false;
        while (!found) {
            if (frames[hand] == -1) {
                frames[hand] = page;
                numFaults++;
                referenced[hand] = true;
                found = true;
            } else if (frames[hand] == page) {
                referenced[hand] = true;
                found = true;
            } else if (referenced[hand]) {
                referenced[hand] = false;
                hand = (hand + 1) % numFrames;
            } else {
                frames[hand] = page;
                numFaults++;
                referenced[hand] = true;
                hand = (hand + 1) % numFrames;
                found = true;
            }
        }
    }
    return numFaults;
}

int main()
{
    vector<int> pageRefs;
    generateRandomPageReferences(pageRefs, 100);

    for (int numFrames = 1; numFrames <= 7; numFrames++) {
        int numFaults = secondChance(pageRefs, numFrames);
        cout << "Second-chance with " << numFrames << " frames: " << numFaults << " faults" << endl;
    }

    return 0;
}
