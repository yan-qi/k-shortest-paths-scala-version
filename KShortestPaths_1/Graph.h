/************************************************************************/
/* $Id
/************************************************************************/
#pragma once

class Graph
{
public: // members

	const static double DISCONNECT; 

protected: // members

	std::map<GVertex*, std::set<GVertex*> > m_mpFanoutVertices;
	std::map<GVertex*, std::set<GVertex*> > m_mpFaninVertices;
	std::map<std::pair<GVertex*,GVertex*>, double> m_mpEdgeWeight; 
	std::vector<GVertex> m_vtVertices;
	int m_nEdgeNum;
	int m_nVertexNum;

	
public:
	Graph(const std::string& file_name);
	~Graph(void);

	void clear();
};
