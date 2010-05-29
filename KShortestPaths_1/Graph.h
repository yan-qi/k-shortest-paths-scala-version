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

typedef GVertex<int> GIntVertex;

class Graph : public TGraph<int>
{
	
public: // methods
	
	Graph(const std::string& file_name);
	~Graph(void){}

	void import_from_file(const std::string& file_name);
};
