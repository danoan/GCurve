#ifndef GLUED_CURVE_GLUEDCURVE_H
#define GLUED_CURVE_GLUEDCURVE_H

#include "Iterator.h"
#include "Seed.h"

namespace GCurve
{
    class GluedCurve
    {
    private:
        typedef DGtal::Z2i::Curve Curve;
        typedef Curve::SCell SCell;

        typedef Curve::ConstIterator CurveIterator;
        typedef DGtal::Circulator<CurveIterator> CurveCirculator;

    public:
        typedef Iterator<Seed::CurveCirculator,Seed::VectorLinkLinels::const_iterator> MyGluedLinelsIterator;

    public:

        GluedCurve(const Seed& seed);

        const MyGluedLinelsIterator begin() const{ return itBegin; }
        const MyGluedLinelsIterator end() const{ return itEnd; }

    public:
        const Seed seed;
    private:
        MyGluedLinelsIterator itBegin;
        MyGluedLinelsIterator itEnd;

    };
}
#endif //GLUED_CURVE_GLUEDCURVE_H
