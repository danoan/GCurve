#include <DGtal/io/readers/GenericReader.h>
#include <DIPaCUS/derivates/Misc.h>
#include <gcurve/GluedCurveRange.h>

typedef DIPaCUS::Misc::ComputeBoundaryCurve::Image2D Image2D;

namespace Examples
{
    std::string projectDir = PROJECT_DIR;
    std::string inputImagesDir = projectDir + "/input_images";
}

int main()
{
    Image2D image = DGtal::GenericReader<Image2D>::import(Examples::inputImagesDir + "/square.pgm");
    Domain domain = image.domain();

    Image2D dilatedImage(domain);
    DigitalSet ds(domain);
    DIPaCUS::Representation::imageAsDigitalSet(ds,image);

    {
        using namespace DIPaCUS::Morphology;
        dilate(dilatedImage,ds,StructuringElement(StructuringElement::RECT,1),1);
    }

    Curve ci;
    DIPaCUS::Misc::ComputeBoundaryCurve(image,ci,100);

    Curve ce;
    DIPaCUS::Misc::ComputeBoundaryCurve(dilatedImage,ce,100);

    KSpace KImage;
    KImage.init(domain.lowerBound(),domain.upperBound(),true);
    GluedCurveRange gcsr(KImage,5,ci.begin(),ci.end(),ce.begin(),ce.end());

    int gcTotal=0;
    std::for_each(gcsr.begin(),gcsr.end(),[&gcTotal](auto gcIt){++gcTotal;});
    std::cout << gcTotal << std::endl;


    return 0;
}
