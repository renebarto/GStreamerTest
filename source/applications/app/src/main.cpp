#include <gstreamer++/application.h>

#include <iostream>

using namespace std;
using namespace GStreamer;

int main (int argc, const char * argv[])
{
    bool verbose = false;
    Application app(argc, argv, {
        OptionEntry{"verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Verbose output", ""}
    });

    ErrorList errors;
    app.InitializeChecked(errors);

    ElementFactoryPtr factory = app.GetElementFactory("fakesrc");
    ElementPtr elementSource = factory->Create("source");
    ElementPtr elementFilter = app.MakeElement("identity", "filter");
    ElementPtr elementSink = app.MakeElement("fakesink", "sink");

    cout << "Source " << elementSource->GetProperty("name") << endl;
    cout << "Filter " << elementFilter->GetProperty("name") << endl;
    cout << "Sink   " << elementSink->GetProperty("name") << endl;
    cout << "Factory for element " << factory->GetElementName()
         << " Category " << factory->GetElementClass()
         << " Description " << factory->GetElementDescription() << endl;

    RegistryPtr registry = app.GetRegistry();
    ElementFactoryList factories = registry->GetFactories();
    cout << "Factory list" << endl;
    for (auto factory : factories)
    {
        cout << "Factory for element " << factory->GetElementName()
             << " Category " << factory->GetElementClass()
             << " Description " << factory->GetElementDescription() << endl;
    }

    PipelinePtr pipeline = app.CreatePipeline("pipeline");

    pipeline->AddElements(elementSource, elementFilter, elementSink);

    app.Deinitialize();

    return 0;
}