#include <gstreamer++/elementfactory.h>

//#include <cassert>
//#include <iostream>
//#include <sstream>
#include <gst/gst.h>

using namespace GStreamer;

ElementFactory::ElementFactory(GstElementFactory * factoryInternal)
    : _factoryInternal(factoryInternal)
{
}

ElementPtr ElementFactory::Create(const char * name)
{
    return std::make_shared<Element>(gst_element_factory_create(_factoryInternal, name));
}

std::string ElementFactory::GetElementName()
{
    return gst_plugin_feature_get_name(GST_PLUGIN_FEATURE(_factoryInternal));
}

std::string ElementFactory::GetElementClass()
{
    return gst_element_factory_get_metadata(_factoryInternal, GST_ELEMENT_METADATA_KLASS);
}

std::string ElementFactory::GetElementDescription()
{
    return gst_element_factory_get_metadata(_factoryInternal, GST_ELEMENT_METADATA_DESCRIPTION);
}

