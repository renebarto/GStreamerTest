#pragma once

#include <memory>

namespace GStreamer {

class Buffer
{
public:
    using Ptr = std::shared_ptr<Buffer>;

    Buffer()
    {
    }
    virtual ~Buffer()
    {
    }

private:
};

} // namespace GStreamer