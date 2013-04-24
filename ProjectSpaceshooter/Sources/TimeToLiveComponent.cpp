
bool TimeToLiveComponent::isTimeIsUp()
{
	return timeToLive<0.0;
}

void TimeToLiveComponent::decreaseTimeToLive(float deltaTime)
{
	timeToLive-=deltaTime;
}

void TimeToLiveComponent::setTimeToLive( float newTime )
{
	timeToLive = newTime;
	startTime = newTime;
}

TimeToLiveComponent::TimeToLiveComponent()
	: timeToLive(1), startTime(1)
{

}

double TimeToLiveComponent::percentOfLeftTime()
{
	return timeToLive / startTime;
}

