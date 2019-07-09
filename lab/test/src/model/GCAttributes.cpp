#include "gcurve/test/model/GCAttributes.h"

using namespace GCurve::Test;

GCAttributes::GCAttributes(int gcTotal,
                           std::vector<double>& estimations):gcTotal(gcTotal),
                                                             estimations(estimations)
{
    std::sort(this->estimations.begin(),this->estimations.end());
};

bool GCAttributes::operator==(const GCAttributes& other) const
{
    if(other.gcTotal!=gcTotal) return false;

    double s1=0,s2=0;
    for(int i=0;i<estimations.size();++i)
    {
        s1+=estimations[i];
        s2+=other.estimations[i];
    }

    return s1==s2;
}