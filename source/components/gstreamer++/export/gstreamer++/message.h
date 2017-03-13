#pragma once

#include <memory>

struct _GstMessage;

namespace GStreamer {

class Element;
using ElementPtr = std::shared_ptr<Element>;

enum class MessageType
{
    GST_MESSAGE_UNKNOWN           = 0,
    EOS               = (1 << 0),
    Error             = (1 << 1),
    Warning           = (1 << 2),
    Info              = (1 << 3),
    Tag               = (1 << 4),
    GST_MESSAGE_BUFFERING         = (1 << 5),
    StateChanged     = (1 << 6),
    GST_MESSAGE_STATE_DIRTY       = (1 << 7),
    GST_MESSAGE_STEP_DONE         = (1 << 8),
    GST_MESSAGE_CLOCK_PROVIDE     = (1 << 9),
    GST_MESSAGE_CLOCK_LOST        = (1 << 10),
    GST_MESSAGE_NEW_CLOCK         = (1 << 11),
    GST_MESSAGE_STRUCTURE_CHANGE  = (1 << 12),
    GST_MESSAGE_STREAM_STATUS     = (1 << 13),
    GST_MESSAGE_APPLICATION       = (1 << 14),
    GST_MESSAGE_ELEMENT           = (1 << 15),
    GST_MESSAGE_SEGMENT_START     = (1 << 16),
    GST_MESSAGE_SEGMENT_DONE      = (1 << 17),
    GST_MESSAGE_DURATION_CHANGED  = (1 << 18),
    GST_MESSAGE_LATENCY           = (1 << 19),
    GST_MESSAGE_ASYNC_START       = (1 << 20),
    GST_MESSAGE_ASYNC_DONE        = (1 << 21),
    GST_MESSAGE_REQUEST_STATE     = (1 << 22),
    GST_MESSAGE_STEP_START        = (1 << 23),
    GST_MESSAGE_QOS               = (1 << 24),
    GST_MESSAGE_PROGRESS          = (1 << 25),
    GST_MESSAGE_TOC               = (1 << 26),
    GST_MESSAGE_RESET_TIME        = (1 << 27),
    GST_MESSAGE_STREAM_START      = (1 << 28),
    GST_MESSAGE_NEED_CONTEXT      = (1 << 29),
    GST_MESSAGE_HAVE_CONTEXT      = (1 << 30),
    GST_MESSAGE_EXTENDED          = (1 << 31),
    GST_MESSAGE_DEVICE_ADDED      = GST_MESSAGE_EXTENDED + 1,
    GST_MESSAGE_DEVICE_REMOVED    = GST_MESSAGE_EXTENDED + 2,
    GST_MESSAGE_ANY               = int(0xffffffff),
};

class Message
{
public:
    using Ptr = std::shared_ptr<Message>;

    Message() = delete;
    Message(const Message & other) = delete;
    Message & operator = (const Message & other) = delete;
    Message(_GstMessage * internalMessage);
    virtual ~Message();

    const char * GetSource();
    MessageType GetType();
    std::string GetTypeName();
    const char * GetTimestamp();
    std::string GetContents();
    std::string GetDebugInfo();

private:
    _GstMessage * _messageInternal;
};

using MessagePtr = Message::Ptr;

class ErrorMessage : public Message
{
public:
    ErrorMessage(_GstMessage * internalMessage)
        : Message(internalMessage)
    {
    }
};

class Warning : public Message
{
public:
    Warning(_GstMessage * internalMessage)
        : Message(internalMessage)
    {
    }
};

class InformationMessage : public Message
{
public:
    InformationMessage(_GstMessage * internalMessage)
        : Message(internalMessage)
    {
    }
};

class TagMessage : public Message
{
public:
    TagMessage(_GstMessage * internalMessage)
        : Message(internalMessage)
    {
    }
};

class EosMessage : public Message
{
public:
    EosMessage(_GstMessage * internalMessage)
        : Message(internalMessage)
    {
    }
};

} // namespace GStreamer