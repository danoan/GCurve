#ifndef GLUED_CURVE_GCSEEDRANGE_H
#define GLUED_CURVE_GCSEEDRANGE_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/GridCurve.h>
#include <DIPaCUS/derivates/Misc.h>

#include "gcurve/utils/kspaceUtils.h"
#include "Iterator.h"
#include "Seed.h"
#include "GluedCurve.h"

namespace GCurve
{
    class Range
    {
    private:
        typedef DGtal::Z2i::Point Point;
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::KSpace KSpace;
        typedef std::set<Point> PointelSet;

        typedef DGtal::Z2i::Curve Curve;
        typedef Curve::SCell SCell;
        typedef Curve::ConstIterator CurveIterator;
        typedef DGtal::Circulator<CurveIterator> CurveCirculator;

        typedef std::vector<Seed> VectorSeed;
        typedef std::vector<GluedCurve> GluedCurveVector;

        typedef std::map<Point,CurveCirculator> PointelCirculator;
    public:
        typedef DGtal::Z2i::DigitalSet DigitalSet;

        typedef VectorSeed::const_iterator SeedIterator;
        typedef GluedCurveVector::const_iterator GluedCurveIterator;

    public:
        Range(const DigitalSet& ds, unsigned int gcLength);

        inline SeedIterator beginSeed() const{ return vectorOfSeeds.begin(); }
        inline SeedIterator endSeed() const{ return vectorOfSeeds.end(); }

        inline GluedCurveIterator begin() const{ return gluedCurveVector.begin(); }
        inline GluedCurveIterator end() const{ return gluedCurveVector.end(); }


    private:
        SCell findLinkLinel(Point sourceCoord, Point targetCoord);
        bool checkSeed(const Seed& seed);
        void generateSeeds();
        void createSeed(const CurveCirculator& mainCirc,
                        const CurveCirculator& auxCirc,
                        const Range::SCell& linkLinel,
                        Seed::SeedType seedType,
                        unsigned int totalLength);

    public:
        KSpace kspace;
        unsigned int gcLength;

        Curve mainCurve;
        Curve innerCurve;
        Curve outerCurve;

        PointelSet mainPS;
        PointelSet innerPS;
        PointelSet outerPS;

        PointelCirculator mainPC;
        PointelCirculator innerPC;
        PointelCirculator outerPC;

        VectorSeed vectorOfSeeds;
        GluedCurveVector gluedCurveVector;
    };
}
#endif //GLUED_CURVE_GCSEEDRANGE_H
