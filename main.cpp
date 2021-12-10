#include "mainwindow.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <queue>
#include "adjlist.h"
#include"adjmatrix.h"
using namespace std;
typedef map<string, string> Couples;
#include <QApplication>
string PATH = "dataset/names.csv";

Couples Matchmaking2(){

    // ====TEST-SPECIFIC CONSTANTS==== //

    int POOLSIZE = 100000;
        AdjMatrix matrix(PATH, POOLSIZE);
        map<string, string> matches = matrix.GenerateMatches();
        return matches;
}

Couples Matchmaking(){
    // creating the men's preferences graph and a list of bachelors
       AdjList bipartiteG;
       bipartiteG.loadData(PATH);

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
       // prints out the couples who are not in their desired engagement
       bipartiteG.stability(engaged);
       return engaged;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


}
