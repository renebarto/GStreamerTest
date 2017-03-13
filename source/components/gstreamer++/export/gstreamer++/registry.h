#pragma once

//#include <thread>
//#include <gstreamer++/bin.h>
#include <gstreamer++/elementfactory.h>

struct _GstRegistry;

namespace GStreamer {

class Registry
{
public:
    using Ptr = std::shared_ptr<Registry>;

    Registry() = delete;
    Registry(const Registry & other) = delete;
    Registry & operator = (const Registry & other) = delete;
    Registry(_GstRegistry * registryInternal);
    virtual ~Registry()
    {
    }

    ElementFactoryList GetFactories();

protected:

private:
    _GstRegistry * _registryInternal;
};

using RegistryPtr = Registry::Ptr;

} // namespace GStreamer