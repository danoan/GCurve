#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>
#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/components/Morphology.h>
#include <DIPaCUS/derivates/Misc.h>
#include <gcurve/GluedCurveRange.h>

#include "boost/filesystem.hpp"

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

    DIPaCUS::Misc::ComputeBoundaryCurve(square,innerCurve);
    DIPaCUS::Misc::ComputeBoundaryCurve(dilatedSquare,outerCurve);

    return domain;
}

void drawGluedCurve(std::string outputFilePath,
                    const Curve& innerCurve,
                    const Curve& outerCurve,
                    GCurve::GluedCurve::MyGluedLinelsIterator begin,
                    GCurve::GluedCurve::MyGluedLinelsIterator end)
{
    std::string gridCurvestyle = innerCurve.begin()->className() + "/Paving";
    std::string gluedCurvestyle = begin->className() + "/Paving";

    DGtal::Board2D board;
    board << DGtal::SetMode( innerCurve.begin()->className(), "Paving" );

    board << DGtal::CustomStyle(gridCurvestyle,new DGtal::CustomColors(DGtal::Color::Black,DGtal::Color::Gray));

    std::for_each(innerCurve.begin(),innerCurve.end(),[&board](DGtal::Z2i::SCell curveLinel) mutable{board << curveLinel;});
    std::for_each(outerCurve.begin(),outerCurve.end(),[&board](DGtal::Z2i::SCell curveLinel) mutable{board << curveLinel;});


    board << DGtal::CustomStyle(gluedCurvestyle,new DGtal::CustomColors(DGtal::Color::Black,DGtal::Color::Red));
    std::for_each(begin,end,[&board](DGtal::Z2i::SCell curveLinel) mutable{board << curveLinel;});

    board.saveEPS(outputFilePath.c_str());
}

int main(int argc, char* argv[])
{
    std::string outputFilePath=projectDir+"/output/drawGCurves";
    boost::filesystem::create_directories(outputFilePath);

    int gcLength=5;
    if(argc>=2)
    {
        gcLength = std::atoi( argv[1] );
    }


    DGtal::Z2i::Curve ci,ce;
    Domain domain = curveExtractor(ci,ce);

    KSpace KImage;
    KImage.init(domain.lowerBound(),domain.upperBound(),true);

    GCurve::GluedCurveRange gcRange(KImage,gcLength,ci.begin(),ci.end(),ce.begin(),ce.end());

    int gcCount=0;
    for(auto itGC=gcRange.begin();itGC!=gcRange.end();++itGC,++gcCount)
    {
        drawGluedCurve(outputFilePath+"/"+std::to_string(gcCount)+".eps",ci,ce,itGC->begin(),itGC->end());
    }
}