#include "testCorrecteness.h"

using namespace Test;

TestCorrecteness::TestCorrecteness()
{
    std::string checkDataFolder = CHECK_DATA_PATH + "/correcteness";
    CheckDataWriter cdw(generateCheckData);

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
        if(!generateCheckData) checkGCAttr = GCAttributesReader(checkDataPath);

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

TestCorrecteness::GCAttributes::GCAttributes(int gcTotal,
                                             std::vector<double>& estimations):gcTotal(gcTotal),
                                                                               estimations(estimations)
{
    std::sort(this->estimations.begin(),this->estimations.end());
};

bool TestCorrecteness::GCAttributes::operator==(const GCAttributes& other) const
{
    if(other.gcTotal!=gcTotal) return false;

    for(int i=0;i<estimations.size();++i)
    {
        if(estimations[i]!=other.estimations[i]) return false;
    }

    return true;
}

TestCorrecteness::GCAttributes TestCorrecteness::GCAttributesReader(std::string filepath)
{
    std::ifstream ifs;
    int totalLines,gcTotal;
    std::vector<double> estimations;

    ifs.open(filepath);

    ifs >> totalLines;
    ifs >> gcTotal;

    double v;

    while(!(ifs >> v).eof())
    {
        estimations.push_back(v);
    }

    if((totalLines-2)!=estimations.size()) throw std::runtime_error("Incompatible sizes.");

    return GCAttributes(gcTotal,estimations);
}
