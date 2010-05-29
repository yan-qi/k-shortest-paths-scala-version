/************************************************************************/
/* $Id$                                                                 */
/************************************************************************/

#pragma once

class DijkstraShortestPathAlg
{
	const Graph& m_rDirectGraph;

	std::set<GIntVertex*, WeightComparator4GVertex<int> > m_stDeterminedVertices; // The set of vertex IDs
	std::priority_queue<GIntVertex*, std::vector<GIntVertex*>, WeightComparator4GVertex<int> > m_quCandidateVertices;
	std::map<GIntVertex*,double> m_mpStartDistanceIndex; 
	std::map<GIntVertex*,GIntVertex*> m_mpPredecessorVertex; 
			

public:
	DijkstraShortestPathAlg(const Graph& pGraph):m_rDirectGraph(pGraph){}
	~DijkstraShortestPathAlg(void);

	void clear();

protected:

	void determine_shortest_paths(GIntVertex& source, GIntVertex& sink, bool is_source2sink);
	void improve2vertex(GIntVertex& cur_vertex, bool is_source2sink);
};
