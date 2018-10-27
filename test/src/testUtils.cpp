#include "testUtils.h"

using namespace Test;

CurvesExtractor::CurvesExtractor(Curve& cI,
                                 Curve&cE,
                                 Domain& domain,
                                 std::string imgPath)
{
    Image2D imageI = DGtal::GenericReader<Image2D>::import(imgPath);
    DIPaCUS::Misc::ComputeBoundaryCurve(imageI,cI,100);

    domain = imageI.domain();

    Image2D imageE(imageI.domain());
    DigitalSet dsE(imageE.domain());
    DIPaCUS::Representation::imageAsDigitalSet(dsE,imageI);

    typedef DIPaCUS::Morphology::StructuringElement SE;
    SE se(SE::RECT,1);

    DIPaCUS::Morphology::dilate(imageE,dsE,se);

    DIPaCUS::Misc::ComputeBoundaryCurve(imageE,cE,100);
}



EstimateCurvature::EstimateCurvature(std::vector<double>& estimations,
                                     MyGluedLinelsIterator itb,
                                     MyGluedLinelsIterator ite,
                                     const Domain& domain)
{
    KSpace KImage;
    KImage.init(domain.lowerBound(), domain.upperBound(), true);
    EstimateCurvature(estimations, itb, ite, KImage);
}

EstimateCurvature::EstimateCurvature(std::vector<double>& estimations,
                                     MyGluedLinelsIterator itb,
                                     MyGluedLinelsIterator ite,
                                     const KSpace& KImage)
{
    AdapterFunctor myFunctor(KImage);
    GluedRangeAdapter range(itb,
                            ite,
                            myFunctor);

    SegmentComputer sc;
    SCEstimator f;

    DGtal::MostCenteredMaximalSegmentEstimator<SegmentComputer,SCEstimator> MCMDCACurvatureEstimator(sc,f);
    MCMDCACurvatureEstimator.init(1.0,
                                  range.begin(),
                                  range.end());

    MCMDCACurvatureEstimator.eval(range.begin(),
                                  range.end(),
                                  std::back_inserter(estimations));
}

CheckDataWriter::CheckDataWriter(bool activeFlag):activeFlag(activeFlag),
                                                  initialized(false),
                                                  completed(false)
{
    ofs.precision(20);
};

void CheckDataWriter::init(std::string filepath)
{
    if(!activeFlag) return;

    if(initialized && !completed) throw std::runtime_error("Initialization without finishing previous task.");

    lines = 0;
    finalFilepath = filepath;
    tempFilepath = filepath + ".temp";

    ofs.open(tempFilepath);
    initialized = true;
    completed = false;
}


void CheckDataWriter::close()
{
    if(!activeFlag) return;
    ofs.close();

    ofs.open(finalFilepath);
    ofs << lines+1 << std::endl;


    std::ifstream tempfs(tempFilepath);
    ofs << tempfs.rdbuf();

    tempfs.close();
    ofs.close();

    remove(tempFilepath.c_str());

    completed = true;
    initialized = false;
}