#pragma once

#include <memory>

namespace GStreamer {

class Element;
using ElementPtr = std::shared_ptr<Element>;

class Message
{
public:

    Message()
    {
    }
    Message(const Message & other)
        : _origin(other._origin)
    {
    }
    Message(Message && other)
        : _origin(std::move(other._origin))
    {
    }
    virtual ~Message()
    {
    }
    Message & operator = (const Message & other)
    {
        if (this != &other)
        {
            _origin = other._origin;
        }
        return *this;
    }
    Message & operator = (Message && other)
    {
        _origin = std::move(other._origin);
        return *this;
    }

private:
    ElementPtr _origin;
};

} // namespace GStreamer