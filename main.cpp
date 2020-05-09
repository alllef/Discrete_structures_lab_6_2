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

void initializeGraph(int &picks, int &ribs, vector<Rib> &structRibs);

void sortRibs(int &picks, int &ribs, vector<Rib> &structRibs);

vector<int> colorize(int &picks, int &ribs, vector<Rib> &structRibs);

vector<int> sortByDegree(int &picks, int &ribs, vector<Rib> &structRibs);

bool existsUncoloredPick(vector<int>&picks);

bool hasAdjacentPick(int pick, vector<Rib> &structRibs, vector<int> &colors, int color);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<Rib> ribsList;
    int n = 0, m = 0;
    initializeGraph(n,m,ribsList);
    sortRibs(n,m,ribsList);
    colorize(n,m,ribsList);
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
    vector<int> sortedPicks;

    for (int i = 1; i <= picks; i++) {
        sortedPicks.push_back(i);
        for (int j = 0; j < structRibs.size(); j++) {
            if (structRibs[j].start == i || structRibs[j].end==i)degree++;
        }
        degrees[i - 1] = degree;
        degree = 0;
    }
    for (int i = 0; i < picks; i++) {
        for (int j = 0; j < picks - 1; j++) {
            if (degrees[sortedPicks[j]-1] < degrees[sortedPicks[j+1]-1]) {
                int tmpPick = sortedPicks[j+1];
                sortedPicks[j+1] = sortedPicks[j];
                sortedPicks[j] = tmpPick;
            }
        }
    }
    return sortedPicks;
}

vector<int> colorize(int &picks, int &ribs, vector<Rib> &structRibs) {
    int color = 0;
    vector<int> sortedPicks = sortByDegree(picks, ribs, structRibs);
    vector<int> pickColors(picks, 0);
    while (existsUncoloredPick(pickColors)) {
        color++;

        for (int i = 0; i < sortedPicks.size(); i++) {
            if (hasAdjacentPick(sortedPicks[i],structRibs,pickColors,color))continue;
            else {
                pickColors[sortedPicks[i]-1]=color;
            }
        }

    }
    return pickColors;
}


bool hasAdjacentPick(int pick, vector<Rib> &structRibs, vector<int> &colors, int color) {
    if (colors[pick - 1] != 0)return true;
    for (int i = 0; i < structRibs.size(); i++) {
        if (structRibs[i].start == pick && colors[structRibs[i].end - 1] == color) return true;
        if (structRibs[i].end == pick && colors[structRibs[i].start - 1] == color) return true;
    }
    return false;
}

bool existsUncoloredPick(vector<int>&picks){
    for(int i=0; i<picks.size(); i++){
        if(picks[i]==0)return true;
    }
    return false;
}
