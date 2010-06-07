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

class DijkstraShortestPathAlg
{
public: // types

	//typedef GVertex<T> BaseVertex;

private: // members

	BaseGraph& m_rDirectGraph;

	std::map<BaseVertex*, double> m_mpStartDistanceIndex; 
	std::map<BaseVertex*, BaseVertex*> m_mpPredecessorVertex; 

	std::set<BaseVertex*, WeightComparator<BaseVertex> > m_stDeterminedVertices; // The set of vertex IDs
	
	std::priority_queue<BaseVertex*, std::vector<BaseVertex*>, WeightComparator<BaseVertex> > m_quCandidateVertices;
	
public:
	DijkstraShortestPathAlg(BaseVertex& pGraph):m_rDirectGraph(pGraph){}
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

	BasePath get_shortest_path(BaseVertex* source, BaseVertex* sink)
	{
		determine_shortest_paths(source, sink, true);

		std::vector<BaseVertex*> vertex_list;
		std::map<BaseVertex*, double>::const_iterator pos = 
			m_mpStartDistanceIndex.find(sink);
		double weight = pos != m_mpStartDistanceIndex.end() ? pos->second : TGraph<T>::DISCONNECT;

		if (weight < TGraph<T>::DISCONNECT)
		{
			BaseVertex* cur_vertex_pt = sink;
			do 
			{
				vertex_list.insert(vertex_list.begin(), cur_vertex_pt);
				
				std::map<BaseVertex*, BaseVertex*>::const_iterator pre_pos = 
					m_mpPredecessorVertex.find(cur_vertex_pt);

				if (pre_pos == m_mpPredecessorVertex.end()) break;
				
				cur_vertex_pt = pre_pos->second;

			} while (cur_vertex_pt != source);

			/*vertex_list.push_back(source);*/
			vertex_list.insert(vertex_list.begin(), source);
		}
		return BasePath(vertex_list, weight);
	}

protected:

	void determine_shortest_paths(BaseVertex* source, BaseVertex* sink, bool is_source2sink)
	{
		//1. clear the intermediate variables
		clear();

		//2. initiate the local variables
		BaseVertex* end_vertex = is_source2sink ? sink : source;
		BaseVertex* start_vertex = is_source2sink ? source : sink;
		m_mpStartDistanceIndex.insert(make_pair(start_vertex, 0));
		start_vertex->Weight(0);
		m_quCandidateVertices.push(start_vertex);

		//3. start searching for the shortest path
		while (!m_quCandidateVertices.empty())
		{
			BaseVertex* cur_vertex_pt = m_quCandidateVertices.top();
			m_quCandidateVertices.pop();

			if (cur_vertex_pt->getID() == end_vertex->getID()) break;

			m_stDeterminedVertices.insert(cur_vertex_pt);

			improve2vertex(cur_vertex_pt, is_source2sink);
		}
	}

	void improve2vertex(BaseVertex* cur_vertex_pt, bool is_source2sink)
	{
		// 1. get the neighboring vertices 
		set<BaseVertex*>* neighbor_vertex_list_pt = is_source2sink ? 
			m_rDirectGraph.get_adjacent_vertex_set(cur_vertex_pt) : 
			m_rDirectGraph.get_precedent_vertex_set(cur_vertex_pt);

		// 2. update the distance passing on the current vertex
		for(set<BaseVertex*>::iterator cur_neighbor_pos=neighbor_vertex_list_pt->begin(); 
			cur_neighbor_pos!=neighbor_vertex_list_pt->end(); ++cur_neighbor_pos)
		{
			//2.1 skip if it has been visited before
			if (m_stDeterminedVertices.find(*cur_neighbor_pos)!=m_stDeterminedVertices.end())
			{
				continue;
			}

			//2.2 calculate the distance
			map<BaseVertex*, double>::const_iterator cur_pos = m_mpStartDistanceIndex.find(cur_vertex_pt);
			double distance =  cur_pos != m_mpStartDistanceIndex.end() ? cur_pos->second : TGraph<T>::DISCONNECT;

			distance += is_source2sink ? m_rDirectGraph.get_edge_weight(cur_vertex_pt, *cur_neighbor_pos) : 
				m_rDirectGraph.get_edge_weight(*cur_neighbor_pos, cur_vertex_pt);

			//2.3 update the distance if necessary
			cur_pos = m_mpStartDistanceIndex.find(*cur_neighbor_pos);
			if (cur_pos == m_mpStartDistanceIndex.end() || cur_pos->second > distance)
			{
				m_mpStartDistanceIndex.insert(make_pair(*cur_neighbor_pos, distance));
				m_mpPredecessorVertex.insert(make_pair(*cur_neighbor_pos, cur_vertex_pt));
				(*cur_neighbor_pos)->Weight(distance);
				m_quCandidateVertices.push(*cur_neighbor_pos);
			}
		}
	}

};
