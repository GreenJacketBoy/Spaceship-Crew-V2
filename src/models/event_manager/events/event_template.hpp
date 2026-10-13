#ifndef EVENT_INTERFACE_HPP
#define EVENT_INTERFACE_HPP

#include <set>

template <typename Payload, typename Subscriber>
class Event {
public: 
    virtual void emitEvent(Payload &payload) = 0; // virtual because Subscribers each have a different handle command

    inline void subscribe(Subscriber &subscriber) {
        this->subscribers.insert(&subscriber);
    };

    inline void unsubscribe(Subscriber &subscriberToRemove) {
        this->subscribers.erase(subscriberToRemove);
    };
protected:
    std::set<Subscriber*> subscribers;
};

#endif // !EVENT_INTERFACE_HPP
