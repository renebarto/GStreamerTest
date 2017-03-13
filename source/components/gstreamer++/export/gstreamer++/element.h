#pragma once

#include <memory>
#include <vector>
#include <gstreamer++/event.h>
#include <gstreamer++/message.h>
#include <gstreamer++/pad.h>
#include <gstreamer++/query.h>
#include <gstreamer++/serialization.h>

struct _GstElement;

namespace GStreamer {

enum class State
{
    VoidPending,
    Null,
    Ready,
    Paused,
    Playing
};

inline std::basic_ostream<char> & operator << (std::basic_ostream<char> & stream, const State & value)
{
    stream << Serialize(value);
    return stream;
}

enum class InterfaceType
{

};

class Element : public std::enable_shared_from_this<Element>
{
public:
    using Ptr = std::shared_ptr<Element>;

    Element() = delete;
    Element(const Element & other) = delete;
    Element & operator = (const Element & other) = delete;
    Element(_GstElement * elementInternal);
    virtual ~Element()
    {
    }
    Ptr GetParent() { return _parent; }
    void SetParent(Ptr parent);

    void ChangeState(State state);
    void OnReceiveMessage(Ptr origin, const MessagePtr & message);
    void OnReceiveEvent(Ptr origin, const Event & event);
    void OnReceiveQuery(Ptr origin, const Query & query);

    std::string GetName() { return GetProperty("name"); }
    std::string GetProperty(const char * name);
    void SetLocation(const char * value) { SetProperty("location", value); }
    void SetProperty(const char * name, const char * value);

    _GstElement * AsGstElement() { return _elementInternal; }

protected:
    virtual void SendMessage(const MessagePtr & message)
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
    _GstElement * _elementInternal;
};

using ElementPtr = Element::Ptr;
using ElementList = std::vector<ElementPtr>;

} // namespace GStreamer