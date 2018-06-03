// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

/*****************************************************************************/

#include "genre.hpp"
#include "time.hpp"
#include <string>

/*****************************************************************************/

class Program
{

/*-----------------------------------------------------------------*/

public:

	Program() = delete;

	Program( Program const & _program ) = delete;

	Program(std::string _m_name);

	Program(std::string _m_name, Time _m_time, Genre _m_genre, int _rating);

	const Genre & getGenre() const { return m_genre; };
	std::string getName() const { return m_name; };
	const Time & getTime() const { return m_time; };
	const int getRating() const { return rating; };

	void Invalidatename(std::string _m_name);
	void Invalidatóerating(int _rating);


private:

/*-----------------------------------------------------------------*/

	std::string m_name;
	Time m_time;
	Genre m_genre;
	int rating;

/*-----------------------------------------------------------------*/   

};

/*****************************************************************************/

#endif // _PROGRAM_HPP_
