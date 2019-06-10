#include "gcurve/test/testCorrecteness.h"

using namespace GCurve::Test;

TestCorrecteness::TestCorrecteness()
{
    std::string checkDataFolder = CHECK_DATA_PATH + "/correcteness";
    GCAttributeWriter cdw(generateCheckData);

    int gcLength = 5;
    int gcTotal=0;

    std::string checkDataPath = checkDataFolder + "/square.txt";
    
    DigitalSet square = DIPaCUS::Shapes::square();
    const Domain& domain = square.domain();

    cdw.init(checkDataPath);
    GCAttributes checkGCAttr;
    if(!generateCheckData) checkGCAttr = read(checkDataPath);


    KSpace KImage;
    KImage.init(domain.lowerBound(),domain.upperBound(),true);

    Range gcr(square,gcLength);

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
