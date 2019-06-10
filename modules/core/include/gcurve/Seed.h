#ifndef GCURVE_GLUEDCURVESEED_H
#define GCURVE_GLUEDCURVESEED_H

#include <vector>
#include <DGtal/helpers/StdDefs.h>
#include "gcurve/utils/iteratorUtils.h"

namespace GCurve
{
    struct Seed
    {
        typedef DGtal::Z2i::Curve Curve;
        typedef Curve::ConstIterator CurveIterator;
        typedef DGtal::Circulator<CurveIterator> CurveCirculator;

        typedef Curve::SCell LinkLinel;
        typedef std::vector<Curve::SCell> VectorLinkLinels;

        enum SeedType{MainInner,InnerMain,MainOuter,OuterMain};

        Seed(CurveCirculator outCirculator,
                       CurveCirculator inCirculator,
                       LinkLinel linkLinel,
                       unsigned int gcLength,
                       SeedType type):type(type)
        {
            outCirculatorBegin = Utils::walkIterator(outCirculator,-(gcLength-1) );
            outCirculatorEnd = outCirculator;

            inCirculatorBegin = inCirculator;
            inCirculatorEnd = Utils::walkIterator(inCirculator,gcLength);

            linkLinels.push_back(linkLinel);
        }


        CurveCirculator outCirculatorBegin;
        CurveCirculator outCirculatorEnd;

        CurveCirculator inCirculatorBegin;
        CurveCirculator inCirculatorEnd;

        VectorLinkLinels linkLinels;

        SeedType type;
    };
}

#endif //GCURVE_GLUEDCURVESEED_H
