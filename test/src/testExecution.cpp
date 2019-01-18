#include "gcurve/test/testExecution.h"

using namespace GCurve::Test;

TestExecution::TestExecution()
{
    int gcLength = 5;
    std::string imgFilename;
    std::string imgPath;
    for (auto it = imgFilenames.begin(); it != imgFilenames.end(); ++it) {
        imgFilename = *it;
        imgPath = Test::IMAGE_INPUT_PATH + "/" + imgFilename;

        Domain domain;
        Curve cI,cE;
        CurvesExtractor(cI,cE,domain,imgPath);

        KSpace KImage;
        KImage.init(domain.lowerBound(),domain.upperBound(),true);

        GluedCurveRange gcr(KImage,gcLength,cI.begin(),cI.end(),cE.begin(),cE.end());


        int size = 0;
        std::for_each(gcr.begin(),gcr.end(),[&size](auto it){size+=1;});

        if(verbose) std::cout << size << std::endl;

        assert(size>0);
    }
}
