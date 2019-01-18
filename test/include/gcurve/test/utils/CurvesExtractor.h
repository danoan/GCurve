#ifndef GCURVE_CURVESEXTRACTOR_H
#define GCURVE_CURVESEXTRACTOR_H

#include <DIPaCUS/derivates/Misc.h>

namespace GCurve
{
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
    }
}

#endif //GCURVE_CURVESEXTRACTOR_H
