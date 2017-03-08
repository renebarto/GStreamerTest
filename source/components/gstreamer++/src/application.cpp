#include <gstreamer++/application.h>

#include <cassert>
#include <iostream>
#include <sstream>
#include <gst/gst.h>

using namespace GStreamer;

bool Application::_initialized = false;

Application::Application(int argc, const char * argv[])
    : _argc(argc)
    , _argv(argv)
    , _thread()
    , _pipeline(nullptr)
    , _majorVersion()
    , _minorVersion()
    , _microVersion()
    , _nanoVersion()
    , _parseOptions()
    , _parseApplicationParameters(false)
{
    guint major, minor, micro, nano;

    gst_version (&major, &minor, &micro, &nano);
    _majorVersion = major;
    _minorVersion = minor;
    _microVersion = micro;
    _nanoVersion = nano;
}

Application::Application(int argc, const char * argv[], std::vector<OptionEntry> parseOptions)
    : Application(argc, argv)
{
    _parseApplicationParameters = true;
    _parseOptions = parseOptions;
}

void Application::Initialize()
{
    assert(!_initialized);
    if ((_argc != 0) && !_parseApplicationParameters)
        gst_init(&_argc, const_cast<char ***>(&_argv));
    else
        gst_init(nullptr, nullptr);
    if (_parseApplicationParameters)
    {
        assert(ParseApplicationParameters());
    }
    _initialized = true;
}

bool Application::InitializeChecked(ErrorList & errors)
{
    errors.Clear();
    if (_initialized)
        errors.AddError(Error(ErrorCode::AlreadyInitialized));
    GError * error;
    bool result {};
    if ((_argc != 0) && !_parseApplicationParameters)
        result = gst_init_check(&_argc, const_cast<char ***>(&_argv), &error);
    else
        result = gst_init_check(nullptr, nullptr, &error);
    if (_parseApplicationParameters && !ParseApplicationParameters())
    {
        Deinitialize();
        return false;
    }
    _initialized = result;
    return _initialized;
}

void Application::Deinitialize()
{
    assert(_initialized);
    gst_deinit();
    _initialized = false;
}

std::string Application::VersionString()
{
    std::ostringstream stream;
    stream << _majorVersion << "." << _minorVersion << "." << _microVersion << "." << _nanoVersion;
    return stream.str();
}

bool Application::IsSegTrapEnabled()
{
    assert(_initialized);
    return gst_segtrap_is_enabled() != FALSE;
}
void Application::SetSegTrapEnabled(bool enabled)
{
    assert(_initialized);
    gst_segtrap_set_enabled(enabled ? TRUE : FALSE);
}

bool Application::IsRegistryForkEnabled()
{
    assert(_initialized);
    return gst_registry_fork_is_enabled() != FALSE;
}

void Application::SetRegistryForkEnabled(bool enabled)
{
    assert(_initialized);
    gst_registry_fork_set_enabled(enabled ? TRUE : FALSE);
}

void Application::UpdateRegistry()
{
    assert(_initialized);
    gst_update_registry();
}

bool Application::ParseApplicationParameters()
{
    applicationName = _argv[0];
    GOptionEntry * optionEntries = new GOptionEntry[_parseOptions.size() + 1];
    for (size_t index = 0; index < _parseOptions.size(); index++)
    {
        optionEntries[index].long_name = _parseOptions[index].longName;
        optionEntries[index].short_name = _parseOptions[index].shortName;
        optionEntries[index].flags = _parseOptions[index].flags;
        optionEntries[index].arg = static_cast<GOptionArg>(_parseOptions[index].arg);
        optionEntries[index].arg_data = _parseOptions[index].argData;
        optionEntries[index].description = _parseOptions[index].description;
        optionEntries[index].arg_description = _parseOptions[index].argDescription;
    }
    optionEntries[_parseOptions.size()] = { nullptr, '\0', 0, GOptionArg::G_OPTION_ARG_NONE, nullptr, nullptr, nullptr };

    GOptionContext * context = g_option_context_new(applicationName.c_str());
    g_option_context_add_main_entries(context, optionEntries, nullptr);
    g_option_context_add_group(context, gst_init_get_option_group());

    GError * err = nullptr;

    bool result = true;
    if (!g_option_context_parse (context, &_argc, const_cast<char ***>(&_argv), &err))
    {
        std::cout << "Failed to initialize: " << err->message << std::endl;
        g_clear_error(&err);
        result = false;
    }
    g_option_context_free(context);
    return result;
}

RegistryPtr Application::GetRegistry()
{
    return std::make_shared<Registry>(gst_registry_get());
}

PipelinePtr Application::CreatePipeline(const char * pipelineName)
{
    return std::make_shared<Pipeline>(GST_PIPELINE(gst_pipeline_new(pipelineName)));
}

ElementFactoryPtr Application::GetElementFactory(const char * factoryName)
{
    return std::make_shared<ElementFactory>(gst_element_factory_find(factoryName));
}

ElementPtr Application::MakeElement(const char * factoryName, const char * elementName)
{
    return std::make_shared<Element>(gst_element_factory_make(factoryName, elementName));
}
