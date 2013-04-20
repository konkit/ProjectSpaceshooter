
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
}

TimeToLiveComponent::TimeToLiveComponent()
{

}

