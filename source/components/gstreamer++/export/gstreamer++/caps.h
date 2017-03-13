#pragma once

#include <memory>
#include <gst/gstcaps.h>

namespace GStreamer {

class Caps
{
public:
    using Ptr = std::shared_ptr<Caps>;

    Caps() = delete;
    Caps(const Caps & other) = delete;
    Caps & operator = (const Caps & other) = delete;
    Caps(_GstCaps * capsInternal)
        : _capsInternal(capsInternal)
    {
    }
    virtual ~Caps()
    {
    }

    _GstCaps * AsGstCaps() { return _capsInternal; }

private:
    _GstCaps * _capsInternal;
};

using CapsPtr = Caps::Ptr;

} // namespace GStreamer