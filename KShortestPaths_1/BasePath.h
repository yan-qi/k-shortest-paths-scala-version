///////////////////////////////////////////////////////////////////////////////
///  BasePath.h
///  <TODO: insert file description here>
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 6/6/2010
///
///  $Id$
///
///////////////////////////////////////////////////////////////////////////////

#pragma once

class BasePath
{
	int m_nLength; 
	double m_dWeight;
	std::vector<BaseVertex*> m_vtVertexList;

public:
	BasePath(const std::vector<BaseVertex*> vertex_list, double weight):m_dWeight(weight)
	{
		m_vtVertexList.assign(vertex_list.begin(), vertex_list.end());
		m_nLength = m_vtVertexList.size();
	};
	~BasePath(void){}

	double Weight() const { return m_dWeight; }
	void Weight(double val) { m_dWeight = val; }

	// display the content
// 	void PrintOut(std::ostream& out_stream) const
// 	{
// 		out_stream << "Cost: " << m_dWeight << " Length: " << m_vtVertexList.size() << std::endl;
// 		//std::copy(m_vtVertexList.begin(), m_vtVertexList.end(), std::ostream_iterator<int>(out_stream, " "));
// 		for(std::vector<BaseVertex*>::const_iterator pos=m_vtVertexList.begin(); pos!=m_vtVertexList.end();++pos)
// 		{
// 			out_stream << (*pos)->getNode() << " ";
// 		}
// 		out_stream << std::endl <<  "*********************************************" << std::endl;	
// 	}
};