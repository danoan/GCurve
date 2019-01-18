#ifndef GCURVE_CURVESEXTRACTOR_H
#define GCURVE_CURVESEXTRACTOR_H

#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/derivates/Misc.h>

namespace GCurve
{
    namespace Test
    {
        struct CurvesExtractor
        {
            typedef DIPaCUS::Misc::ComputeBoundaryCurve::Curve Curve;
            typedef DIPaCUS::Morphology::DigitalSet DigitalSet;

            typedef DGtal::Z2i::Domain Domain;

            CurvesExtractor(Curve& cI,
                            Curve&cE,
                            Domain& domain,
                            const DigitalSet& ds);
        };
    }
}

#endif //GCURVE_CURVESEXTRACTOR_H
