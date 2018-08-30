#ifndef TEST_GLUED_CURVE_TESTEXECUTION_H
#define TEST_GLUED_CURVE_TESTEXECUTION_H

#include "vector"
#include "string"

#include "gcurve/GluedCurveRange.h"

#include "testUtils.h"

namespace Test
{
    extern std::string projectDir;

    extern std::string IMAGE_INPUT_PATH;
    extern std::string IMAGE_OUTPUT_PATH;

    extern bool verbose;
    extern bool visualOutput;


    class TestExecution
    {
    public:
        typedef DIPaCUS::Misc::ComputeBoundaryCurve::Curve Curve;
        typedef DGtal::Circulator<Curve::ConstIterator> CurveCirculator;
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Domain Domain;

    private:
        const std::vector<std::string> imgFilenames = {"square.pgm"};
    public:
        TestExecution();
    };
}

#endif //TEST_GLUED_CURVE_TESTEXECUTION_H