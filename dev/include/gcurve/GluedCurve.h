#ifndef GLUED_CURVE_GLUEDCURVE_H
#define GLUED_CURVE_GLUEDCURVE_H

#include "GluedLinelsIterator.h"

namespace GCurve
{
    class GluedCurve
    {
    private:
        typedef DGtal::Z2i::Curve Curve;
        typedef Curve::SCell SCell;

    public:
        typedef DGtal::Circulator<Curve::ConstIterator> CurveCirculator;
        typedef std::vector<SCell>::const_iterator LinkLinelsIterator;

        typedef GluedLinelsIterator<CurveCirculator,LinkLinelsIterator> MyGluedLinelsIterator;

        enum LinkType{
            INTERN_TO_EXTERN,
            EXTERN_TO_INTERN,
        };

        enum GluedCurveType
        {
            SHORTCUT,
            EXTENSION
        };

    private:
        CurveCirculator walkCirculator(const CurveCirculator c, int w) const;

    public:

        GluedCurve(CurveCirculator c1It,
                   CurveCirculator c2It,
                   int gcLength,
                   LinkType linkType,
                   GluedCurveType gcType,
                   LinkLinelsIterator llItBegin,
                   LinkLinelsIterator llItEnd);


        const MyGluedLinelsIterator begin() const{ return itBegin; }
        const MyGluedLinelsIterator end() const{ return itEnd; }

        LinkType linkType(){return lt;}
        GluedCurveType gluedCurveType(){return gct;}

    private:

        LinkType lt;
        GluedCurveType gct;
        int gcLength;

        MyGluedLinelsIterator itBegin;
        MyGluedLinelsIterator itEnd;

    };
}
#endif //GLUED_CURVE_GLUEDCURVE_H
