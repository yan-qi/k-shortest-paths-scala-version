/************************************************************************/
/* $Id$                                                                 */
/************************************************************************/
#pragma once

class GVertex
{
	static int ID; 

private:
	int m_nID;
	double m_dWeight;	
	
public:
	GVertex(){ m_nID = ID++; }
	GVertex(int ID_){ m_nID = ID_; }
	int getID() const { return m_nID; }


	double Weight() const { return m_dWeight; }
	void Weight(double val) { m_dWeight = val; }
};

class Comparator4GVertex
{
public:
	// Determine priority.
	bool operator()(const GVertex& a, const GVertex& b) const
	{
		return a.Weight() < b.Weight();
	}

	bool operator()(const GVertex* a, const GVertex* b) const
	{
		return a->Weight() < b->Weight();
	}
};

// Determine priority.
// bool operator<(const GVertex& a, const GVertex& b)
// {
// 	return a.Weight() < b.Weight();
// }
// 
// bool operator<(const GVertex* a, const GVertex* b)
// {
// 	return a->Weight() < b->Weight();
// }

class GEdge
{
private:

	int m_nStartVertexID;
	int m_nEndVertexID;
	double m_dWeight;

public:
	
	// Getter & Setter

};

//////////////////////////////////////////////////////////////////////////
// A class for the object deletion
//////////////////////////////////////////////////////////////////////////
template<class T>
class DeleteFunc
{
public:
	void operator()(const T* it) const
	{
		delete it;
	}
};
