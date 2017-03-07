#include <gtest/gtest.h>

#include <cstdio>
#include <gstreamer++/application.h>

static const std::string ApplicationName = "GStreamerTest";

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests for " << ApplicationName << std::endl;
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    std::cout << std::flush;

    return result;
}
