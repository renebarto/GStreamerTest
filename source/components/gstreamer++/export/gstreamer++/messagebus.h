#pragma once

#include <vector>
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
    void AddMessage(const Message & message);

private:
    std::vector<Message> _messages;
};

} // namespace GStreamer