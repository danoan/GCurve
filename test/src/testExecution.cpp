#include "gcurve/test/testExecution.h"

using namespace GCurve::Test;

TestExecution::TestExecution()
{
    int gcLength = 5;
    DigitalSet square = DIPaCUS::Shapes::square();

    Domain domain;
    Curve cI,cE;
    CurvesExtractor(cI,cE,domain,square);

    KSpace KImage;
    KImage.init(domain.lowerBound(),domain.upperBound(),true);

    GluedCurveRange gcr(KImage,gcLength,cI.begin(),cI.end(),cE.begin(),cE.end());


    int size = 0;
    std::for_each(gcr.begin(),gcr.end(),[&size](auto it){size+=1;});

    if(verbose) std::cout << size << std::endl;

    assert(size>0);

}
