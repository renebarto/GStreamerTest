#include <gstreamer++/bin.h>

#include <cstdarg>
//#include <iostream>
//#include <sstream>
#include <gst/gst.h>

using namespace GStreamer;

Bin::Bin()
    : Element()
    , _elements()
    , _internalBin()
{
}

Bin::Bin(_GstBin * internalBin)
    : Element(GST_ELEMENT(internalBin))
    , _elements()
    , _internalBin(internalBin)
{
}

void Bin::AddElement(Element::Ptr element)
{
    gst_bin_add(_internalBin, element->AsGstElement());
}

void Bin::AddElements(const ElementList &elements)
{
    for (auto element : elements)
    {
        AddElement(element);
    }
}

//void Bin::AddElements(ElementPtr element, ...)
//{
//    va_list list;
//    va_start(list, element);
//    AddElement(element);
//    Element * currentElement;
//    while (currentElement = va_arg(list, Element *))
//    {
//        if (nullptr == currentElement)
//            break;
//        AddElement(reinterpret_cast<ElementPtr>(currentElement));
//    }
//    va_end(list);
//}
