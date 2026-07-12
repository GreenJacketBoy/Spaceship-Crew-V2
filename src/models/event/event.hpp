#ifndef EVENT_H
#define EVENT_H

enum class EventType {
    MEDICAL,
    ENGINEERING,
};

class Event {
public:
    virtual ~Event() {};
    virtual const char* getTypeName() final { return this->typeName; }
    virtual EventType getType() final { return this->type; }

protected:
    EventType type;
    // String literal instead of std::string because they are stored in .rodata, not the stack or the heap
    // https://en.cppreference.com/cpp/language/string_literal
    const char* typeName;
};

#endif // !EVENT_H
