#pragma once
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>
#include <map>
using namespace std;
class AdjMatrix
{
    // ========META-DATA======== //
    int poolsize;
    vector<int> rankingset;
    map<string,string> matches;			//indexed by woman
    // ====NAME DICTIONARIES==== //
    vector<string> men;
    vector<string> women;
    // ===ADJACENCY MATRICES=== //
    vector<vector<int>> womensPrefGraph;
    vector<vector<int>> mensPrefGraph;
public:
    AdjMatrix(string& fname, int N);
    void loadData(string& fname, int N);
    void setPreferences();
    bool WomanPrefersMOverM2(int w, int m, int m2) const;
    map<string, string>& GenerateMatches();
};
