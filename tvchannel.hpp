// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TVCHANNEL_HPP_
#define _TVCHANNEL_HPP_
#include <vector>
#include <string>
#include <set>

#include "day.hpp"
#include "time.hpp"

/*****************************************************************************/

class Program;

/*****************************************************************************/

class TVChannel
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	TVChannel(const std::string & _channelName);

	TVChannel() = delete;

	TVChannel(const TVChannel & _channel ) = delete;

	void emptyday(int _poz);
	void validtime(Time _time, int _day);
	std::vector<Program*> returnProgram(int _day);
	void Invalidday(int _day) const;
	//std::vector< std::string > TVChannel::getnameProgram(int _day)const;

	const std::vector<Program*> & getTVshow() const { return TVshow[7]; }
	std::string getTVName() const { return TVName; };
	//
	const std::vector<std::string> getPrograms(int _day) const;
	const void getSportPrograms(std::vector< std::string > * _vector) ;

	double getAverageRating() const;

	std::pair< Program*, int > getChannelLongestProgramm() const;

	Program* getChannelBestProgramChoiceFor(Day _day, int _hour) const;

	void addProgram(int day, Program * _program,  Time _startTime);
	
	/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string TVName;
	std::vector<Program*> TVshow[7];
	std::set < std::string > SportPrograms;
	std::vector <Time> First_Program;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _TVCHANNEL_HPP_
