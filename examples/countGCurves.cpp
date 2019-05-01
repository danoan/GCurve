#include <DGtal/io/readers/GenericReader.h>
#include <DIPaCUS/derivates/Misc.h>
#include <gcurve/GluedCurveRange.h>
#include "DIPaCUS/base/Shapes.h"


std::string projectDir = PROJECT_DIR;

using namespace DGtal::Z2i;

Domain curveExtractor(Curve& innerCurve, Curve& outerCurve)
{
    DigitalSet square = DIPaCUS::Shapes::square();
    const Domain &domain = square.domain();

    Domain dilatedDomain( domain.lowerBound() - DGtal::Z2i::Point(1,1), domain.upperBound()+DGtal::Z2i::Point(1,1));
    DigitalSet dilatedSquare(dilatedDomain);

    {
        using namespace DIPaCUS::Morphology;
        dilate(dilatedSquare,square,StructuringElement(StructuringElement::RECT,1),1);
    }

    DIPaCUS::Misc::computeBoundaryCurve(innerCurve,square);
    DIPaCUS::Misc::computeBoundaryCurve(outerCurve,dilatedSquare);

    return domain;
}

int main()
{
    Curve ci,ce;
    Domain domain = curveExtractor(ci,ce);

    KSpace KImage;
    KImage.init(domain.lowerBound(),domain.upperBound(),true);
    GluedCurveRange gcsr(KImage,5,ci.begin(),ci.end(),ce.begin(),ce.end());

    int gcTotal=0;
    std::for_each(gcsr.begin(),gcsr.end(),[&gcTotal](auto gcIt){++gcTotal;});
    std::cout << gcTotal << std::endl;


    return 0;
}
