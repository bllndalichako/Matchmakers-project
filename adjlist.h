#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;
typedef vector<string> PrefList;
typedef vector<string> DataSet;
typedef map<string, string> Couples;
class AdjList {
    map<string, PrefList> PrefGraph;
    // variables to store the dataset by gender
    DataSet men;
    DataSet women;
 public:
    void loadData(string);
    void setPreferences(queue<string>&); // fixme potential problem
    void matchCouples(queue<string>&, Couples&);
    bool prefers(const PrefList&, const string&, const string&);
    void stability(const Couples &engaged);
};

