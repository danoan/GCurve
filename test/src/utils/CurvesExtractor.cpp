#include "gcurve/test/utils/CurvesExtractor.h"

using namespace GCurve::Test;

CurvesExtractor::CurvesExtractor(Curve& cI,
                                 Curve&cE,
                                 Domain& domain,
                                 std::string imgPath)
{
    Image2D imageI = DGtal::GenericReader<Image2D>::import(imgPath);
    DIPaCUS::Misc::ComputeBoundaryCurve(imageI,cI,100);

    domain = imageI.domain();

    Image2D imageE(imageI.domain());
    DigitalSet dsE(imageE.domain());
    DIPaCUS::Representation::imageAsDigitalSet(dsE,imageI);

    typedef DIPaCUS::Morphology::StructuringElement SE;
    SE se(SE::RECT,1);

    DIPaCUS::Morphology::dilate(imageE,dsE,se);

    DIPaCUS::Misc::ComputeBoundaryCurve(imageE,cE,100);
}


