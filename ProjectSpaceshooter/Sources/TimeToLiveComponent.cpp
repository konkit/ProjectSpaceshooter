
bool TimeToLiveComponent::isTimeIsUp()
{
	return timeToLive<0;
}

void TimeToLiveComponent::decreaseTimeToLive()
{
	timeToLive--;
}

void TimeToLiveComponent::setTimeToLive( int newTime )
{
	timeToLive = newTime;
}

TimeToLiveComponent::TimeToLiveComponent()
{

}

