#ifndef TEST_GLUED_CURVE_TESTEXECUTION_H
#define TEST_GLUED_CURVE_TESTEXECUTION_H


#include "vector"
#include "string"

#include <DIPaCUS/derivates/Misc.h>
#include "gcurve/GluedCurveRange.h"

#include <gcurve/test/utils/CurvesExtractor.h>

namespace GCurve
{
    namespace Test
    {
        extern std::string projectDir;

        extern std::string IMAGE_INPUT_PATH;
        extern std::string IMAGE_OUTPUT_PATH;

        extern bool verbose;
        extern bool visualOutput;


        class TestExecution
        {
        private:
            const std::vector<std::string> imgFilenames = {"square.pgm"};
        public:
            TestExecution();
        };
    }
}

#endif //TEST_GLUED_CURVE_TESTEXECUTION_H