#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include<Windows.h>

using namespace std;

struct Rib {
public:
    int start;
    int end;
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<Rib> ribsList;
    int n = 0, m = 0;
    return 0;
}

void initializeGraph(int &picks, int &ribs, vector<Rib> &structRibs) {
    Rib myRib{};
    ifstream inFile;
    inFile.open("myGraph.txt");

    if (!inFile.is_open()) cout << "It is not open" << endl;
    inFile >> picks >> ribs;

    for (int i = 0; i < ribs; i++) {
        inFile >> myRib.start >> myRib.end;

        structRibs.push_back(myRib);
    }
    inFile.close();
}

void sortRibs(int &picks, int &ribs, vector<Rib> &structRibs) {

    Rib tmp{};
    for (int i = 0; i < ribs - 1; i++) {
        for (int j = 0; j < ribs - 1; j++) {
            if ((structRibs[j].start + structRibs[j].end) > (structRibs[j + 1].start + structRibs[j + 1].end)) {

                tmp = structRibs[j];
                structRibs[j] = structRibs[j + 1];
                structRibs[j + 1] = tmp;

            }
        }
    }
}

vector<int> sortByDegree(int &picks, int &ribs, vector<Rib> &structRibs) {
    int degree = 0;
    vector<int> degrees(picks);
    vector<int>picks
    for (int i = 1; i < picks; i++) {
        for (int j = 0; j < structRibs.size(); j++) {
            if (structRibs[i].start == i || structRibs[i].end)degree++;
        }
        degrees[i - 1] = degree;
        degree=0;
    }

}