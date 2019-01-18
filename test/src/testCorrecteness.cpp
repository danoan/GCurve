#include "gcurve/test/testCorrecteness.h"

using namespace GCurve::Test;

TestCorrecteness::TestCorrecteness()
{
    std::string checkDataFolder = CHECK_DATA_PATH + "/correcteness";
    GCAttributeWriter cdw(generateCheckData);

    int gcLength = 5;
    int gcTotal=0;

    std::string imgFilename;
    std::string imgPath;
    std::string checkDataPath;
    for (auto it = imgFilenames.begin(); it != imgFilenames.end(); ++it) {
        imgFilename = *it;
        imgPath = Test::IMAGE_INPUT_PATH + "/" + imgFilename;
        checkDataPath = checkDataFolder + "/" + imgFilename + ".txt";

        cdw.init(checkDataPath);
        GCAttributes checkGCAttr;
        if(!generateCheckData) checkGCAttr = read(checkDataPath);

        Domain domain;
        Curve cI, cE;
        CurvesExtractor(cI, cE, domain, imgPath);

        KSpace KImage;
        KImage.init(domain.lowerBound(),domain.upperBound(),true);

        GluedCurveRange gcr(KImage,gcLength,cI.begin(),cI.end(),cE.begin(),cE.end());

        std::for_each(gcr.begin(),gcr.end(),[&gcTotal](auto it){++gcTotal;});

        cdw.write(gcTotal);

        std::vector<double> estimations;
        for(GluedCurveIterator it = gcr.begin();it!=gcr.end();++it)
        {
            MyGluedLinelsIterator itB = it->begin();
            MyGluedLinelsIterator itE = it->end();

            EstimateCurvature(estimations,itB,itE,domain);
        }

        cdw.write(estimations.begin(),estimations.end());
        GCAttributes currentGCAttr = GCAttributes(gcTotal,estimations);

        if(!generateCheckData) assert(checkGCAttr==currentGCAttr);

        cdw.close();
    }

}
