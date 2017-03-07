#pragma once

namespace GStreamer {

enum class ErrorCode : int
{
    Undefined = -1,
    None = 0,
    AlreadyInitialized = 1,
};
class Error
{
public:
    Error()
        : _code(ErrorCode::None)
    {
    }
    Error(ErrorCode code)
        : _code(code)
    {
    }
    virtual ~Error()
    {
    }

private:
    ErrorCode _code;
};

} // namespace GStreamer