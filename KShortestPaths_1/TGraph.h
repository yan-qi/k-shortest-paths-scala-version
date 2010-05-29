///////////////////////////////////////////////////////////////////////////////
///  TGraph.h
///  <TODO: insert file description here>
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 5/29/2010
/// 
/// $Id
///////////////////////////////////////////////////////////////////////////////
#pragma once

template<typename T>
class TGraph
{
public: // members

	const static double DISCONNECT; 

protected: // members

	std::map<GVertex<T>*, std::set<GVertex<T>*> > m_mpFanoutVertices;
	std::map<GVertex<T>*, std::set<GVertex<T>*> > m_mpFaninVertices;
	std::map<int, double> m_mpEdgeWeight; 
	std::set<T> m_stVertices;
	std::vector<GVertex<T>*> m_vtVertices;
	int m_nEdgeNum;
	int m_nVertexNum;


public: // methods

	virtual ~TGraph(void){clear();}

	void clear()
	{
		m_nEdgeNum = 0;
		m_nVertexNum = 0;
		m_mpFanoutVertices.clear();
		m_mpFaninVertices.clear();
		m_mpEdgeWeight.clear();
		m_stVertices.clear();
		//clear the list
		for_each(m_vtVertices.begin(), m_vtVertices.end(), DeleteFunc<GIntVertex>());
		m_vtVertices.clear();
	}
	
protected: // methods

	int get_edge_code(const GVertex<T>* start_vertex_pt, const GVertex<T>* end_vertex_pt) const
	{
		/// Note that the computation below works only if 
		/// the result is smaller than the maximum of an integer!
		return start_vertex_pt->getID()*m_nVertexNum+end_vertex_pt->getID();
	}
};
