#ifndef TEST_GLUED_CURVE_TESTEXECUTION_H
#define TEST_GLUED_CURVE_TESTEXECUTION_H


#include "vector"
#include "string"

#include <DIPaCUS/derivates/Misc.h>
#include "../../../../../modules/core/include/gcurve/Range.h"

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
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Curve Curve;
            typedef DGtal::Z2i::KSpace KSpace;
            typedef DGtal::Z2i::DigitalSet DigitalSet;

        public:
            TestExecution();
        };
    }
}

#endif //TEST_GLUED_CURVE_TESTEXECUTION_H