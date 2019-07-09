#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/io/readers/GenericReader.h>

#include <DIPaCUS/base/Shapes.h>

#include "gcurve/Range.h"
#include "gcurve/utils/displayUtils.h"

std::string projectDir = PROJECT_DIR;

using namespace GCurve;
using namespace DGtal::Z2i;

void usage(int argc, char* argv[])
{
    std::cerr << "Usage: " << argv[0] << "\n"
            << "[-l Glued curve length]\n"
            << "[-S Shape (rectangle, imagePath)]\n";
}

struct InputData
{
    enum ShapeType{Rectangle,UserDefined};

    InputData(){
        gcLength = 5;
        shapeType = ShapeType::Rectangle;
    }

    int gcLength;
    ShapeType shapeType;
    std::string inputImagePath;
    std::string outputFolder;
};

InputData readInput(int argc, char* argv[])
{
    if(argc<2)
    {
        usage(argc,argv);
        exit(1);
    }

    InputData id;
    int opt;
    while( (opt=getopt(argc,argv,"l:S:"))!=-1 )
    {
        switch(opt)
        {
            case 'l':
            {
                id.gcLength = std::atoi(optarg);
                break;
            }
            case 'S':
            {
                if(strcmp(optarg,"rectangle")==0) id.shapeType = InputData::Rectangle;
                else
                {
                    id.shapeType = InputData::UserDefined;
                    id.inputImagePath = optarg;
                }
                break;
            }
            default:
            {
                usage(argc,argv);
                exit(1);
            }
        }
    }

    id.outputFolder = argv[optind++];
    return id;
}

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
    InputData id = readInput(argc,argv);
    boost::filesystem::create_directories(id.outputFolder);

    DigitalSet* myShapePtr;
    if(id.shapeType == InputData::Rectangle)
    {
        myShapePtr = new DigitalSet(rectangle(10,2));
    }else
    {
        typedef DIPaCUS::Representation::Image2D Image2D;
        Image2D image = DGtal::GenericReader<Image2D>::import(id.inputImagePath);
        myShapePtr = new DigitalSet( image.domain() );
        DIPaCUS::Representation::imageAsDigitalSet(*myShapePtr,image,1);
    }

    const DigitalSet& myShape = *myShapePtr;
    const Domain &domain = myShape.domain();

    KSpace KImage;
    KImage.init(domain.lowerBound(),domain.upperBound(),true);

    DGtal::Board2D board;
    GCurve::Range gcRange(myShape,id.gcLength);

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

        board.saveSVG( (id.outputFolder+"/"+std::to_string(gcCount)+".svg").c_str());
    }

    delete myShapePtr;

    return 0;
}