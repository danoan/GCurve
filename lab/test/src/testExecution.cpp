#include "gcurve/test/testExecution.h"

using namespace GCurve::Test;

TestExecution::TestExecution()
{
    int gcLength = 5;
    DigitalSet square = DIPaCUS::Shapes::square();
    const Domain& domain = square.domain();

    KSpace KImage;
    KImage.init(domain.lowerBound(),domain.upperBound(),true);

    GCurve::Range gcr(square,gcLength);

    int size = 0;
    std::for_each(gcr.begin(),gcr.end(),[&size](auto it){size+=1;});

    if(verbose) std::cout << size << std::endl;

    assert(size>0);

    DGtal::Z2i::Curve curve;
    for(auto it=gcr.begin();it!=gcr.end();++it)
    {
        curve.initFromSCellsRange(it->begin(),it->end());
    }


}
