#ifndef GCURVE_ITERATORUTILS_H
#define GCURVE_ITERATORUTILS_H

namespace GCurve
{
    namespace Utils
    {
        template<class TIterator>
        TIterator walkIterator(const TIterator c, int w)
        {
            TIterator cc = c;
            while(w!=0){
                w>0?cc++:cc--;
                w>0?w--:w++;
            }

            return cc;
        }
    }
}

#endif //GCURVE_ITERATORUTILS_H
