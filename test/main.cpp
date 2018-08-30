#include <iostream>

#include "testExecution.h"
#include "testCorrecteness.h"

namespace Development
{
    bool makeConvexArcs = false;
}

namespace Test
{
    std::string projectDir = std::string(PROJECT_DIR);

    std::string IMAGE_INPUT_PATH = projectDir + "/input_images";
    std::string IMAGE_OUTPUT_PATH = projectDir + "/output_images";
    std::string CHECK_DATA_PATH = projectDir + "/check_data";

    bool verbose  = true;
    bool visualOutput = false;
    bool generateCheckData = false;
};

int main()
{
    std::cout << "Testing TestExecution" << std::endl;
    Test::TestExecution();

    std::cout << "Testing TestCorrecteness" << std::endl;
    Test::TestCorrecteness();

    return 0;
}