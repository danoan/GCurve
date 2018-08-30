#ifndef TEST_GLUED_CURVE_TESTUTILS_H
#define TEST_GLUED_CURVE_TESTUTILS_H

#include <gcurve/GluedCurve.h>
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/geometry/curves/StabbingCircleComputer.h"
#include "DGtal/geometry/curves/estimation/MostCenteredMaximalSegmentEstimator.h"

#include "DIPaCUS/derivates/Misc.h"


namespace Test
{
    struct CurvesExtractor
    {
        typedef DIPaCUS::Misc::ComputeBoundaryCurve::Curve Curve;
        typedef DIPaCUS::Misc::ComputeBoundaryCurve::Image2D Image2D;
        typedef DIPaCUS::Morphology::DigitalSet DigitalSet;

        typedef DGtal::Z2i::Domain Domain;

        CurvesExtractor(Curve& cI,
                        Curve&cE,
                        Domain& domain,
                        std::string imgPath);
    };

    struct EstimateCurvature
    {
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Curve Curve;

        typedef DGtal::Circulator<Curve::ConstIterator> CurveCirculator;

        typedef DGtal::functors::SCellToIncidentPoints<KSpace> AdapterFunctor;

        typedef GluedCurve::MyGluedLinelsIterator MyGluedLinelsIterator;

        typedef DGtal::ConstRangeAdapter< MyGluedLinelsIterator,
                AdapterFunctor,
                AdapterFunctor::Output > GluedRangeAdapter;


        typedef DGtal::StabbingCircleComputer<GluedRangeAdapter::ConstIterator> SegmentComputer;
        typedef DGtal::CurvatureFromDCAEstimator<SegmentComputer, false> SCEstimator;

        EstimateCurvature(std::vector<double>& estimations,
                          MyGluedLinelsIterator itb,
                          MyGluedLinelsIterator ite,
                          const Domain& domain);

        EstimateCurvature(std::vector<double>& estimations,
                          MyGluedLinelsIterator itb,
                          MyGluedLinelsIterator ite,
                          const KSpace& KImage);
    };

    class CheckDataWriter
    {
    public:

        CheckDataWriter(bool activeFlag);

        void init(std::string filepath);

        template<typename TIterator>
        void write(TIterator begin, TIterator end);

        template<typename Value>
        void write(Value v);

        void close();

    private:
        bool activeFlag;
        bool initialized,completed;
        int lines;

        std::string tempFilepath,finalFilepath;
        std::ofstream ofs;
    };

}

#include "testUtils.hpp"

#endif //TEST_GLUED_CURVE_TESTUTILS_H
