///////////////////////////////////////////////////////////////////////////////
///  Graph.h
///  <TODO: insert file description here>
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 5/29/2010
/// 
/// $Id$
///////////////////////////////////////////////////////////////////////////////
#pragma once

/*typedef GVertex<int> GIntVertex;*/

class Vertex : public BaseVertex
{
	int node_id; 
	
public:
	int get_node_id() const { return node_id; }
	void set_node_id(int val) { node_id = val; }

};

class Path : public BasePath
{
public: 
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


/*class Graph : public TGraph<int>*/
class Graph : public BaseGraph
{
public: // members

	map<int, BaseVertex*> m_mpVertexIndex;


public: // methods
	
	Graph(const std::string& file_name);
	~Graph(void){ m_mpVertexIndex.clear(); }

	void import_from_file(const std::string& file_name);

	BaseVertex* get_vertex(int node_id);	
};
