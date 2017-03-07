#pragma once

#include <vector>

#include <gstreamer++/error.h>

namespace GStreamer {

class ErrorList
{
public:
    void Clear() { _errors.clear(); }

    void AddError(const Error & error) { _errors.push_back(error); }

private:
    std::vector<Error> _errors;
};

} // namespace GStreamer