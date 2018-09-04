#ifndef GLUED_CURVE_GCSEEDRANGE_H
#define GLUED_CURVE_GCSEEDRANGE_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/GridCurve.h>

#include "GluedLinelsIterator.h"
#include "GluedCurve.h"

namespace GCurve {
    class GluedCurveRange {
    public:
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Curve Curve;
        typedef Curve::SCell LinkLinelType;

        typedef Curve::ConstIterator CurveIterator;
        typedef DGtal::Circulator<CurveIterator> CurveCirculator;

        typedef std::vector<GluedCurve>::const_iterator GluedCurveIterator;

        typedef KSpace::Point SCellPointelKey;

    private:
        const static int POINTEL_GROUP_INTERNAL_CURVE = 0;
        const static int POINTEL_GROUP_EXTERNAL_CURVE = 1;

        struct GluedCurveSeed {
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


    public:

        GluedCurveRange(const KSpace &KImage,
                        int gcLength,
                        const CurveIterator ciItBegin,
                        const CurveIterator ciItEnd,
                        const CurveIterator ceItBegin,
                        const CurveIterator ceItEnd);

        GluedCurveIterator begin();

        GluedCurveIterator end();

    private:
        void identifyAlmostEnclosingLinels(std::set<SCell> &enclosingLinels,
                                           CurveCirculator externalCurveCirculator);

        bool enclosingPixelStack(std::queue<SCell> pixels,
                                 const std::queue<SCell> &linels);


        void alignIterator(CurveCirculator &internalCirculator,
                           SCell &connectorLinel);


        void setPointelGroup(const CurveCirculator &curveCirculator,
                             int pointelGroupId);


    public:
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
