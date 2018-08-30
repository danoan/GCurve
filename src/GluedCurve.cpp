#include "gcurve/GluedCurve.h"


GluedCurve::CurveCirculator GluedCurve::walkCirculator(const CurveCirculator c, int w) const
{
    CurveCirculator cc = c;
    while(w!=0){
        w>0?cc++:cc--;
        w>0?w--:w++;
    }

    return cc;
}


GluedCurve::GluedCurve(CurveCirculator c1It,
                       CurveCirculator c2It,
                       int gcLength,
                       LinkType linkType,
                       GluedCurveType gcType,
                       LinkLinelsIterator llItBegin,
                       LinkLinelsIterator llItEnd):lt(linkType),
                                                   gct(gcType),
                                                   gcLength(gcLength)
{
    CurveCirculator c1ItE = c1It;
    CurveCirculator c2ItB = c2It;

    CurveCirculator c1ItB = walkCirculator(c1ItE, -gcLength+1);
    CurveCirculator c2ItE = walkCirculator(c2ItB, gcLength);

    itBegin =  GluedCurve::MyGluedLinelsIterator (llItBegin,
                                                  llItEnd-1,
                                                  c1ItB,
                                                  c1ItE,
                                                  c2ItB,
                                                  c2ItE,
                                                  false);

    itEnd =  GluedCurve::MyGluedLinelsIterator (llItBegin,
                                                  llItEnd-1,
                                                  c1ItB,
                                                  c1ItE,
                                                  c2ItB,
                                                  c2ItE,
                                                  true);
}

