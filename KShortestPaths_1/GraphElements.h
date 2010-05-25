/************************************************************************/
/* $Id$                                                                 */
/************************************************************************/
#pragma once

class GVertex
{
	const static int ID; 

private:
	int m_nID;
	double m_dWeight;	
	
public:
	double Weight() const { return m_dWeight; }
	void Weight(double val) { m_dWeight = val; }
};

// Determine priority.
bool operator<(const GVertex& a, const GVertex& b)
{
	return a.Weight() < b.Weight();
}

class GEdge
{
private:

	int m_nStartVertexID;
	int m_nEndVertexID;
	double m_dWeight;

public:
	
	// Getter & Setter

};

class GDirectGraph
{

};