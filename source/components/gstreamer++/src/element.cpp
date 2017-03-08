#include <gstreamer++/element.h>

//#include <cassert>
//#include <iostream>
//#include <sstream>
#include <gst/gst.h>

using namespace GStreamer;

Element::Element()
    : _parent()
    , _sinkPads()
    , _sourcePads()
    , _elementInternal()
{
}

Element::Element(GstElement * elementInternal)
    : _parent()
    , _sinkPads()
    , _sourcePads()
    , _elementInternal(elementInternal)
{
}

std::string Element::GetProperty(const char * name)
{
    char * result = nullptr;
    g_object_get(G_OBJECT(_elementInternal), name, &result, nullptr);
    std::string resultString = result;
    g_free(result);
    return resultString;
}
