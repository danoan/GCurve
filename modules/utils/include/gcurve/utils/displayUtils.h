#ifndef GCURVE_DISPLAYUTILS_H
#define GCURVE_DISPLAYUTILS_H

#include <string>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>

namespace GCurve
{
    namespace Utils
    {
        typedef DGtal::Z2i::Curve Curve;
        typedef Curve::const_iterator CurveIterator;
        typedef DGtal::Board2D Board2D;
        typedef DGtal::Color Color;

        template<class TSCellIterator>
        void drawCurve(Board2D& board,
                       Color contourColor,
                       Color fillColor,
                       TSCellIterator begin,
                       TSCellIterator end);

        #include "displayUtils.hpp"
    }
}

#endif //GCURVE_DISPLAYUTILS_H
