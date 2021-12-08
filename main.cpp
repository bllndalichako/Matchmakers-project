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

typedef vector<string> DataSet;
typedef vector<string> PrefList;
typedef map<string, string> Couples;
typedef map<string, PrefList> PrefGraph;

// Does 'first' appear before 'second' in preference list?
bool prefers(const PrefList &prefer, const string &first, const string &second)
{
    for (const auto & it : prefer)
    {
        if (it == first) return true;
        if (it == second) return false;
    }
    return false; // no preference
}

void check_stability(const Couples &engaged, const PrefGraph &men_pref, const PrefGraph &women_pref)
{
    cout << "Stablility:\n";
    bool stable = true;
    for (auto it = engaged.begin(); it != engaged.end(); ++it)
    {
        const string &bride = it->first;
        const string &groom = it->second;
        const PrefList &preflist = men_pref.at(groom);

        for (PrefList::const_iterator it = preflist.begin(); it != preflist.end(); ++it)
        {
            if (*it == bride) // he prefers his bride
                break;
            if (prefers(preflist, *it, bride) && // he prefers another woman
                prefers(women_pref.at(*it), groom, engaged.at(*it))) // other woman prefers him
            {
                cout << "\t" << *it <<
                     " prefers " << groom <<
                     " over " << engaged.at(*it) <<
                     " and " << groom <<
                     " prefers " << *it <<
                     " over " << bride << "\n";
                stable = false;
            }
        }
    }
    if (stable) cout << "\t(all marriages stable)\n";
}

int main() {
    // variables to store the dataset by gender
    DataSet men;
    DataSet women;

    // opening the data file
    fstream names;
    names.open(R"(C:\Users\Beatrice Ndalichako\Documents\AdjList\names.csv)");

    // throwing an error if the data file could not be opened
    if (!names.is_open()) {
        throw runtime_error("Could not open the file");
    }

    // variables to store name and gender from the data file
    string name, gender;

    // reading names, gender from the data file
    while (!names.eof()) {
        // reading in name and gender
        getline(names, name, ',');
        getline(names, gender, '\n');

        // putting the name into the appropriate data set by gender
        if (gender != "F" && gender != "M") {
            throw runtime_error (name + "'s gender is not determined");
        }
        else if (gender == "M") {
            men.push_back(name);
        }
        // todo: implement equality in the size of the data set
        else if (gender == "F" && women.size() < men.size()){
            women.push_back(name);
        }
    }
    names.close();

    // creating the men's preferences graph and a list of bachelors
    PrefGraph menPref;
    queue<string> bachelors;
    for (const string& man: men) {
        // shuffling women to create a unique pref list for each man
        shuffle(women.begin(), women.end(), std::mt19937(std::random_device()()));
        menPref[man] = women;
        bachelors.push(man);
    }

    // creating women's preferences graph
    PrefGraph womenPref;
    for (const string& woman: women) {
        // shuffling men to create a unique pref list for each woman
        shuffle(men.begin(), men.end(), std::mt19937(std::random_device()()));
        womenPref[woman] = men;
    }

    // stores pairs in a couple
    Couples engaged;

    // matchmaking
    while (!bachelors.empty()) {
        string suitor = bachelors.front(); // male suitor
        PrefList preflist = menPref[suitor]; // male suitor's pref list

        // go through each bride in the pref list
        for (const auto & bride : preflist) {
            if (engaged.find(bride) == engaged.end()) { // she's available
                cout << bride << " and " << suitor << " are engaged!\nCongratulations are in order\n";
                engaged[bride] = suitor; // hook up
                break;
            }

            // if the bride is engaged, see if a switch is necessary
            const string &groom = engaged[bride];

            if (prefers(womenPref[bride], suitor, groom)) {
                cout << bride << " dumped " << groom << " for " << suitor << "\n";
                bachelors.push(groom); // dump that zero
                engaged[bride] = suitor; // get a hero
                break;
            }
        }
        bachelors.pop(); // pop at the end to not invalidate suitor reference
    }
    cout << "Engagements:\n";
    for (Couples::const_iterator it = engaged.begin(); it != engaged.end(); ++it)
    {
        cout << "\t" << it->first << " and " << it->second << "\n";
    }
    check_stability(engaged, menPref, womenPref);
    return 0;
}
