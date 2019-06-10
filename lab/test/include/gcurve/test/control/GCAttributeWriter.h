#ifndef GCURVE_GCATTRIBUTEWRITER_H
#define GCURVE_GCATTRIBUTEWRITER_H

#include <stdexcept>
#include <fstream>

namespace GCurve
{
    namespace Test
    {
        class GCAttributeWriter
        {
        public:

            GCAttributeWriter(bool activeFlag);

            void init(std::string filepath);

            template<typename TIterator>
            void write(TIterator begin, TIterator end);

            template<typename Value>
            void write(Value v);

            void close();

        private:
            bool activeFlag;
            bool initialized,completed;
            int lines;

            std::string tempFilepath,finalFilepath;
            std::ofstream ofs;
        };
    }
}

#include "GCAttributeWriter.hpp"

#endif //GCURVE_GCATTRIBUTEWRITER_H
