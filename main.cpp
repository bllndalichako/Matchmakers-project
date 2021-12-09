#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <queue>
#include "AdjList.h"
using namespace std;
typedef map<string, string> Couples;

int main() {
    // creating the men's preferences graph and a list of bachelors
    AdjList bipartiteG;
    bipartiteG.loadData(R"(C:\Users\Beatrice Ndalichako\Documents\AdjList\names.csv)");

    // setting preferences and creating the list of bachelors
    queue<string> bachelors;
    bipartiteG.setPreferences(bachelors);

    // stores pairs in a couple
    Couples engaged;

    // start matchmaking
    bipartiteG.matchCouples(bachelors, engaged);

    // printing engagements
    for (Couples::const_iterator it = engaged.begin(); it != engaged.end(); ++it)
    {
        cout << it->first << " and " << it->second << "\n";
    }
    cout << "\n";
    // prints out the couples who are not in their desired engagement
    bipartiteG.stability(engaged);
    return 0;
}