#pragma once

#include <vector>
#include <gstreamer++/element.h>

namespace GStreamer {

class Bin : public Element
{
public:
    Bin()
        : _elements()
    {
    }
    virtual ~Bin()
    {
    }

    void AddElement(Element::Ptr element);
    void RemoveElement(Element::Ptr element);

private:
    std::vector<Element::Ptr> _elements;
};

} // namespace GStreamer