#include <gstreamer++/application.h>

int main (int argc, const char * argv[])
{
    GStreamer::Application app(argc, argv);
    app.Initialize();

    app.Deinitialize();

    return 0;
}