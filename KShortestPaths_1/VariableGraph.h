///////////////////////////////////////////////////////////////////////////////
///  VariableGraph.h
///  <TODO: insert file description here>
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 8/18/2010
/// 
///  $Id$
///////////////////////////////////////////////////////////////////////////////


#pragma once

using namespace std;

class Vertex : public BaseVertex
{
	int node_id; 

public:

	Vertex(int nID){ node_id = nID; }

	int get_node_id() const { return node_id; }
	void set_node_id(int val) { node_id = val; }

};

class Path : public BasePath
{
public: 

	Path(const std::vector<BaseVertex*>& vertex_list, double weight):BasePath(vertex_list,weight){}

	// display the content
	void PrintOut(std::ostream& out_stream) const
	{
		out_stream << "Cost: " << m_dWeight << " Length: " << m_vtVertexList.size() << std::endl;
		//std::copy(m_vtVertexList.begin(), m_vtVertexList.end(), std::ostream_iterator<int>(out_stream, " "));
		for(std::vector<BaseVertex*>::const_iterator pos=m_vtVertexList.begin(); pos!=m_vtVertexList.end();++pos)
		{
			out_stream << ((Vertex*)(*pos))->get_node_id() << " ";
		}
		out_stream << std::endl <<  "*********************************************" << std::endl;	
	}
};

class VariableGraph
{
public: // members

	const static double DISCONNECT; 

	typedef set<BaseVertex*>::iterator VertexPtSetIterator;
	typedef map<BaseVertex*, set<BaseVertex*>*>::iterator BaseVertexPt2SetMapIterator;

protected: // members

	// Basic information
	map<BaseVertex*, set<BaseVertex*>*> m_mpFanoutVertices;
	map<BaseVertex*, set<BaseVertex*>*> m_mpFaninVertices;
	map<int, double> m_mpEdgeCodeWeight; 
	vector<BaseVertex*> m_vtVertices;
	int m_nEdgeNum;
	int m_nVertexNum;

	map<int, BaseVertex*> m_mpVertexIndex;

	// Members for graph modification
	set<int> m_stRemovedVertexIds;
	set<pair<int,int> > m_stRemovedEdge;

public:

	// Constructors and Destructor
	VariableGraph(const string& file_name);
	VariableGraph(const VariableGraph& rGraph);
	~VariableGraph(void);

	void clear();

	BaseVertex* get_vertex(int node_id);
	BaseVertex* get_vertex_by_ID(int id) const;
	void get_vertex_list(vector<BaseVertex*>& vertex_list);

	int get_edge_code(const BaseVertex* start_vertex_pt, const BaseVertex* end_vertex_pt) const;
	set<BaseVertex*>* get_vertex_set_pt(BaseVertex* vertex_, map<BaseVertex*, set<BaseVertex*>*>& vertex_container_index);

	double get_edge_weight(const BaseVertex* source, const BaseVertex* sink);
	void get_adjacent_vertices(BaseVertex* vertex, set<BaseVertex*>& vertex_set);
	void get_precedent_vertices(BaseVertex* vertex, set<BaseVertex*>& vertex_set);

	/// Methods for changing graph
	void remove_edge(const pair<int,int> edge)
	{
		//m_stRemovedEdge.erase(m_stRemovedEdge.find(edge));
		m_stRemovedEdge.insert(edge);
	}

	void remove_vertex(const int vertex_id)
	{
		m_stRemovedVertexIds.insert(vertex_id);
	}

	void recover_removed_edges()
	{
		m_stRemovedEdge.clear();
	}

	void recover_removed_vertices()
	{
		m_stRemovedVertexIds.clear();
	}

	void recover_removed_edge(const pair<int,int> edge)
	{
		m_stRemovedEdge.erase(m_stRemovedEdge.find(edge));
	}

	void recover_removed_vertex(int vertex_id)
	{
		m_stRemovedVertexIds.erase(m_stRemovedVertexIds.find(vertex_id));
	}
	
private:
	void _import_from_file(const std::string& file_name);

};
