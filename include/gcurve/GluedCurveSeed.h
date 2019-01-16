#ifndef GCURVE_GLUEDCURVESEED_H
#define GCURVE_GLUEDCURVESEED_H

#include "GluedCurve.h"

namespace GCurve
{
    struct GluedCurveSeed
    {
        typedef Curve::ConstIterator CurveIterator;
        typedef DGtal::Circulator<CurveIterator> CurveCirculator;

        GluedCurveSeed(CurveCirculator c1It,
                       CurveCirculator c2It,
                       int gcLength,
                       GluedCurve::LinkType linkType,
                       GluedCurve::GluedCurveType gcType,
                       int numLinkLinels) : c1It(c1It),
                                            c2It(c2It),
                                            gcLength(gcLength),
                                            linkType(linkType),
                                            gcType(gcType),
                                            numLinkLinels(numLinkLinels) {};

        CurveCirculator c1It;
        CurveCirculator c2It;
        int gcLength;
        GluedCurve::LinkType linkType;
        GluedCurve::GluedCurveType gcType;
        int numLinkLinels;
    };
}

#endif //GCURVE_GLUEDCURVESEED_H
