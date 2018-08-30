#include "gcurve/GluedCurveRange.h"

GluedCurveRange::GluedCurveRange(const KSpace& KImage,
                         int gcLength,
                         const CurveIterator ciItBegin, 
                         const CurveIterator ciItEnd,
                         const CurveIterator ceItBegin,
                         const CurveIterator ceItEnd):gcLength(gcLength)
{
    CurveCirculator internalCurveCirculator(ciItBegin,
                                            ciItBegin,
                                            ciItEnd);

    CurveCirculator externalCurveCirculator(ceItBegin,
                                            ceItBegin,
                                            ceItEnd);    
    
    //The order is important when I consider superposed linels!!!!
    setPointelGroup(externalCurveCirculator,POINTEL_GROUP_EXTERNAL_CURVE);
    setPointelGroup(internalCurveCirculator,POINTEL_GROUP_INTERNAL_CURVE);


    CurveCirculator ie = externalCurveCirculator;
    CurveCirculator ii = internalCurveCirculator;

    //Connection edges creation
    if(DGtal::isNotEmpty(externalCurveCirculator,externalCurveCirculator)){

        std::set<SCell> enclosingLinels;
        identifyAlmostEnclosingLinels(enclosingLinels,
                                      externalCurveCirculator);

        do
        {
            SCell externalLinel = *ie;

            if(enclosingLinels.find(*ie)==enclosingLinels.end()) {

                SCell sourceExtLinel = KImage.sIndirectIncident(externalLinel,
                                                                *KImage.sDirs(externalLinel));    //Source
                SCell targetExtLinel = KImage.sDirectIncident(externalLinel, *KImage.sDirs(externalLinel));    //Target

                SCell mainSpel = KImage.sDirectIncident(*ie, KImage.sOrthDir(externalLinel));
                SCells neighborhood = KImage.sNeighborhood(mainSpel);


                for (auto itp = neighborhood.begin(); itp != neighborhood.end(); ++itp) {
                    SCells incidentEdges = KImage.sLowerIncident(*itp);

                    for (auto ite = incidentEdges.begin(); ite != incidentEdges.end(); ite++) {
                        SCell potentialConnectionLinel = *ite;

                        if (gridLinels.find(potentialConnectionLinel) != gridLinels.end()) continue;
                        SCell otherDirection(potentialConnectionLinel);
                        KImage.sSetSign(otherDirection, !KImage.sSign(otherDirection));
                        if (gridLinels.find(otherDirection) != gridLinels.end()) continue;

                        SCell p1 = KImage.sIndirectIncident(potentialConnectionLinel,
                                                            *KImage.sDirs(potentialConnectionLinel));    //Source
                        SCell p2 = KImage.sDirectIncident(potentialConnectionLinel,
                                                          *KImage.sDirs(potentialConnectionLinel));      //Target

                        if ((pointelGroup.find(p1.preCell().coordinates) == pointelGroup.end()) ||
                            (pointelGroup.find(p2.preCell().coordinates) == pointelGroup.end())) {
                            continue;   //There is a pointel which does not belong to any PointelGroup
                        }

                        if ((pointelGroup[p1.preCell().coordinates] == pointelGroup[p2.preCell().coordinates])) {
                            continue;   //Same PointelGroup. It is not a connection linel
                        }

                        bool from_intern_to_extern =
                                pointelGroup[p1.preCell().coordinates] == POINTEL_GROUP_INTERNAL_CURVE;

                        alignIterator(ii, potentialConnectionLinel);

                        if (from_intern_to_extern) {  //Internal Curve is Source

                            if (p2.preCell().coordinates != sourceExtLinel.preCell().coordinates) {
                                continue;   //Conectivity Error
                            }

                            GluedCurveSeed gcs(ii,
                                               ie,
                                               gcLength,
                                               GluedCurve::LinkType::INTERN_TO_EXTERN,
                                               GluedCurve::GluedCurveType::EXTENSION,
                                               1);

                            gcsVector.push_back(gcs);
                            linkLinels.push_back(potentialConnectionLinel);

                        } else {

                            if (p1.preCell().coordinates != targetExtLinel.preCell().coordinates) {
                                continue;   //Conectivity Error
                            }

                            GluedCurveSeed gcs(ie,
                                               ii,
                                               gcLength,
                                               GluedCurve::LinkType::EXTERN_TO_INTERN,
                                               GluedCurve::GluedCurveType::EXTENSION,
                                               1);

                            gcsVector.push_back(gcs);
                            linkLinels.push_back(potentialConnectionLinel);

                        }

                    }
                }
            }

            ++ie;
        }while(ie!=externalCurveCirculator);

        auto linkIt = linkLinels.begin();
        for(auto it=gcsVector.begin();it!=gcsVector.end();++it,++linkIt)
        {
            GluedCurve gc(it->c1It,it->c2It,it->gcLength,it->linkType,it->gcType,linkIt,linkIt+it->numLinkLinels);
            gciVector.push_back(gc);
        }
    }
}



