#include "gcurve/Range.h"

using namespace GCurve;

Range::Range(const DigitalSet& ds, unsigned int gcLength):gcLength(gcLength)
{
    const Domain& domain = ds.domain();
    kspace.init(domain.lowerBound(),domain.upperBound(),true);


    DIPaCUS::Misc::computeBoundaryCurve(mainCurve,ds);
    Utils::mInnerCurve(innerCurve,ds);
    Utils::mOuterCurve(outerCurve,ds);

    auto outMainPS = std::inserter(mainPS,mainPS.begin());
    auto outInnerPS = std::inserter(innerPS,innerPS.begin());
    auto outOuterPS = std::inserter(outerPS,outerPS.begin());

    Utils::mCurvePointels(outMainPS,kspace,mainCurve);
    Utils::mCurvePointels(outInnerPS,kspace,innerCurve);
    Utils::mCurvePointels(outOuterPS,kspace,outerCurve);

    auto outMainPC = std::inserter(mainPC,mainPC.begin());
    auto outInnerPC = std::inserter(innerPC,innerPC.begin());
    auto outOuterPC = std::inserter(outerPC,outerPC.begin());

    Utils::mPointelCirculator(outMainPC,kspace,mainCurve);
    Utils::mPointelCirculator(outInnerPC,kspace,innerCurve);
    Utils::mPointelCirculator(outOuterPC,kspace,outerCurve);

    generateSeeds();
}

Range::SCell Range::findLinkLinel(Point sourceCoord, Point targetCoord)
{
    SCell source = kspace.sCell(sourceCoord,false);
    auto scells = kspace.sUpperIncident(source);

    for(auto it=scells.begin();it!=scells.end();++it)
    {
        SCell potTarget = kspace.sDirectIncident(*it,*kspace.sDirs(*it));
        if(potTarget.preCell().coordinates==targetCoord)return *it;
    }

    throw std::runtime_error("Link linel not found!");
}

bool Range::checkSeed(const Seed& seed)
{
    if(seed.linkLinels.size()==0) return true;

    SCell linkLinel = seed.linkLinels[0];
    SCell firstIn = *seed.inCirculatorBegin;
    SCell lastOut = *(seed.outCirculatorEnd);
    Point linkLinelTarget = kspace.sDirectIncident(linkLinel,*kspace.sDirs(linkLinel)).preCell().coordinates;
    Point linkLinelSource = kspace.sIndirectIncident(linkLinel,*kspace.sDirs(linkLinel)).preCell().coordinates;

    //Link linel must not coincide with first linel of inCurve
    bool flag = linkLinel.preCell().coordinates!=firstIn.preCell().coordinates;
    //Link linel must not coincide with last linel of outCurve
    flag = flag && linkLinel.preCell().coordinates!=lastOut.preCell().coordinates;
    //A pointel must be visited at most twice

    if(!flag) return false;

    std::map<Point,int> pointelsDegree;
    Utils::visitPointels(pointelsDegree,kspace,seed.inCirculatorBegin,seed.inCirculatorEnd);
    Utils::visitPointels(pointelsDegree,kspace,seed.outCirculatorBegin,seed.outCirculatorEnd);
    Utils::visitPointels(pointelsDegree,kspace,seed.linkLinels.begin(),seed.linkLinels.end());

    for(auto it=pointelsDegree.begin();it!=pointelsDegree.end();++it)
    {
        if(it->second>2)
        {
            return false;
        }
    }

    return true;
}

void Range::createSeed(const CurveCirculator& mainCirc,
                       const CurveCirculator& auxCirc,
                       const Range::SCell& linkLinel,
                       Seed::SeedType seedType,
                       unsigned int totalLength)
{
    unsigned int outLength = 1;
    Seed seed(mainCirc,
              auxCirc,
                linkLinel,
            outLength,
            totalLength-outLength,
            seedType);

    if (checkSeed(seed))
        vectorOfSeeds.push_back(seed);

}

void Range::generateSeeds()
{
    Point neighborhood[4] = {Point(2,0),Point(-2,0),Point(0,2),Point(0,-2)};
    for(auto it=mainCurve.begin();it!=mainCurve.end();++it)
    {
        SCell target = kspace.sDirectIncident(*it,*kspace.sDirs(*it));
        SCell source = kspace.sIndirectIncident(*it,*kspace.sDirs(*it));

        Point sourceCoord = source.preCell().coordinates;
        Point targetCoord = target.preCell().coordinates;

        unsigned int totalLength = 2*gcLength;
        for(int i=0;i<4;++i)
        {
            Point np = targetCoord + neighborhood[i];
            if(innerPS.find(np)!=innerPS.end())
            {

                createSeed(mainPC[sourceCoord],innerPC[np],findLinkLinel(targetCoord, np),Seed::MainInner,totalLength);
                createSeed(innerPC[np]-1,mainPC[targetCoord],findLinkLinel(np, targetCoord),Seed::InnerMain,totalLength);

            }
            if(outerPS.find(np)!=outerPS.end())
            {
                createSeed(mainPC[sourceCoord],outerPC[np],findLinkLinel(targetCoord, np),Seed::MainOuter,totalLength);
                createSeed(outerPC[np]-1,mainPC[targetCoord],findLinkLinel(np, targetCoord),Seed::OuterMain,totalLength);

            }
        }
    }

    for(auto it=vectorOfSeeds.begin();it!=vectorOfSeeds.end();++it)
    {
        gluedCurveVector.push_back(GCurve::GluedCurve(*it));
    }

}