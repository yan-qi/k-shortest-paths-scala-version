/************************************************************************/
/* $Id           
/************************************************************************/
#include <limits>
#include <set>
#include <map>
#include <string>
#include <vector>
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
	m_vtVertices.clear();
	m_mpFanoutVertices.clear();
	m_mpFaninVertices.clear();
	m_mpEdgeWeight.clear();
}