#include "gcurve/test/control/GCAttributeReader.h"

using namespace GCurve;

Test::GCAttributes Test::read(std::string filepath)
{
    std::ifstream ifs;
    int totalLines,gcTotal;
    std::vector<double> estimations;

    ifs.open(filepath);

    ifs >> totalLines;
    ifs >> gcTotal;

    double v;

    while(!(ifs >> v).eof())
    {
        estimations.push_back(v);
    }

    if((totalLines-2)!=estimations.size()) throw std::runtime_error("Incompatible sizes.");

    return GCAttributes(gcTotal,estimations);
}