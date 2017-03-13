#pragma once

#include <thread>
#include <gstreamer++/bin.h>
#include <gstreamer++/bus.h>

struct _GstPipeline;

namespace GStreamer {

class Pipeline : public Bin
{
public:
    using Ptr = std::shared_ptr<Pipeline>;

    Pipeline() = delete;
    Pipeline(const Pipeline & other) = delete;
    Pipeline & operator = (const Pipeline & other) = delete;
    Pipeline(_GstPipeline * pipelineInternal);
    virtual ~Pipeline();

    MessagePtr GetMessage() { return _bus->GetMessage(); }
    BusPtr GetBus() { return _bus; }

protected:
    virtual void SendMessage(const MessagePtr & message) override
    {
        _bus->AddMessage(message);
    }

private:
    _GstPipeline * _pipelineInternal;
    std::thread _thread;
    BusPtr _bus;
};

using PipelinePtr = Pipeline::Ptr;

} // namespace GStreamer