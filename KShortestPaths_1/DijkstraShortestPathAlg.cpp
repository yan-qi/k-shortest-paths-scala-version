/************************************************************************/
/* $Id$                                                                 */
/************************************************************************/
#include <set>
#include <queue>
#include <map>

#include "GraphElements.h"
#include "DijkstraShortestPathAlg.h"

using namespace std;

DijkstraShortestPathAlg::~DijkstraShortestPathAlg(void)
{
}

void DijkstraShortestPathAlg::clear()
{
	m_stDeterminedVertices.clear();
	m_mpPredecessorVertex.clear();
	m_mpStartDistanceIndex.clear();
	while (!m_quCandidateVertices.empty())
	{
		m_quCandidateVertices.pop();
	}
}

void DijkstraShortestPathAlg::determine_shortest_paths( GVertex source, GVertex sink, bool is_source2sink )
{
	//1. clear the intermediate variables
	clear();

	//2. 
}