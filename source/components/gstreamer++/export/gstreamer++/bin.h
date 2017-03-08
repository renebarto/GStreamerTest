#pragma once

#include <vector>
#include <gstreamer++/element.h>

struct _GstBin;

namespace GStreamer {

class Bin : public Element
{
public:
    Bin();
    Bin(_GstBin * internalBin);
    virtual ~Bin()
    {
    }

    void AddElement(ElementPtr element);
    void RemoveElement(Element::Ptr element);

    void AddElements(const ElementList & elements);
    void AddElements() {}
    template<class ElementPtr, class ...ElementPtrArgs>
    void AddElements(ElementPtr element, ElementPtrArgs... elements)
    {
        AddElement(element);
        AddElements(elements...);
    }

private:
    std::vector<Element::Ptr> _elements;
    _GstBin * _internalBin;
};

} // namespace GStreamer