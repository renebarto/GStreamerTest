#pragma once

#include <memory>
#include <vector>
#include <gstreamer++/event.h>
#include <gstreamer++/message.h>
#include <gstreamer++/pad.h>
#include <gstreamer++/query.h>

namespace GStreamer {

enum class State
{
    Paused,
    Playing
};

class Element : std::enable_shared_from_this<Element>
{
public:
    using Ptr = std::shared_ptr<Element>;

    Element()
    {
    }
    virtual ~Element()
    {
    }
    Ptr GetParent() { return _parent; }
    void SetParent(Ptr parent);

    void ChangeState(State state);
    void OnReceiveMessage(Ptr origin, const Message & message);
    void OnReceiveEvent(Ptr origin, const Event & event);
    void OnReceiveQuery(Ptr origin, const Query & query);

protected:
    virtual void SendMessage(const Message & message)
    {
        __glibcxx_assert(_parent != nullptr);
        _parent->SendMessage(message);
    }
    void SendEvent(Ptr target, const Event & event)
    {
        target->OnReceiveEvent(shared_from_this(), event);
    }
    void SendQuery(Ptr target, const Query & query)
    {
        target->OnReceiveQuery(shared_from_this(), query);
    }

private:
    Ptr _parent;
    std::vector<Pad::Ptr> _sinkPads;
    std::vector<Pad::Ptr> _sourcePads;
};

using ElementPtr = Element::Ptr;

} // namespace GStreamer