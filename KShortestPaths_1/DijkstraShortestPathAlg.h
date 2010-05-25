/************************************************************************/
/* $Id$                                                                 */
/************************************************************************/

#pragma once

class DijkstraShortestPathAlg
{
	const GDirectGraph& m_rDirectGraph;

	std::set<GVertex> m_stDeterminedVertices; 
	std::priority_queue<GVertex> m_quCandidateVertices;
	std::map<GVertex,double> m_mpStartDistanceIndex; 
	std::map<GVertex,GVertex> m_mpPredecessorVertex; 
			

public:
	DijkstraShortestPathAlg(const GDirectGraph& pGraph):m_rDirectGraph(pGraph){}
	~DijkstraShortestPathAlg(void);

	void clear();

protected:

	void determine_shortest_paths(GVertex source, GVertex sink, bool is_source2sink);

};
