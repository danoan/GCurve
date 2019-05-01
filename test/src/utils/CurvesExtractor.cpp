#include "gcurve/test/utils/CurvesExtractor.h"

using namespace GCurve::Test;

CurvesExtractor::CurvesExtractor(Curve& innerCurve,
                                 Curve& outerCurve,
                                 Domain& domain,
                                 const DigitalSet &ds)
{

    Domain dilatedDomain( ds.domain().lowerBound() - DGtal::Z2i::Point(1,1), ds.domain().upperBound()+DGtal::Z2i::Point(1,1));
    DigitalSet dilatedSquare(dilatedDomain);

    {
        using namespace DIPaCUS::Morphology;
        dilate(dilatedSquare,ds,StructuringElement(StructuringElement::RECT,1),1);
    }

    DIPaCUS::Misc::computeBoundaryCurve(innerCurve,ds);
    DIPaCUS::Misc::computeBoundaryCurve(outerCurve,dilatedSquare);

    domain = dilatedDomain;
}


