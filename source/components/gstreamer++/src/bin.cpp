#include <gstreamer++/bin.h>

#include <cstdarg>
//#include <iostream>
//#include <sstream>
#include <gst/gst.h>
#include <gvalue.h>

using namespace GStreamer;

Bin::Bin(_GstBin * internalBin)
    : Element(GST_ELEMENT(internalBin))
    , _elements()
    , _internalBin(internalBin)
{
    UpdateElements();
}

ElementPtr Bin::FindElementByName(const char * elementName)
{
    return std::make_shared<Element>(gst_bin_get_by_name(_internalBin, elementName));
}

ElementPtr Bin::FindElementByInterface(InterfaceType interface)
{
    return std::make_shared<Element>(gst_bin_get_by_interface(_internalBin, GType(interface)));
}

ElementList Bin::GetElements()
{
    GstIterator * iterator = gst_bin_iterate_elements(_internalBin);
    ElementList result;
    if (iterator)
    {
        GValue value = G_VALUE_INIT;
        while (GST_ITERATOR_OK == gst_iterator_next(iterator, &value))
        {
            result.push_back(FindOrCreateElement(GST_ELEMENT(value.data->v_pointer)));
            g_value_reset(&value);
        }
    }
    gst_iterator_free(iterator);
    return result;
}

void Bin::AddElement(Element::Ptr element)
{
    gst_bin_add(_internalBin, element->AsGstElement());
    // if (bin state = PAUSED or PLAYING)
    //    gst_element_sync_state_with_parent(element)
}

void Bin::AddElements(const ElementList &elements)
{
    for (auto element : elements)
    {
        AddElement(element);
    }
}

void Bin::RemoveElement(Element::Ptr element)
{
    gst_bin_remove(_internalBin, element->AsGstElement());
}

bool Bin::LinkElements(ElementPtr source, ElementPtr sink)
{
    return gst_element_link(source->AsGstElement(), sink->AsGstElement()) != FALSE;
}

bool Bin::LinkElements(ElementPtr source, ElementPtr sink, CapsPtr filter)
{
    return gst_element_link_filtered(source->AsGstElement(), sink->AsGstElement(), filter->AsGstCaps()) != FALSE;
}

void Bin::UnlinkElements(ElementPtr source, ElementPtr sink)
{
    gst_element_unlink(source->AsGstElement(), sink->AsGstElement());
}

ElementPtr Bin::FindOrCreateElement(_GstElement * element)
{
    char * result = nullptr;
    g_object_get(G_OBJECT(element), "name", &result, nullptr);
    for (auto item : _elements)
    {
        if (item->GetName() == result)
            return item;
    }
    ElementPtr newElement = std::make_shared<Element>(element);
    _elements.push_back(newElement);
    return newElement;
}

void Bin::UpdateElements()
{
    GetElements();
}