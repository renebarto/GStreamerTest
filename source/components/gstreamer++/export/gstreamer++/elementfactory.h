#pragma once

//#include <memory>
//#include <vector>
//#include <gstreamer++/event.h>
//#include <gstreamer++/message.h>
//#include <gstreamer++/pad.h>
#include <gstreamer++/element.h>

struct _GstElementFactory;

namespace GStreamer {

class ElementFactory : public std::enable_shared_from_this<ElementFactory>
{
public:
    using Ptr = std::shared_ptr<ElementFactory>;

    ElementFactory() = delete;
    ElementFactory(const ElementFactory & other) = delete;
    ElementFactory & operator = (const ElementFactory & other) = delete;
    ElementFactory(_GstElementFactory * factoryInternal);
    virtual ~ElementFactory()
    {
    }

    ElementPtr Create(const char * name);
    std::string GetElementName();
    std::string GetElementClass();
    std::string GetElementDescription();

protected:

private:
    _GstElementFactory * _factoryInternal;
};

using ElementFactoryPtr = ElementFactory::Ptr;
using ElementFactoryList = std::vector<ElementFactoryPtr>;

} // namespace GStreamer