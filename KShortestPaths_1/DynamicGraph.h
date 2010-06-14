///////////////////////////////////////////////////////////////////////////////
///  VariableGraph.h
///  Depict a graph that can change dynamically!
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 6/13/2010
///
///  $Id$
///
///////////////////////////////////////////////////////////////////////////////

#pragma once

using namespace std;

class DynamicGraph : public BaseGraph
{
	set<int> m_stRemovedVertexIds;
	set<pair<int,int> > m_stRemovedEdge;

public:
	DynamicGraph(void);
	~DynamicGraph(void);
};
