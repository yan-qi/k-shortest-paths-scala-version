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
	//std::map<std::pair<GVertex*,GVertex*>, double> m_mpEdgeWeight; 
	std::map<int, double> m_mpEdgeWeight; 
	std::vector<GVertex*> m_vtVertices;
	int m_nEdgeNum;
	int m_nVertexNum;

	
public: // methods
	
	Graph(const std::string& file_name);
	~Graph(void);

	void clear();
	void import_from_file(const std::string& file_name);

protected: // methods

	int get_edge_code(const GVertex* start_vertex_pt, const GVertex* end_vertex_pt) const
	{
		/// Note that the computation below works only if 
		/// the result is smaller than the maximum of an integer!
		return start_vertex_pt->getID()*m_nVertexNum+end_vertex_pt->getID();
	}
};
