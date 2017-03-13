#include <gstreamer++/element.h>

//#include <cassert>
//#include <iostream>
//#include <sstream>
#include <gst/gst.h>

using namespace GStreamer;

template<>
std::vector<EnumConversion<State>> EnumSerializationInfo<State>::Info =
{
    { State::VoidPending, "Void" },
    { State::Null, "Null" },
    { State::Ready, "Ready" },
    { State::Paused, "Paused" },
    { State::Playing, "Playing" },
};

Element::Element(GstElement * elementInternal)
    : _parent()
    , _sinkPads()
    , _sourcePads()
    , _elementInternal(elementInternal)
{
}

void Element::ChangeState(State state)
{
    gst_element_set_state(_elementInternal, GstState(state));
}

std::string Element::GetProperty(const char * name)
{
    char * result = nullptr;
    g_object_get(G_OBJECT(_elementInternal), name, &result, nullptr);
    std::string resultString = result;
    g_free(result);
    return resultString;
}

void Element::SetProperty(const char * name, const char * value)
{
    g_object_set(G_OBJECT(_elementInternal), name, value, nullptr);
}