bool GluedCurveRange::enclosingPixelStack(std::queue<SCell> pixels, const std::queue<SCell>& linels)
{
    SCell currentPixel;
    do
    {
        currentPixel = pixels.front();
        pixels.pop();
    }while(!pixels.empty() && currentPixel==pixels.front());

    return pixels.empty();
}


void GluedCurveRange::identifyAlmostEnclosingLinels(std::set<SCell>& setOfEnclosingLinels,
                                                                                    CurveCirculator externalCurveCirculator)
{
    std::queue<SCell> linels;
    std::queue<SCell> pixels;
    int k=3;
    CurveCirculator it = externalCurveCirculator;
    do
    {
        linels.push(*it);
        pixels.push( KImage.sDirectIncident(*it, KImage.sOrthDir(*it)) );
        k--;
        ++it;
    }while(k>0 && it!=externalCurveCirculator);


    while(it!=externalCurveCirculator)
    {
        if( enclosingPixelStack(pixels,linels) )
        {
            k=3;
            SCell enclosingLinel;
            while(k>0)
            {
                enclosingLinel = linels.front();
                linels.pop();
                linels.push(enclosingLinel);

                setOfEnclosingLinels.insert(enclosingLinel);
                --k;
            }
        }

        linels.push(*it);
        pixels.push(KImage.sDirectIncident(*it, KImage.sOrthDir(*it)));
        linels.pop();
        pixels.pop();

        ++it;
    }



};


void GluedCurveRange::alignIterator(CurveCirculator& internalCirculator,
                                SCell& connectorLinel)
{
    SCell p1 = KImage.sIndirectIncident(connectorLinel,*KImage.sDirs(connectorLinel));    //Source
    SCell p2 = KImage.sDirectIncident(connectorLinel,*KImage.sDirs(connectorLinel));      //Target

    bool from_intern_to_extern = pointelGroup[p1.preCell().coordinates]==POINTEL_GROUP_INTERNAL_CURVE;

    --internalCirculator;   //To not incur the risk to traverse all the scells.

    CurveCirculator endInternalCirculator = internalCirculator;
    if(from_intern_to_extern) {
        do {
            SCell pInt = KImage.sDirectIncident(*internalCirculator, *KImage.sDirs(*internalCirculator));
            if (pInt.preCell().coordinates == p1.preCell().coordinates)//Internal target equals Connector source.
            {
                break;
            }
            ++internalCirculator;
        } while (internalCirculator!=endInternalCirculator);
    }else{
        do {
            SCell pInt = KImage.sIndirectIncident(*internalCirculator, *KImage.sDirs(*internalCirculator));
            if (pInt.preCell().coordinates == p2.preCell().coordinates)//Internal source equals Connector target.
            {
                break;
            }
            ++internalCirculator;
        } while (internalCirculator!=endInternalCirculator);
    }


}


void GluedCurveRange::setPointelGroup(const CurveCirculator& curveCirculator,
                                  int pointelGroupId)
{
    if( DGtal::isNotEmpty(curveCirculator,curveCirculator) ) {
        CurveCirculator ic = curveCirculator;
        do {
            gridLinels.insert(*ic);
            SCells incidentPointels = KImage.sLowerIncident(*ic);

            SCell p = KImage.sDirectIncident( *ic, *KImage.sDirs(*ic) );   //Target
            pointelGroup[p.preCell().coordinates] = pointelGroupId;

            ++ic;
        } while (ic != curveCirculator);
    }

}

GluedCurveRange::GluedCurveIterator GluedCurveRange::begin()
{
    return gciVector.begin();
}

GluedCurveRange::GluedCurveIterator GluedCurveRange::end()
{
    return gciVector.end();
}