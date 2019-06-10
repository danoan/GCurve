#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>

#include <DIPaCUS/base/Shapes.h>

#include "gcurve/Range.h"
#include "gcurve/utils/displayUtils.h"



std::string projectDir = PROJECT_DIR;

using namespace DGtal::Z2i;


int main(int argc, char* argv[])
{
    std::string outputFilePath=projectDir+"/output/drawGCurves";
    boost::filesystem::create_directories(outputFilePath);

    int gcLength=5;
    if(argc>=2)
    {
        gcLength = std::atoi( argv[1] );
    }


    DigitalSet square = DIPaCUS::Shapes::square();
    const Domain &domain = square.domain();

    KSpace KImage;
    KImage.init(domain.lowerBound(),domain.upperBound(),true);

    DGtal::Board2D board;
    GCurve::Range gcRange(square,gcLength);

    int gcCount=0;
    for(auto itGC=gcRange.begin();itGC!=gcRange.end();++itGC,++gcCount)
    {
        Utils::drawCurve(board,
                DGtal::Color::Black,
                DGtal::Color::Silver,
                itGC->seed.inCirculatorBegin,
                itGC->seed.inCirculatorEnd);

        Utils::drawCurve(board,
                DGtal::Color::Black,
                         DGtal::Color::Silver,
                         itGC->seed.outCirculatorBegin,
                         itGC->seed.outCirculatorEnd);

        Utils::drawCurve(board,
                DGtal::Color::Black,
                         DGtal::Color::Red,
                         itGC->begin(),
                         itGC->end());

        board.saveSVG( (outputFilePath+"/"+std::to_string(gcCount)+".svg").c_str());
    }
}