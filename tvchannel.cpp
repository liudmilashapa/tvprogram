// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "tvchannel.hpp"
#include "messages.hpp"
#include "program.hpp"
#include <iostream>
/*****************************************************************************/

TVChannel::TVChannel(const std::string & _channelName)
	: TVName(_channelName)
{
}


void TVChannel::emptyday(int _poz)
{
	for (int i = 6; i > _poz; i--)
		if (!(TVshow[i].empty()))
			throw std::logic_error(Messages::InvalidProgramTime);
}
//ось
void TVChannel::Invalidday(int _day) const
{
	if (_day <0 || _day >6)
		throw std::logic_error(Messages::InvalidDayIndex);
}

void TVChannel::validtime(Time _time, int _day)

{
/*	for (const auto & program : TVshow[_day])
	{}
		if ((program->getTime().getHours() + 1 == _time.getHours()) || (program->getTime().getHours() - 1 == _time.getHours()) || (program->getTime().getHours() == _time.getHours()))
			throw std::logic_error(Messages::InvalidProgramTime);*/

		for (auto & show : TVshow[_day])
			if (show->getTime() >= _time)
				throw std::logic_error(Messages::InvalidProgramTime);
	
}

std::vector<Program*> TVChannel::returnProgram(int _day)
{
	return TVshow[_day];
}


void TVChannel::addProgram(int _day, Program * _program, Time _startTime)
{ 
	emptyday((int)_day);
	Invalidday((int)_day);
	validtime(_startTime, (int)_day);
	TVshow[_day].push_back(_program);
}

const std::vector<std::string> TVChannel::getPrograms(int _day) const
{
	std::vector<std::string> res;
	for (auto & show : TVshow[_day])
	{
		res.push_back(show->getName());
	}
	return res;
}

const void TVChannel::getSportPrograms(std::vector< std::string > * _vector)
{
	for (int i = 0; i < 7; i++)
	{
		for (auto & program : TVshow[i])
		{
			if (program->getGenre() == Genre::Sport)
			{
				if (SportPrograms.count(program->getName()) == 0)
					_vector->push_back(program->getName());
				SportPrograms.insert(program->getName());
			}
		}
	}
}

double TVChannel::getAverageRating() const
{
	int i, j, count = 0, rat = 0;
	for (i = 0; i < 7; i++)
	{
		for (j =0; j < TVshow[i].size(); j++)
		{
			rat += TVshow[i][j]->getRating();
		}
		count += j;
	}
	return ((double)rat / (double)count);
}


std::pair< Program*, int > TVChannel::getChannelLongestProgramm() const
{
	int i, j;
	int iCur = 0, jCur = 0;
	int Max;
	Max = TVshow[0][1]->getTime() - TVshow[0][0]->getTime();
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < TVshow[i].size() - 1; j++)
		{
			if (TVshow[i][j + 1]->getTime() - TVshow[i][j]->getTime() > Max)
			{
				Max = TVshow[i][j + 1]->getTime() - TVshow[i][j]->getTime();
				iCur = i;
				jCur = j;
			}
		}

		if ((i != 6) && (TVshow[i + 1][0]->getTime() - TVshow[i][j]->getTime() + 24 * 3600) > Max)
		{
			iCur = i;
			jCur = j ;
			Max = TVshow[i + 1][0]->getTime() - TVshow[i][j]->getTime() + 24 * 3600;
		}
		if ((i == 6) && (TVshow[0][0]->getTime() - TVshow[i][j]->getTime() + 24 * 3600) > Max)
		{
			Max = TVshow[0][0]->getTime() - TVshow[i][j]->getTime() + 24 * 3600;
			iCur = i;
			jCur = j;
		}
	}
	return std::make_pair(TVshow[iCur][jCur], Max);
}

Program *TVChannel::getChannelBestProgramChoiceFor(Day _day, int _hour) const
{
	
		int num = 0;
		for (int i = 0; i < TVshow[(int)_day].size(); i++)
		{
			Time t = TVshow[(int)_day][i]->getTime();
			if ((t.getHours() >= _hour - 1) && (t.getHours() <= _hour + 1))
			{
				num = i;;
				break;
			}
		}
		for (int i = 0; i < TVshow[(int)_day].size(); i++)
		{
			Time t = TVshow[(int)_day][i]->getTime();
			if ((t.getHours() >= _hour - 1) && (t.getHours() <= _hour + 1))
				if (TVshow[(int)_day][num]->getRating() < TVshow[(int)_day][i]->getRating())
					num = i;
		}
		return TVshow[(int)_day][num];
	
}

/*****************************************************************************/   