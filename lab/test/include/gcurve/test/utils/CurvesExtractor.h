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
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Curve Curve;
            typedef DGtal::Z2i::DigitalSet DigitalSet;



            CurvesExtractor(Curve& cI,
                            Curve&cE,
                            Domain& domain,
                            const DigitalSet& ds);
        };
    }
}

#endif //GCURVE_CURVESEXTRACTOR_H
