#pragma once

#include <memory>

namespace GStreamer {

class Pad
{
public:
    using Ptr = std::shared_ptr<Pad>;

    Pad()
    {
    }
    virtual ~Pad()
    {
    }

private:
};

} // namespace GStreamer