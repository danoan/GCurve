#ifndef GLUED_CURVE_TESTCORRECTENESS_H
#define GLUED_CURVE_TESTCORRECTENESS_H

#include "string"
#include "vector"

#include <DIPaCUS/derivates/Misc.h>
#include "gcurve/GluedCurveRange.h"

#include <gcurve/test/model/GCAttributes.h>
#include <gcurve/test/utils/CurvesExtractor.h>
#include <gcurve/test/utils/EstimateCurvature.h>
#include <gcurve/test/control/GCAttributeWriter.h>
#include <gcurve/test/control/GCAttributeReader.h>

namespace GCurve
{
    namespace Test
    {
        extern std::string projectDir;

        extern std::string IMAGE_INPUT_PATH;
        extern std::string IMAGE_OUTPUT_PATH;
        extern std::string CHECK_DATA_PATH;

        extern bool verbose;
        extern bool visualOutput;

        extern bool generateCheckData;

        class TestCorrecteness
        {
        public:
            typedef GluedCurveRange::GluedCurveIterator GluedCurveIterator;
            typedef GluedCurve::MyGluedLinelsIterator MyGluedLinelsIterator;

            const std::vector<std::string> imgFilenames = {"square.pgm"};

            GCAttributes GCAttributesReader(std::string filepath);

        public:
            TestCorrecteness();
        };
    }
}

#endif //GLUED_CURVE_TESTCORRECTENESS_H
