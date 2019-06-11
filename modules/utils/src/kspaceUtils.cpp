#include "gcurve/utils/kspaceUtils.h"
#include <DGtal/io/boards/Board2D.h>
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

            DGtal::Board2D board;
            board << eroded;
            board.saveEPS("eroded.eps");
            if(eroded.size()>0)
                DIPaCUS::Misc::computeBoundaryCurve(innerCurve,eroded);

        }
    }
}