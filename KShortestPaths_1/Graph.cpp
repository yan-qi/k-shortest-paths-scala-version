/************************************************************************/
/* $Id           
/************************************************************************/
#include <limits>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "GraphElements.h"
#include "Graph.h"

using namespace std;

const double Graph::DISCONNECT = (numeric_limits<double>::max)();

Graph::Graph(const string& file_name)
{
}

Graph::~Graph(void)
{
}

void Graph::clear()
{
	m_nEdgeNum = 0;
	m_nVertexNum = 0;
	m_mpFanoutVertices.clear();
	m_mpFaninVertices.clear();
	m_mpEdgeWeight.clear();
	
	//clear the list
	for_each(m_vtVertices.begin(), m_vtVertices.end(), DeleteFunc<GVertex>());
	m_vtVertices.clear();
}

void Graph::import_from_file( const string& input_file_name )
{
	const char* file_name = input_file_name.c_str();

	//1. Check the validity of the file
	ifstream ifs(file_name);
	if (!ifs)
	{
		cerr << "The file " << file_name << " can not be opened!" << endl;
		exit(1);
	}

	//2. Reset the members of the class
	clear();

	//3. Start to read information from the input file. 
	/// Note the format of the data in the graph file.
	//3.1 The first line has an integer as the number of vertices of the graph
	ifs >> m_nVertexNum;

	//3.2 In the following lines, each line contains a directed edge in the graph:
	///   the id of starting point, the id of ending point, the weight of the edge. 
	///   These values are separated by 'white space'. 
	int start_vertex_id, end_vertex_id;
	double edge_weight;

	while(ifs >> start_vertex_id)
	{
		if (start_vertex_id == -1)
		{
			break;
		}
		ifs >> end_vertex_id;
		ifs >> edge_weight;

		///3.2.1 construct the vertices
		GVertex* start_vertex_pt = new GVertex(start_vertex_id);
		GVertex* end_vertex_pt = new GVertex(end_vertex_id);

		///3.2.2 add the edge weight
// 		int edge_code = get_edge_code(start_vertex_pt, end_vertex_pt);
// 		if(m_mpEdgeWeight.find(edge_code) != m_mpEdgeWeight.end())
// 		{
// 			++m_nEdgeNum;
// 		}
		//// note that the duplicate edge would overwrite the one occurring before. 
		m_mpEdgeWeight.insert(make_pair(get_edge_code(start_vertex_pt, end_vertex_pt), edge_weight));

		///3.2.3 update the fan-in or fan-out variables
		set<GVertex*> fan_in_set;
		
		
	}	

	m_nEdgeNum = m_mpEdgeWeight.size();

	ifs.close();	
}