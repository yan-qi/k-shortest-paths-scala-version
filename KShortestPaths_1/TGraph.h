///////////////////////////////////////////////////////////////////////////////
///  TGraph.h
///  <TODO: insert file description here>
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 5/29/2010
/// 
/// $Id$
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
	std::map<int, double> m_mpEdgeCodeWeight; 
	//std::set<T> m_stVertices;
	std::map<T, GVertex<T>*> m_mpVertexIndex;
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

		m_mpEdgeCodeWeight.clear();

		/*m_stVertices.clear();*/
		m_mpVertexIndex.clear();

		//clear the list of vertices objects
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

	double get_edge_weight(const GVertex<T>* start_vertex_pt, const GVertex<T>* end_vertex_pt) const
	{
		std::map<int, double>::const_iterator pos = 
			m_mpEdgeWeight.find(get_edge_code(start_vertex_pt, end_vertex_pt));
		
		if (pos != m_mpEdgeWeight.end())
		{
			return pos->second;
		}

		return DISCONNECT;
	}

	GVertex<T>* get_vertex(int id) const
	{
		return m_vtVertices.at(id);
	}

	GVertex<T>* get_vertex(T node_)
	{
		GVertex<T>* vertex_pt = NULL;
		const std::map<T, GVertex<T>*>::iterator pos = m_mpVertexIndex.find(node_);
		if (pos == m_mpVertexIndex.end())
		{
			int vertex_id = m_vtVertices.size();
			vertex_pt = new GVertex<T>(node_);
			vertex_pt->setID(vertex_id);
			m_vtVertices.push_back(vertex_pt);
			m_mpVertexIndex.insert(make_pair(node_, vertex_pt));
		}else
		{
			vertex_pt = m_vtVertices.at(pos->second->getID());
		}

		return vertex_pt;
	}

    const std::set<GVertex<T>*>& get_precedent_vertex_set(GVertex<T>* vertex) const
	{
		return get_vertex_set(vertex, m_mpFaninVertices);
	}

	const std::set<GVertex<T>*>& get_adjacent_vertex_set(GVertex<T>* vertex) const
	{
		return get_vertex_set(vertex, m_mpFanoutVertices);
	}

	std::set<GVertex<T>*>& get_vertex_set(GVertex<T>* vertex_, 
		std::map<GVertex<T>*, std::set<GVertex<T>*> > vertex_container_index)
	{
		std::map<GVertex<T>*, std::set<GVertex<T>*> >::iterator pos = 
			vertex_container_index.find(vertex_);

		if(pos == vertex_container_index.end())
		{
			std::set<GVertex<T>*> vertex_set;
			pair<std::map<GVertex<T>*, std::set<GVertex<T>*> >::iterator,bool> ins_pos = 
				vertex_container_index.insert(make_pair(vertex_, vertex_set));

			pos = ins_pos.first;
		}
	
		return pos->second;
	}

};
