///////////////////////////////////////////////////////////////////////////////
///  DijkstraShortestPathAlg.h
///  The implementation of Dijkstra algorithm to get the shortest path of 
///  a pair of vertices in a graph. 
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 5/30/2010
/// 
///  $Id$
///
///////////////////////////////////////////////////////////////////////////////

#pragma once

using namespace std;

template<typename T>
class DijkstraShortestPathAlg
{
public: // types

	typedef GVertex<T> TVertex;

private: // members

	TGraph<T>& m_rDirectGraph;

	std::map<TVertex*, double> m_mpStartDistanceIndex; 
	std::map<TVertex*, TVertex*> m_mpPredecessorVertex; 

	std::set<TVertex*, WeightComparator<TVertex> > m_stDeterminedVertices; // The set of vertex IDs
	
	std::priority_queue<GVertex<T>*, std::vector<GVertex<T>*>, WeightComparator<GVertex<T> > > m_quCandidateVertices;
	
public:
	DijkstraShortestPathAlg(TGraph<T>& pGraph):m_rDirectGraph(pGraph){}
	~DijkstraShortestPathAlg(void){clear();}

	void clear()
	{
		m_stDeterminedVertices.clear();
		m_mpPredecessorVertex.clear();
		m_mpStartDistanceIndex.clear();
		while (!m_quCandidateVertices.empty())
		{
			m_quCandidateVertices.pop();
		}
	}

	TPath<T> get_shortest_path(TVertex* source, TVertex* sink)
	{
		determine_shortest_paths(source, sink, true);
		std::vector<TVertex*> vertex_list;
		std::map<TVertex*, double>::const_iterator pos = 
			m_mpStartDistanceIndex.find(sink);
		double weight = pos != m_mpStartDistanceIndex.end() ? pos->second : TGraph<T>::DISCONNECT;

		if (weight < TGraph<T>::DISCONNECT)
		{
			TVertex* cur_vertex_pt = sink;
			do 
			{
				vertex_list.insert(vertex_list.begin(), cur_vertex_pt->_node((()(((.m_mpStartDistanceIndex.))))));
				
				std::map<TVertex*, TVertex*>::const_iterator pre_pos = 
					m_mpPredecessorVertex.find(cur_vertex_pt);

				if (pre_pos == m_mpPredecessorVertex.end()) break;
				
				cur_vertex_pt = pre_pos->second;

			} while (cur_vertex_pt != source);

			/*vertex_list.push_back(source);*/
			vertex_list.insert(vertex_list.begin(), source);
		}
		return TPath<T>(vertex_list, weight);
	}

protected:

	void determine_shortest_paths(TVertex* source, TVertex* sink, bool is_source2sink)
	{
		//1. clear the intermediate variables
		clear();

		//2. initiate the local variables
		TVertex* start_vertex = is_source2sink ? sink : source;
		TVertex* end_vertex = is_source2sink ? source : sink;
		m_mpStartDistanceIndex.insert(make_pair(start_vertex, 0));
		start_vertex->Weight(0);
		m_quCandidateVertices.push(start_vertex);

		//3. start searching for the shortest path
		while (!m_quCandidateVertices.empty())
		{
			TVertex* cur_vertex_pt = m_quCandidateVertices.top();
			m_quCandidateVertices.pop();

			if (cur_vertex_pt->getID() == end_vertex->getID()) break;

			m_stDeterminedVertices.insert(cur_vertex_pt);

			improve2vertex(cur_vertex_pt, is_source2sink);
		}
	}

	void improve2vertex(TVertex* cur_vertex_pt, bool is_source2sink)
	{
		// 1. get the neighboring vertices 
		set<TVertex*> neighbor_vertex_list = is_source2sink ? 
			m_rDirectGraph.get_adjacent_vertex_set(cur_vertex_pt) : 
			m_rDirectGraph.get_precedent_vertex_set(cur_vertex_pt);

		// 2. update teh distance passing on the current vertex
		for(set<TVertex*>::iterator cur_neighbor_pos=neighbor_vertex_list.begin(); 
			cur_neighbor_pos!=neighbor_vertex_list.end(); ++cur_neighbor_pos)
		{
			//2.1 skip if it has been visited before
			if (m_stDeterminedVertices.find(*cur_neighbor_pos)!=m_stDeterminedVertices.end())
			{
				continue;
			}

			//2.2 calculate the distance
			map<TVertex*, double>::const_iterator cur_pos = m_mpStartDistanceIndex.find(cur_vertex_pt);
			double distance =  cur_pos != m_mpStartDistanceIndex.end() ? cur_pos->second : TGraph<T>::DISCONNECT;

			distance += is_source2sink ? m_rDirectGraph.get_edge_weight(cur_vertex_pt, *cur_neighbor_pos) : 
				m_rDirectGraph.get_edge_weight(*cur_neighbor_pos, cur_vertex_pt);

			//2.3 update the distance if necessary
			cur_pos = m_mpStartDistanceIndex.find(*cur_neighbor_pos);
			if (cur_pos == m_mpStartDistanceIndex.end() || cur_pos->second > distance)
			{
				m_mpStartDistanceIndex.insert(make_pair(cur_pos->first, distance));
				m_mpPredecessorVertex.insert(make_pair(cur_pos->first, cur_vertex_pt));
				(*cur_neighbor_pos)->Weight(distance);
				m_quCandidateVertices.push(*cur_neighbor_pos);
			}
		}
	}

};
