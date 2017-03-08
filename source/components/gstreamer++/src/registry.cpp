#include <gstreamer++/registry.h>

//#include <cassert>
//#include <iostream>
//#include <sstream>
#include <gst/gst.h>

using namespace GStreamer;

Registry::Registry(GstRegistry * registryInternal)
    : _registryInternal(registryInternal)
{
}

ElementFactoryList Registry::GetFactories()
{
    ElementFactoryList factoryList;
    GList *l = gst_registry_get_feature_list(_registryInternal, GST_TYPE_ELEMENT_FACTORY);
    GList *i = l;
    GList *e = g_list_last(i);
    for(;;)
    {
        factoryList.push_back(std::make_shared<ElementFactory>(static_cast<GstElementFactory *>(i->data)));
        if (i == e) break;
        i = g_list_next(i);
    }
    g_list_free(l);
    return factoryList;
}
