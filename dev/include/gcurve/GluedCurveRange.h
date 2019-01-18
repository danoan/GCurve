#ifndef GLUED_CURVE_GCSEEDRANGE_H
#define GLUED_CURVE_GCSEEDRANGE_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/GridCurve.h>

#include "GluedLinelsIterator.h"
#include "GluedCurveSeed.h"
#include "GluedCurve.h"

namespace GCurve
{
    class GluedCurveRange
    {
    private:
        typedef DGtal::Z2i::Curve Curve;
        typedef Curve::ConstIterator CurveIterator;
        typedef DGtal::Z2i::KSpace::Point SCellPointelKey;
        typedef DGtal::Z2i::SCell SCell;
        typedef DGtal::Z2i::SCells SCells;

    public:
        typedef DGtal::Z2i::KSpace KSpace;
        typedef Curve::SCell LinkLinelType;

        typedef DGtal::Circulator<CurveIterator> CurveCirculator;

        typedef std::vector<GluedCurve>::const_iterator GluedCurveIterator;
        typedef std::vector<GluedCurveSeed>::const_iterator GluedCurveSeedIterator;
        typedef std::vector<LinkLinelType>::const_iterator GluedCurveLinkIterator;

    private:
        const static int POINTEL_GROUP_INTERNAL_CURVE = 0;
        const static int POINTEL_GROUP_EXTERNAL_CURVE = 1;


    public:

        GluedCurveRange(const KSpace &KImage,
                        int gcLength,
                        const CurveIterator ciItBegin,
                        const CurveIterator ciItEnd,
                        const CurveIterator ceItBegin,
                        const CurveIterator ceItEnd);

        GluedCurveIterator begin();
        GluedCurveIterator end();

        GluedCurveSeedIterator beginSeed() const { return gcsVector.begin();}
        GluedCurveSeedIterator endSeed() const { return gcsVector.end();}

        GluedCurveLinkIterator beginLink() const { return linkLinels.begin();}
        GluedCurveLinkIterator endLink() const { return linkLinels.end();}

    private:
        void identifyAlmostEnclosingLinels(std::set<SCell> &enclosingLinels,
                                           CurveCirculator externalCurveCirculator);

        bool enclosingPixelStack(std::queue<SCell> pixels,
                                 const std::queue<SCell> &linels);


        void alignIterator(CurveCirculator &internalCirculator,
                           SCell &connectorLinel);


        void setPointelGroup(const CurveCirculator &curveCirculator,
                             int pointelGroupId);

    private:
        int gcLength;
        std::vector<GluedCurve> gciVector;
        std::vector<GluedCurveSeed> gcsVector;
        std::vector<LinkLinelType> linkLinels;

    private:
        KSpace KImage;

        std::map<SCellPointelKey, int> pointelGroup;
        std::set<SCell> gridLinels;
    };
}
#endif //GLUED_CURVE_GCSEEDRANGE_H
