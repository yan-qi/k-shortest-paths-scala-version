///////////////////////////////////////////////////////////////////////////////
///  Graph.cpp
///  <TODO: insert file description here>
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 5/29/2010
/// 
///  $Id$
///////////////////////////////////////////////////////////////////////////////


#include <limits>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "GraphElements.h"
#include "BasePath.h"
#include "BaseGraph.h"
#include "VariableGraph.h"
#include "Graph.h"

using namespace std;

Graph::Graph(const string& file_name)
{
	import_from_file(file_name);
}


///////////////////////////////////////////////////////////////////////////////
///  public  import_from_file
///  Construct the graph by importing the edges from the input file. 
///
///  @param [in]       file_name const std::string &    The input graph file
///
///  This function doesn't return a value
///
///  @remarks The format of the file is as follows:
///   1. The first line has an integer as the number of vertices of the graph
///   2. Each line afterwards contains a directed edge in the graph:
///		     starting point, ending point and the weight of the edge. 
///		 These values are separated by 'white space'.
///
///  @see <TODO: insert text here>
///
///  @author Yan Qi @date 5/29/2010
///////////////////////////////////////////////////////////////////////////////
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
	int start_vertex, end_vertex;
	double edge_weight;
	int vertex_id = 0;

	while(ifs >> start_vertex)
	{
		if (start_vertex == -1)
		{
			break;
		}
		ifs >> end_vertex;
		ifs >> edge_weight;

		///3.2.1 construct the vertices
		/*GIntVertex* start_vertex_pt = new GIntVertex(start_vertex);*/
		BaseVertex* start_vertex_pt = get_vertex(start_vertex);
		BaseVertex* end_vertex_pt = get_vertex(end_vertex);

		///3.2.2 add the edge weight
		//// note that the duplicate edge would overwrite the one occurring before. 
		m_mpEdgeCodeWeight.insert(make_pair(get_edge_code(start_vertex_pt, end_vertex_pt), edge_weight));

		///3.2.3 update the fan-in or fan-out variables
		//// Fan-in
		get_vertex_set_pt(end_vertex_pt, m_mpFaninVertices)->insert(start_vertex_pt);

		//// Fan-out
		get_vertex_set_pt(start_vertex_pt, m_mpFanoutVertices)->insert(end_vertex_pt);
		
	}	
	
	m_nVertexNum = m_vtVertices.size();
	m_nEdgeNum = m_mpEdgeCodeWeight.size();

	ifs.close();	
}

BaseVertex* Graph::get_vertex( int node_id )
{
	BaseVertex* vertex_pt = NULL;
	const map<int, BaseVertex*>::iterator pos = m_mpVertexIndex.find(node_id);
	if (pos == m_mpVertexIndex.end())
	{
		int vertex_id = m_vtVertices.size();
		vertex_pt = new Vertex(node_id);
		vertex_pt->setID(vertex_id);
		m_vtVertices.push_back(vertex_pt);
		m_mpVertexIndex.insert(make_pair(node_id, vertex_pt));
	}else
	{
		vertex_pt = m_vtVertices.at(pos->second->getID());
	}

	return vertex_pt;
}