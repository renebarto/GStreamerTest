#pragma once

#include <deque>
#include <gstreamer++/message.h>

namespace GStreamer {

class MessageBus
{
public:
    MessageBus()
    {
    }
    virtual ~MessageBus()
    {
    }

    bool HaveMessage();
    Message GetMessage();
    void AddMessage(const Message & message) { _messages.push_back(message); }

private:
    std::deque<Message> _messages;
};

} // namespace GStreamer