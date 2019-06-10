#include "gcurve/utils/kspaceUtils.h"

namespace GCurve
{
    namespace Utils
    {
        void mOuterCurve(Curve& outerCurve, const DigitalSet& ds)
        {
            const Domain& domain = ds.domain();

            DigitalSet dilated(domain);
            {
                using namespace DIPaCUS::Morphology;
                dilate(dilated,ds,StructuringElement(StructuringElement::CROSS,1),1);
            }

            DIPaCUS::Misc::computeBoundaryCurve(outerCurve,dilated);
        }

        void mInnerCurve(Curve& innerCurve, const DigitalSet& ds)
        {
            const Domain& domain = ds.domain();

            DigitalSet eroded(domain);
            {
                using namespace DIPaCUS::Morphology;
                erode(eroded,ds,StructuringElement(StructuringElement::RECT,1),1);
            }

            DigitalSet boundary(domain);
            DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::FourNeighborhoodPredicate>(boundary,ds);

            Point neigh[4] = {Point(1,0),Point(-1,0),Point(0,1),Point(0,-1)};
            KSpace kspace;
            kspace.init(domain.lowerBound(),domain.upperBound(),true);
            for(auto it=boundary.begin();it!=boundary.end();++it)
            {
                int n=0;
                bool adjacent=false;
                Point adjInBoundary;
                for(int i=0;i<4;++i)
                {
                    Point np = *it + neigh[i];
                    if(eroded(np)) ++n;
                    if(n>2)
                    {
                        adjacent=true;
                        break;
                    }
                }

                if(!adjacent) eroded.insert(*it);
            }

            DIPaCUS::Misc::computeBoundaryCurve(innerCurve,eroded);
        }
    }
}