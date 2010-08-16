/************************************************************************/
/* $Id$                                                                 */
/************************************************************************/

#include <limits>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "GraphElements.h"
#include "BasePath.h"
#include "BaseGraph.h"
#include "Graph.h"
#include "DynamicGraph.h"
#include "DijkstraShortestPathAlg.h"
#include "YenTopKShortestPathsAlg.h"

using namespace std;


void testDijkstraGraph()
{
	BaseGraph* my_graph_pt = new Graph("data/test_2");
	DijkstraShortestPathAlg shortest_path_alg(my_graph_pt);
	BasePath* result = 
		shortest_path_alg.get_shortest_path(
			my_graph_pt->get_vertex_by_ID(0), my_graph_pt->get_vertex_by_ID(2));
	result->PrintOut(cout);
}

void testYenAlg()
{
	Graph my_graph("data/test_6_2");
	
	YenTopKShortestPathsAlg yenAlg(my_graph, my_graph.get_vertex_by_ID(4), 
		my_graph.get_vertex_by_ID(5));

	int i=0;
	while(yenAlg.has_next())
	{
		++i;
		yenAlg.next()->PrintOut(cout);
		//System.out.println("Path "+i+++" : "+yenAlg.next());
	}

// 	System.out.println("Result # :"+i);
// 	System.out.println("Candidate # :"+yenAlg.get_cadidate_size());
// 	System.out.println("All generated : "+yenAlg.get_generated_path_size());

}

int main(...)
{
	cout << "Welcome to the real world!" << endl;

	/*testDijkstraGraph();*/
	testYenAlg();
}
