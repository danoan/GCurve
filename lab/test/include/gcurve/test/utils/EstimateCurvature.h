#ifndef GCURVE_ESTIMATECURVATURE_H
#define GCURVE_ESTIMATECURVATURE_H

#include <vector>
#include <DGtal/geometry/curves/GridCurve.h>
#include <DIPaCUS/derivates/Misc.h>
#include "gcurve/GluedCurve.h"
#include "gcurve/Range.h"

#include "DGtal/geometry/curves/StabbingCircleComputer.h"
#include "DGtal/geometry/curves/estimation/MostCenteredMaximalSegmentEstimator.h"

namespace GCurve
{
    namespace Test
    {
        struct EstimateCurvature
        {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::KSpace KSpace;

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

    }
}

#endif //GCURVE_ESTIMATECURVATURE_H
