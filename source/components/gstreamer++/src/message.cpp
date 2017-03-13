#include <gstreamer++/message.h>

//#include <cassert>
#include <sstream>
#include <vector>
#include <gst/gst.h>
#include <gstreamer++/element.h>
#include <gstreamer++/serialization.h>

using namespace std;
using namespace GStreamer;

template<>
std::vector<EnumConversion<MessageType>> EnumSerializationInfo<MessageType>::Info =
    {
        { MessageType::EOS, "EOS" },
        { MessageType::Error, "Error" },
        { MessageType::Warning, "Warning" },
        { MessageType::Info, "Info" },
        { MessageType::Tag, "Tag" },
        { MessageType::StateChanged, "State" },
    };

Message::Message(GstMessage * messageInternal)
    : _messageInternal(messageInternal)
{
}

Message::~Message()
{
}

const char * Message::GetSource()
{

}

MessageType Message::GetType()
{
    return MessageType(GST_MESSAGE_TYPE(_messageInternal));
}

string Message::GetTypeName()
{
    return Serialize(GetType());
}

const char * Message::GetTimestamp()
{

}

string Message::GetContents()
{
    string contents;
    GError * err {};
    switch (GetType())
    {
        case MessageType::Error:
        {
            gst_message_parse_error(_messageInternal, &err, nullptr);
            contents = err->message;
            g_error_free(err);
            break;
        }
        case MessageType::Warning:
        {
            gst_message_parse_warning(_messageInternal, &err, nullptr);
            contents = err->message;
            g_error_free(err);
            break;
        }
        case MessageType::Info:
        {
            gst_message_parse_info(_messageInternal, &err, nullptr);
            contents = err->message;
            g_error_free(err);
            break;
        }
        case MessageType::Tag:
        {
            GstTagList * tagList;
            gst_message_parse_tag(_messageInternal, &tagList);
            contents = "Tag - to be parsed";
            gst_tag_list_unref(tagList);
            break;
        }
        case MessageType::StateChanged:
        {
            GstState oldState;
            GstState newState;
            GstState pendingState;
            gst_message_parse_state_changed(_messageInternal, &oldState, &newState, &pendingState);
            ostringstream stream;
            stream << static_cast<State>(oldState) << " --> "
                   << static_cast<State>(newState);
            if (static_cast<State>(pendingState) != State::VoidPending)
            {
                stream << " --->> " << static_cast<State>(pendingState);
            }
            contents = stream.str();
            break;
        }
        case MessageType::GST_MESSAGE_BUFFERING:
        {
            const GstStructure * structureInfo = gst_message_get_structure(_messageInternal);
            ostringstream stream;
            stream << "To be parsed";
            contents = stream.str();
            break;
        }
        default:
            contents = "";
            break;
    }
    return contents;
}

string Message::GetDebugInfo()
{
    string debugInfo;
    GError * err {};
    gchar * debug {};
    switch (GetType())
    {
        case MessageType::Error:
        {
            gst_message_parse_error(_messageInternal, &err, &debug);
            debugInfo = debug;
            g_error_free(err);
            g_free(debug);
            break;
        }
        case MessageType::Warning:
        {
            GError *err;
            gst_message_parse_warning(_messageInternal, &err, &debug);
            debugInfo = debug;
            g_error_free(err);
            g_free(debug);
            break;
        }
        case MessageType::Info:
        {
            GError *err;
            gst_message_parse_info(_messageInternal, &err, &debug);
            debugInfo = debug;
            g_error_free(err);
            g_free(debug);
            break;
        }
        default:
            debugInfo = "";
            break;
    }
    return debugInfo;
}

