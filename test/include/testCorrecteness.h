#ifndef GLUED_CURVE_TESTCORRECTENESS_H
#define GLUED_CURVE_TESTCORRECTENESS_H

#include "string"
#include "vector"

#include "gcurve/GluedCurveRange.h"

#include "testUtils.h"

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
        typedef DIPaCUS::Misc::ComputeBoundaryCurve::Curve Curve;
        typedef DGtal::Circulator<Curve::ConstIterator> CurveCirculator;
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Domain Domain;

        typedef GluedCurveRange::GluedCurveIterator GluedCurveIterator;
        typedef GluedCurve::MyGluedLinelsIterator MyGluedLinelsIterator;


    private:
        struct GCAttributes
        {
            GCAttributes(){};

            GCAttributes(int gcTotal,
                         std::vector<double>& estimations);

            bool operator==(const GCAttributes& other) const;

            std::vector<double> estimations;
            int gcTotal;
        };

        const std::vector<std::string> imgFilenames = {"square.pgm"};

        GCAttributes GCAttributesReader(std::string filepath);

    public:
        TestCorrecteness();
    };
}

#endif //GLUED_CURVE_TESTCORRECTENESS_H
