#ifndef GCURVE_GCATTRIBUTES_H
#define GCURVE_GCATTRIBUTES_H

#include <algorithm>
#include <vector>

namespace GCurve
{
    namespace Test
    {
        struct GCAttributes
        {
            GCAttributes(){};

            GCAttributes(int gcTotal,
                         std::vector<double>& estimations);

            bool operator==(const GCAttributes& other) const;

            std::vector<double> estimations;
            int gcTotal;
        };
    }
}

#endif //GCURVE_GCATTRIBUTES_H
