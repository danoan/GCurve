#include "kspaceUtils.h"

template<class TIterator>
void visitPointels(std::map<Point,int>& pointelsDegree, const KSpace& kspace, TIterator begin, TIterator end)
{
    for(auto it=begin;it!=end;++it)
    {
        auto pointels = kspace.sLowerIncident(*it);
        Point p1 = pointels[0].preCell().coordinates;
        Point p2 = pointels[1].preCell().coordinates;

        if( pointelsDegree.find( p1 )==pointelsDegree.end() ) pointelsDegree[ p1 ] = 0;
        ++pointelsDegree[ p1 ];

        if( pointelsDegree.find( p2 )==pointelsDegree.end() ) pointelsDegree[ p2 ] = 0;
        ++pointelsDegree[ p2 ];
    }
}

template<class TContainer>
void mCurvePointels(std::insert_iterator<TContainer>& out,const KSpace& kspace, const Curve& curve)
{
    for(auto it=curve.begin();it!=curve.end();++it)
    {
        (*out++) = kspace.sDirectIncident(*it,*kspace.sDirs(*it)).preCell().coordinates;
    }
}

template<class TContainer>
void mPointelCirculator(std::insert_iterator<TContainer>& out, const KSpace& kspace, const Curve& curve)
{
    if(curve.size()==0) return;

    CurveCirculator circ(curve.begin(),curve.begin(),curve.end());
    CurveCirculator it = circ;
    do
    {
        Point source = kspace.sIndirectIncident(*it,*kspace.sDirs(*it)).preCell().coordinates;
        (*out++) = std::pair<Point,CurveCirculator>(source, it);
        ++it;
    }while(it!=circ);
}