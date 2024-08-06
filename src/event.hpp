#pragma once
#include<stack>

enum class Event : int
{
    END_CURRENT_SCENE,
};

class EventManager
{
public:
    
    static bool pollEvent(Event& event);
    static void dispatchEvent(Event event);

private:
    inline static std::stack<Event> s_events;
};