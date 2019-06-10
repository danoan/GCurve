#include <gcurve/test/utils/EstimateCurvature.h>

using namespace GCurve::Test;

EstimateCurvature::EstimateCurvature(std::vector<double>& estimations,
                                     MyGluedLinelsIterator itb,
                                     MyGluedLinelsIterator ite,
                                     const Domain& domain)
{
    KSpace KImage;
    KImage.init(domain.lowerBound(), domain.upperBound(), true);
    EstimateCurvature(estimations, itb, ite, KImage);
}

EstimateCurvature::EstimateCurvature(std::vector<double>& estimations,
                                     MyGluedLinelsIterator itb,
                                     MyGluedLinelsIterator ite,
                                     const KSpace& KImage)
{
    AdapterFunctor myFunctor(KImage);
    GluedRangeAdapter range(itb,
                            ite,
                            myFunctor);

    SegmentComputer sc;
    SCEstimator f;

    DGtal::MostCenteredMaximalSegmentEstimator<SegmentComputer,SCEstimator> MCMDCACurvatureEstimator(sc,f);
    MCMDCACurvatureEstimator.init(1.0,
                                  range.begin(),
                                  range.end());

    MCMDCACurvatureEstimator.eval(range.begin(),
                                  range.end(),
                                  std::back_inserter(estimations));
}