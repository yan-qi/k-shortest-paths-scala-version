///////////////////////////////////////////////////////////////////////////////
///  GraphElements.h
///  <TODO: insert file description here>
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 5/28/2010
///
///  $Id$
///////////////////////////////////////////////////////////////////////////////

#pragma once


///////////////////////////////////////////////////////////////////////////////
///  GVertex
///  The class for the graph nodes
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 5/28/2010
///////////////////////////////////////////////////////////////////////////////
template<class T>
class GVertex
{
	int m_nID;
	double m_dWeight;	
	T _node; /* Note that the type of node may need to be modified for the improvement upon the performance. */

public:

	//typedef GVertex<T> TYPE;

	GVertex(T node):_node(node){}

	int getID() const { return m_nID; }
	void setID(int ID_) { m_nID = ID_; }

	double Weight() const { return m_dWeight; }
	void Weight(double val) { m_dWeight = val; }

	T getNode() const {return _node;}
};

///////////////////////////////////////////////////////////////////////////////
///  WeightComparator4GVertex
///		The comparator is for the comparison of vertices of the graph, 
///     in terms of their weights. 
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 5/28/2010
///////////////////////////////////////////////////////////////////////////////
template<class T>
class WeightComparator4GVertex
{
public:
	// Determine priority.
	bool operator()(const GVertex<T>& a, const GVertex<T>& b) const
	{
		return a.Weight() < b.Weight();
	}

	bool operator()(const GVertex<T>* a, const GVertex<T>* b) const
	{
		return a->Weight() < b->Weight();
	}
};

template<class T>
class WeightComparator
{
public:
	// Determine priority.
	bool operator()(const T& a, const T& b) const
	{
		return a.Weight() < b.Weight();
	}

	bool operator()(const T* a, const T* b) const
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
