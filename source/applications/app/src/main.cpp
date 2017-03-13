#include <gstreamer++/application.h>

#include <iostream>
#include <string.h>
#include <termios.h>

using namespace std;
using namespace GStreamer;

int kbhit();

int main (int argc, const char * argv[])
{
    bool verbose = false;
    Application app(argc, argv, {
        OptionEntry{"verbose", 'v', 0, OptionType::G_OPTION_ARG_NONE, &verbose, "Verbose output", ""}
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

    if (!pipeline->LinkElements(elementSource, elementFilter, elementSink))
        cout << "Failed to link elements" << endl;

    app.Start();

    bool quit = false;
    while (!quit)
    {
        ::g_usleep(1000);
        if (kbhit() == 'q')
            quit = true;
    }
    app.Stop();

    app.Deinitialize();

    return 0;
}

int kbhit()
{
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

