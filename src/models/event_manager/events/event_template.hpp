#ifndef EVENT_INTERFACE_HPP
#define EVENT_INTERFACE_HPP

#include <vector>

template <typename Payload, typename Subscriber>
class Event {
public: 
    virtual void emit(Payload &payload) = 0; // virtual because Subscribers each have a different handle command

    inline void subscribe(Subscriber &subscriber) {
        this->subscribers.push_back(&subscriber);
    };

    void unsubscribe(Subscriber &subscriberToRemove) {
        std::vector<Subscriber*> newSubscribers;
        newSubscribers.reserve(this->subscribers.size() - 1);
        for (auto subscriber : this->subscribers) {
            if (subscriber != &subscriberToRemove) newSubscribers.push_back(subscriber);
        }
        this->subscribers = std::move(newSubscribers);
    };
protected:
    std::vector<Subscriber*> subscribers;
};

#endif // !EVENT_INTERFACE_HPP
