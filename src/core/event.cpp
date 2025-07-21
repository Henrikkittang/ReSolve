#include"event.hpp"


bool EventManager::pollEvent(Event& event)
{
    if( s_events.empty() )
        return false;

    event = s_events.top();
    s_events.pop();

    return true;
}

void EventManager::dispatchEvent(Event event)
{
    s_events.push(event);
}