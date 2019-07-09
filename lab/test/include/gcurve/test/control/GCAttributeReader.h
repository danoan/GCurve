#ifndef GCURVE_GCATTRIBUTEREADER_H
#define GCURVE_GCATTRIBUTEREADER_H

#include <fstream>
#include <stdexcept>

#include <gcurve/test/model/GCAttributes.h>

namespace GCurve
{
    namespace Test
    {
        GCAttributes read(std::string filepath);
    }
}

#endif //GCURVE_GCATTRIBUTEREADER_H
