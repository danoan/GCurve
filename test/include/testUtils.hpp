#include "testUtils.h"

using namespace Test;

template<typename TIterator>
void CheckDataWriter::write(TIterator begin, TIterator end)
{
    if(!activeFlag) return;

    for(TIterator it=begin;it!=end;++it)
    {
        ofs << *it << std::endl;
        ++lines;
    }
}

template<typename Value>
void CheckDataWriter::write(Value v)
{
    if(!activeFlag) return;

    ofs << v << std::endl;
    ++lines;
}