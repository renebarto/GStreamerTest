#include <gtest/gtest.h>
#include <gst/gst.h>
#include <gstreamer++/application.h>

namespace GStreamer {
namespace Test {

class ApplicationTest : public ::testing::Test {
public:
    ApplicationTest()
        : argc(0)
        , argv(nullptr)
    {}

protected:
    virtual void SetUp() {}

    virtual void TearDown()
    {
        CleanupArgv();
        if (Application::IsInitialized())
            Application::Cleanup();
    }

    void SetupArgv(const std::vector<std::string> & arguments)
    {
        CleanupArgv();
        argc = static_cast<int>(arguments.size());
        argv = new const char * [argc + 1];
        char * * tmp = const_cast<char * *>(argv);
        for (auto arg : arguments)
        {
            *tmp = new char[arg.length() + 1];
            strcpy(*tmp, arg.data());
            *(*tmp + arg.length()) = '\0';
            ++tmp;
        }
        *tmp = nullptr;
    }
    void CleanupArgv()
    {
        if (argv != nullptr)
        {
            const char * * tmp = argv;
            const char * arg = *tmp++;
            while (arg)
            {
                delete [] arg;
                arg = *tmp++;
            }
            delete [] argv;
            argv = nullptr;
            argc = 0;
        }
    }
    int argc;
    const char * * argv;
};

TEST_F(ApplicationTest, Constructor)
{
    SetupArgv({ "App" });
    Application app(argc, argv);

    EXPECT_FALSE(app.IsInitialized()) << "Application should not be initialized";
    EXPECT_NE(0, app.MajorVersion()) << "Version should be initialized";
    EXPECT_NE("", app.VersionString()) << "Version should be initialized";
}

TEST_F(ApplicationTest, Initialize)
{
    SetupArgv({ "App" });
    Application app(argc, argv);
    app.Initialize();

    EXPECT_TRUE(app.IsInitialized()) << "Application should not be initialized";
    EXPECT_NE(0, app.MajorVersion()) << "Version should be initialized";
    EXPECT_NE("", app.VersionString()) << "Version should be initialized";
}

TEST_F(ApplicationTest, InitializeChecked)
{
    SetupArgv({ "App" });
    Application app(argc, argv);
    ErrorList errors;
    EXPECT_TRUE(app.InitializeChecked(errors));

    EXPECT_TRUE(app.IsInitialized()) << "Application should not be initialized";
    EXPECT_NE(0, app.MajorVersion()) << "Version should be initialized";
    EXPECT_NE("", app.VersionString()) << "Version should be initialized";
}

TEST_F(ApplicationTest, InitializeWithApplicationParameters)
{
    SetupArgv({ "App" });
    bool verbose = false;
    Application app(argc, argv, { OptionEntry{"verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Verbose output", ""} });
    ErrorList errors;
    EXPECT_TRUE(app.InitializeChecked(errors));

    EXPECT_TRUE(app.IsInitialized()) << "Application should not be initialized";
    EXPECT_NE(0, app.MajorVersion()) << "Version should be initialized";
    EXPECT_NE("", app.VersionString()) << "Version should be initialized";
    EXPECT_FALSE(verbose);
}

TEST_F(ApplicationTest, InitializeWithApplicationParametersSpecifiedShort)
{
    SetupArgv({ "App", "-v" });
    bool verbose = false;
    Application app(argc, argv, { OptionEntry{"verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Verbose output", ""} });
    ErrorList errors;
    EXPECT_TRUE(app.InitializeChecked(errors));

    EXPECT_TRUE(app.IsInitialized()) << "Application should not be initialized";
    EXPECT_NE(0, app.MajorVersion()) << "Version should be initialized";
    EXPECT_NE("", app.VersionString()) << "Version should be initialized";
    EXPECT_TRUE(verbose);
}

TEST_F(ApplicationTest, InitializeWithApplicationParametersSpecifiedLong)
{
    SetupArgv({ "App", "--verbose" });
    bool verbose = false;
    Application app(argc, argv, { OptionEntry{"verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Verbose output", ""} });
    ErrorList errors;
    EXPECT_TRUE(app.InitializeChecked(errors));

    EXPECT_TRUE(app.IsInitialized()) << "Application should not be initialized";
    EXPECT_NE(0, app.MajorVersion()) << "Version should be initialized";
    EXPECT_NE("", app.VersionString()) << "Version should be initialized";
    EXPECT_TRUE(verbose);
}

TEST_F(ApplicationTest, Deinitialize)
{
    SetupArgv({ "App" });
    Application app(argc, argv);
    app.Initialize();
    app.Deinitialize();

    EXPECT_FALSE(app.IsInitialized()) << "Application should not be initialized";
    EXPECT_NE(0, app.MajorVersion()) << "Version should be initialized";
    EXPECT_NE("", app.VersionString()) << "Version should be initialized";
}

} // namespace Test
} // namespace GStreamer
