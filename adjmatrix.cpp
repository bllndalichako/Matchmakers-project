#include "adjmatrix.h"

// Constructor
AdjMatrix::AdjMatrix(string& fname, int N)
{
    poolsize = N;
    // Initialize values of rankingset
    for (int i = 0; i < N; i++)
        rankingset.push_back(i);
    // Initialize two N x N arrays for adjacency matrices
    womensPrefGraph.resize(N);
    mensPrefGraph.resize(N);
    loadData(fname, N);
    setPreferences();
}
// Setting name dictionaries
void AdjMatrix::loadData(string& fname, int N)
{
    // opening the data file
    fstream names;
    names.open(fname);
    // throwing an error if the data file could not be opened
    if (!names.is_open()) {
        throw runtime_error("Could not open the file");
    }
    // variables to store name and gender from the data file
    string name;
    string gender;
    // reading names, gender from the data file
    while (!names.eof()) {
        // reading in name and gender
        getline(names, name, ',');
        getline(names, gender, '\n');
        // putting the name into the appropriate data set by gender
        if (gender != "F" && gender != "M") {
            throw runtime_error(name + "'s gender is not determined");
        }
        else if (gender == "M" && men.size() < N) {
            men.push_back(name);
        }
        else if (gender == "F" && women.size() < N) {
            women.push_back(name);
        }
    }
    names.close();
}
// Assigning shuffled rankingset (of ints) to each man/woman
void AdjMatrix::setPreferences()
{
    // Set prefs of women
    for (int w = 0; w < poolsize; w++)
    {
        shuffle(rankingset.begin(), rankingset.end(), std::mt19937(std::random_device()()));
        womensPrefGraph[w] = rankingset;
    }
    // Set prefs of men
    for (int m = 0; m < poolsize; m++)
    {
        shuffle(rankingset.begin(), rankingset.end(), std::mt19937(std::random_device()()));
        mensPrefGraph[m] = rankingset;
    }
}
// Adjacency Matrix Gale-Shapley Algorithm
// Creates and returns matches
map<string,string>& AdjMatrix::GenerateMatches()
{
    vector<int> womanspartner(poolsize, -1);
    vector<bool> mansfreedom (poolsize, true);
    int freemen = poolsize;
    while (freemen > 0)
    {
        int m;
        for (m = 0; m < poolsize; m++)
            if (mansfreedom[m]) break;
        for (int i = 0; i < poolsize && mansfreedom[m]; i++)
        {
            int w = mensPrefGraph[m][i];
            if (womanspartner[w] == -1)
            {
                womanspartner[w] = m;
                mansfreedom[m] = false;
                freemen--;
            }
            else
            {
                int m2 = womanspartner[w];
                if (WomanPrefersMOverM2(w, m, m2))
                {
                    womanspartner[w] = m;
                    mansfreedom[m] = false;
                    mansfreedom[m2] = true;
                }
            }
        }
    }

    // Store matches into map<string, string> matches
    for (int i = 0; i < womanspartner.size(); i++)
    {
        string wname = women[i];
        int mindex = womanspartner[i];
        string mname = men[mindex];
        matches[wname] = mname;
    }
    return matches;
}
bool AdjMatrix::WomanPrefersMOverM2(int w, int m, int m2) const
{
    return womensPrefGraph[w][m] < womensPrefGraph[w][m2];
}
