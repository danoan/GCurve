#include "displayUtils.h"

template<class TSCellIterator>
void drawCurve(Board2D& board,
               Color contourColor,
               Color fillColor,
               TSCellIterator begin,
               TSCellIterator end)
{
    std::string curveStyle = begin->className() + "/Paving";

    board << DGtal::SetMode( begin->className(), "Paving" );
    board << DGtal::CustomStyle(curveStyle,new DGtal::CustomColors(contourColor,fillColor));

    auto it=begin;
    do{
        board << *it;
        ++it;
    }while(it!=end);

}