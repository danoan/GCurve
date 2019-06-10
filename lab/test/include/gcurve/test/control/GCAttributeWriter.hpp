#include "gcurve/test/model/GCAttributes.h"

using namespace GCurve::Test;

template<typename TIterator>
void GCAttributeWriter::write(TIterator begin, TIterator end)
{
    if(!activeFlag) return;

    for(TIterator it=begin;it!=end;++it)
    {
        ofs << *it << std::endl;
        ++lines;
    }
}

template<typename Value>
void GCAttributeWriter::write(Value v)
{
    if(!activeFlag) return;

    ofs << v << std::endl;
    ++lines;
}