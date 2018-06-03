// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include <algorithm>

/*****************************************************************************/




int Controller::findChannel(const std::string & _channelName) const
{
	if (Names.count(_channelName) == 0)
		throw std::logic_error(Messages::ChannelCannotBeFound);
	int i;
	for (i = 0; i < v_controller.size(); i++)
	{
		if (v_controller[i]->getTVName() == _channelName)
			return i;
	}
	return -1;

}


void Controller::addChannel(const std::string & _channelName)
{
	TVChannel * chanel = new TVChannel(_channelName);
	if (_channelName.empty())
		throw std::logic_error(Messages::EmptyChannelName);

	if(Names.count(_channelName)==1)
		throw std::logic_error(Messages::DuplicateChannel);
	v_controller.push_back(chanel);
	Names.insert(_channelName);
}


void Controller::addProgram(
	const std::string & _channelName
	, Day _day
	, const std::string & _programName
	, Time _startTime
	, Genre _genre
	, int _rating
)
{
	int i = findChannel(_channelName);
	Program * pro = new Program(_programName
		, _startTime
		, _genre
		, _rating);
	if (i!=-1)
	// should not exist
//	v_programs.push_back(new Program(_programName, _startTime, _genre, _rating));
	

	v_controller[i]->addProgram((int)_day, pro, _startTime);
}


std::vector< std::string >
Controller::getPrograms(
	const std::string & _channelName
	,Day _day
	) const
{
	v_controller[0]->Invalidday((int)_day);
	int i = findChannel(_channelName);
	if (i != -1)
	return v_controller[i]->getPrograms((int)_day);
	


}


std::vector< std::vector< std::string > > Controller::getPrograms(const std::string & _channelName) const
{	std::vector< std::vector< std::string > > res;//= new  std::vector< std::vector< std::string > >;
	int i = findChannel(_channelName);
	if (i != -1)

		
	for (auto & channels : v_controller)
	{
		for (int i = 0; i < 7; i++)
		{
			res.push_back(channels->getPrograms(i));
		}
	}
	return res;
}



std::vector< std::string > Controller::getAllSportPrograms() const
{
	std::vector< std::string > res;
		for (auto & channels : v_controller)
		{
			channels->getSportPrograms(&res);
		}
	std::sort(res.begin(), res.end());
	return res;
}

std::string Controller::getChannelWithHighestAverageRating() const
{
	std::string res;
	for (int i = 0; i < v_controller.size() - 1; i++)
	{
		if (v_controller[i]->getAverageRating() > v_controller[i + 1]->getAverageRating())
			res = v_controller[i]->getTVName();
	}
	return res;
}

std::string Controller::getLongestProgram() const
{
	std::pair< Program*, int > temp= v_controller[0]->getChannelLongestProgramm();
	for (int i = 1; i < v_controller.size() ; i++)
	{
		if (v_controller[i ]->getChannelLongestProgramm().second > temp.second)
		{
			temp.first = v_controller[i]->getChannelLongestProgramm().first;
			temp.second = v_controller[i]->getChannelLongestProgramm().second;
		}

	}
	return (temp.first)->getName();
}

std::pair< std::string, std::string > Controller::getBestProgramChoiceFor(Day _day, int _hour) const
{
	v_controller[0]->Invalidday((int)_day);
	if ((_hour<1)&&(_hour>23))
	{
		throw std::logic_error(Messages::InvalidDateTime);
	}
	int num = 0;
	Program * cur = v_controller[0]->getChannelBestProgramChoiceFor(_day, _hour);
	for (int i = 1; i < v_controller.size(); i++)
	{
		Program * temp = v_controller[i]->getChannelBestProgramChoiceFor(_day, _hour);
		if (cur->getRating() < temp->getRating())
		{
			cur = temp;
			num = i;
		}
	}
	return std::make_pair(v_controller[num]->getTVName(), cur->getName());
}
	

/*****************************************************************************/  