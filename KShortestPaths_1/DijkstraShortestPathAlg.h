#pragma once

#include <set>
#include <queue>
#include <map>

#include "GraphElements.h"

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
};
