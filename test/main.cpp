#include <iostream>

#include "gcurve/test/testExecution.h"
#include "gcurve/test/testCorrecteness.h"


namespace GCurve
{
    namespace Test
    {
        std::string projectDir = std::string(PROJECT_DIR);

        std::string IMAGE_INPUT_PATH = projectDir + "/input_images";
        std::string IMAGE_OUTPUT_PATH = projectDir + "/output_images";
        std::string CHECK_DATA_PATH = projectDir + "/check_data";

        bool verbose  = true;
        bool visualOutput = false;
        bool generateCheckData = false;
    }
};

using namespace GCurve::Test;

int main()
{
    std::cout << "Testing TestExecution" << std::endl;
    TestExecution();

    std::cout << "Testing TestCorrecteness" << std::endl;
    TestCorrecteness();

    return 0;
}