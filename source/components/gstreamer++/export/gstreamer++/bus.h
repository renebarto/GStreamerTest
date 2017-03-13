#pragma once

#include <deque>
#include <gstreamer++/message.h>

struct _GstBus;

namespace GStreamer {

using BusWatchID = unsigned;
typedef int BusCallbackType(_GstBus * bus, _GstMessage * message, void * data);

class Bus
{
public:
    using Ptr = std::shared_ptr<Bus>;

    Bus() = delete;
    Bus(const Bus & other) = delete;
    Bus & operator = (const Bus & other) = delete;
    Bus(_GstBus * busInternal);
    virtual ~Bus()
    {
    }

    BusWatchID AddWatch(BusCallbackType callback, void * data);

    bool HaveMessage();
    MessagePtr GetMessage();
    void AddMessage(MessagePtr message) { _messages.push_back(message); }

private:
    std::deque<MessagePtr> _messages;
    _GstBus * _busInternal;
};

using BusPtr = Bus::Ptr;

} // namespace GStreamer