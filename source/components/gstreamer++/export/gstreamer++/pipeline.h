#pragma once

#include <thread>
#include <gstreamer++/bin.h>
#include <gstreamer++/messagebus.h>

namespace GStreamer {

class Pipeline : public Bin
{
public:
    using Ptr = std::shared_ptr<Pipeline>;

    Pipeline()
    {
    }
    virtual ~Pipeline()
    {
    }

    Message GetMessage() { return _messageBus.GetMessage(); }

protected:
    virtual void SendMessage(const Message & message) override
    {
        _messageBus.AddMessage(message);
    }

private:
    std::thread _thread;
    MessageBus _messageBus;
};

using PipelinePtr = Pipeline::Ptr;

} // namespace GStreamer