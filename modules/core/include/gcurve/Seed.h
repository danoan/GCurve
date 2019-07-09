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

        Seed(){}

        Seed(CurveCirculator outCirculator,
                       CurveCirculator inCirculator,
                       LinkLinel linkLinel,
                       unsigned int gcLength,
                       SeedType type):type(type)
        {
            initSeed(outCirculator,inCirculator,linkLinel,gcLength,gcLength,type);
        }

        Seed(CurveCirculator outCirculator,
             CurveCirculator inCirculator,
             LinkLinel linkLinel,
             unsigned int gcLengthOut,
             unsigned int gcLengthIn,
             SeedType type):type(type)
        {
            initSeed(outCirculator,inCirculator,linkLinel,gcLengthOut,gcLengthIn,type);
        }

        void initSeed(CurveCirculator outCirculator,
                      CurveCirculator inCirculator,
                      LinkLinel linkLinel,
                      unsigned int gcLengthOut,
                      unsigned int gcLengthIn,
                      SeedType type)
        {
            outCirculatorBegin = Utils::walkIterator(outCirculator,-(gcLengthOut-1) );
            outCirculatorEnd = outCirculator;

            inCirculatorBegin = inCirculator;
            inCirculatorEnd = Utils::walkIterator(inCirculator,gcLengthIn);

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
