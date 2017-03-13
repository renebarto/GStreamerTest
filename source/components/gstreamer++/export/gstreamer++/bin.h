#pragma once

#include <vector>
#include <gstreamer++/caps.h>
#include <gstreamer++/element.h>

struct _GstBin;

namespace GStreamer {

class Bin : public Element
{
public:
    using Ptr = std::shared_ptr<Bin>;

    Bin() = delete;
    Bin(const Bin & other) = delete;
    Bin & operator = (const Bin & other) = delete;
    Bin(_GstBin * internalBin);
    virtual ~Bin()
    {
    }

    void AddElement(ElementPtr element);
    void RemoveElement(Element::Ptr element);
    bool LinkElements(ElementPtr source, ElementPtr sink);
    bool LinkElements(ElementPtr source, ElementPtr sink, CapsPtr filter);
    void UnlinkElements(ElementPtr source, ElementPtr sink);

    ElementPtr FindElementByName(const char * elementName);
    ElementPtr FindElementByInterface(InterfaceType interface);
    ElementList GetElements();

    void AddElements(const ElementList & elements);
    void AddElements() {}
    template<class Element, class ...OtherElements>
    void AddElements(Element element, OtherElements... elements)
    {
        AddElement(element);
        AddElements(elements...);
    }
    template<class Element, class ...OtherElements>
    void RemoveElements(Element element, OtherElements... elements)
    {
        RemoveElement(element);
        RemoveElements(elements...);
    }
    template<class Source, class Sink, class ...ElementPtrArgs>
    bool LinkElements(Source source, Sink sink, ElementPtrArgs... elements)
    {
        if (!LinkElements(source, sink))
            return false;
        return LinkElements(sink, elements...);
    }
    template<class Source, class Sink, class ...ElementPtrArgs>
    void UnlinkElements(Source source, Sink sink, ElementPtrArgs... elements)
    {
        UnlinkElements(source, sink);
        UnlinkElements(sink, elements...);
    }

private:
    std::vector<ElementPtr> _elements;
    _GstBin * _internalBin;

    ElementPtr FindOrCreateElement(_GstElement * element);
    void UpdateElements();
};

using BinPtr = Bin::Ptr;

} // namespace GStreamer