// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "program.hpp"
#include "messages.hpp"

/*****************************************************************************/

Program::Program(std::string _m_name)
	: m_name(_m_name)
{
	Invalidatename(_m_name);
}


Program::Program(std::string _m_name
	, Time _m_time
	, Genre _m_genre
	, int _rating)
	:m_name(_m_name), m_time(_m_time), m_genre(_m_genre), rating(_rating)
{
	Invalidatename(_m_name);
	Invalidatóerating(_rating);
}


void Program::Invalidatóerating(int _rating)
{
	if (_rating < 1 || _rating >5)
		throw std::logic_error(Messages::InvalidRatingValue);
}

void Program::Invalidatename(std::string _m_name)
{
	if (_m_name.empty())
		throw std::logic_error(Messages::EmptyProgramName);
}

/*****************************************************************************/   