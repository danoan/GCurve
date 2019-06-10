#ifndef GCURVE_KSPACEUTILS_H
#define GCURVE_KSPACEUTILS_H

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Morphology.h>
#include <DIPaCUS/derivates/Misc.h>

namespace GCurve
{
    namespace Utils
    {
        typedef DGtal::Z2i::Curve Curve;
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Point Point;

        typedef Curve::ConstIterator CurveIterator;
        typedef DGtal::Circulator<CurveIterator> CurveCirculator;

        typedef std::map<Point,int> PointelsDegree;

        void mOuterCurve(Curve& outerCurve, const DigitalSet& ds);
        void mInnerCurve(Curve& innerCurve, const DigitalSet& ds);

        template<class TIterator>
        void visitPointels(PointelsDegree& pointelsDegree, const KSpace& kspace, TIterator begin, TIterator end);

        template<class TContainer>
        void mCurvePointels(std::insert_iterator<TContainer>& out,const KSpace& kspace, const Curve& curve);

        template<class TContainer>
        void mPointelCirculator(std::insert_iterator<TContainer>& out, const KSpace& kspace, const Curve& curve);

        #include "kspaceUtils.hpp"
    }
}

#endif //GCURVE_KSPACEUTILS_H
