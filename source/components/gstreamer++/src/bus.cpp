#include <gstreamer++/bus.h>

//#include <cassert>
//#include <iostream>
//#include <sstream>
#include <gst/gst.h>

using namespace GStreamer;

Bus::Bus(GstBus * busInternal)
    : _busInternal(busInternal)
{
}

BusWatchID Bus::AddWatch(BusCallbackType callback, void * data)
{
    return gst_bus_add_watch(_busInternal, callback, data);
}
