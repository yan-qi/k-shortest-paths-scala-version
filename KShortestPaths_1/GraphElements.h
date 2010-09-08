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

#include <string>


template<class T>
class WeightGreater
{
public:
	// Determine priority.
	bool operator()(const T& a, const T& b) const
	{
		return a.Weight() > b.Weight();
	}

	bool operator()(const T* a, const T* b) const
	{
		return a->Weight() > b->Weight();
	}
};

template<class T>
class WeightLess
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



/**************************************************************************
*  BaseVertex
*  <TODO: insert class description here>
*
*
*  @remarks <TODO: insert remarks here>
*
*  @author Yan Qi @date 6/6/2010
**************************************************************************/
class BaseVertex
{
	int m_nID;
	double m_dWeight;	

public:

	int getID() const { return m_nID; }
	void setID(int ID_) { m_nID = ID_; }

	double Weight() const { return m_dWeight; }
	void Weight(double val) { m_dWeight = val; }

	void PrintOut(std::ostream& out_stream)
	{
		out_stream << m_nID;
	}
};