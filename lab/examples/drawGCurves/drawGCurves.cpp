#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>

#include <DIPaCUS/base/Shapes.h>

#include "gcurve/Range.h"
#include "gcurve/utils/displayUtils.h"

std::string projectDir = PROJECT_DIR;

using namespace GCurve;
using namespace DGtal::Z2i;


DigitalSet rectangle(int width, int height)
{
    Point border(5,5);
    Domain domain(Point(0,0)-border,Point(width,height)+border);
    DigitalSet ds(domain);
    for(int i=0;i<width;++i)
    {
        for(int j=0;j<height;++j)
        {
            ds.insert(Point(i,j));
        }
    }

    return ds;
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


    DigitalSet square = rectangle(10,2);//DIPaCUS::Shapes::square();
    const Domain &domain = square.domain();

    KSpace KImage;
    KImage.init(domain.lowerBound(),domain.upperBound(),true);

    DGtal::Board2D board;
    GCurve::Range gcRange(square,gcLength);

    int gcCount=0;
    for(auto itGC=gcRange.begin();itGC!=gcRange.end();++itGC,++gcCount)
    {
        board.clear();
        Utils::drawCurve(board,
                DGtal::Color::Black,
                DGtal::Color::Silver,
                itGC->seed.inCirculatorBegin,
                itGC->seed.inCirculatorBegin);

        Utils::drawCurve(board,
                DGtal::Color::Black,
                         DGtal::Color::Silver,
                         itGC->seed.outCirculatorBegin,
                         itGC->seed.outCirculatorBegin);

        Utils::drawCurve(board,
                DGtal::Color::Black,
                         DGtal::Color::Red,
                         itGC->begin(),
                         itGC->end());

        board.saveSVG( (outputFilePath+"/"+std::to_string(gcCount)+".svg").c_str());
    }
}