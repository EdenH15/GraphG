// Email:Edenhassin@gmail.com

#include <iostream>
#include "Graph.h"
#include "Algorithms.h"
#include "structures.h"
using namespace graph;
using namespace std;


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    Graph g(6);

    g.addEdge(0,1,4);
    g.addEdge(0,2,3);
    g.addEdge(1,3,2);
    g.addEdge(1,4,7);
    g.addEdge(2,4,1);
    g.addEdge(3,5,5);
    g.addEdge(4,5,2);

    cout << "original graph:\n" << endl;
    g.print_graph();


    Graph bfsTree= Algorithms::bfs(g,0);
    cout << "after bfs\n" << endl;
    bfsTree.print_graph();

    Graph dfsTree= Algorithms::dfs(g,0);
    cout << "after dfs\n" << endl;
    dfsTree.print_graph();

    Graph dTree=Algorithms::dijkstra(g,0);
    cout << "after dijkstra:\n" << endl;
    dTree.print_graph();

    Graph prim=Algorithms::prim(g);
    cout << "after prim:\n" << endl;
    prim.print_graph();

    Graph kruskalTree=Algorithms::kruskal(g);
    cout << "after kruskal:\n" << endl;
    kruskalTree.print_graph();


    return 0;


}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.