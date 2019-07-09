#ifndef GLUED_CURVE_GLUEDCURVEITERATOR_H
#define GLUED_CURVE_GLUEDCURVEITERATOR_H

#include "DGtal/helpers/StdDefs.h"

namespace GCurve {
    template<typename CurveCirculator, typename LinkIteratorType>
    class CurrentIteratorType
    {
    private:
        typedef DGtal::Z2i::SCell SCell;

    public:
        CurrentIteratorType() : cit(),
                                lit(),
                                gridIterator(false) {};

        CurrentIteratorType(const CurrentIteratorType &other) : cit(other.cit),
                                                                lit(other.lit),
                                                                gridIterator(other.gridIterator) {};

        CurrentIteratorType &operator=(const CurrentIteratorType &other) {
            cit = other.cit;
            lit = other.lit;
            gridIterator = other.gridIterator;
            return *this;
        };

        bool operator==(const CurveCirculator &c) const {
            return gridIterator && c == cit;
        }

        bool operator==(const LinkIteratorType &l) const {
            return !gridIterator && l == lit;
        }

        bool operator==(const CurrentIteratorType &other) const {
            return gridIterator == other.gridIterator &&
                   ((gridIterator && cit == other.cit) || (!gridIterator && lit == other.lit));
        }

        void set(CurveCirculator &c) {
            gridIterator = true;
            cit = c;
        }

        void set(LinkIteratorType &l) {
            gridIterator = false;
            lit = l;
        }

        void operator++() {
            if (gridIterator) ++cit;
            else ++lit;
        }

        void operator--() {
            if (gridIterator) --cit;
            else --lit;
        }

        SCell operator*() const {
            if (gridIterator) return *cit;
            else return *lit;
        }

    private:
        CurveCirculator cit;
        LinkIteratorType lit;
        bool gridIterator;

    };

    template<typename TCurveCirculator, typename TLinkIteratorType>
    class Iterator
            : public boost::iterator_facade<
                    Iterator<TCurveCirculator, TLinkIteratorType>,
                    typename TCurveCirculator::value_type,
                    boost::bidirectional_traversal_tag
            > {
    private:
        typedef DGtal::Z2i::SCell SCell;

    public:
        typedef TLinkIteratorType LinkIteratorType;
        typedef TCurveCirculator CurveCirculator;

        Iterator();

        Iterator(LinkIteratorType itLb,
                            LinkIteratorType itLe,
                            CurveCirculator it1b,
                            CurveCirculator it1e,
                            CurveCirculator it2b,
                            CurveCirculator it2e,
                            bool theEnd = false);

        Iterator(const Iterator &other);

        Iterator<CurveCirculator, LinkIteratorType> &operator=(const Iterator &other);

        ~Iterator() { delete element; };

        inline SCell linkSurfel() { return *myItLb; };

        inline LinkIteratorType connectorsBegin() { return myItLb; };

        inline LinkIteratorType connectorsEnd() { return myItLe; };

        inline CurveCirculator curveSegment1End() { return myIt1e; };

        inline CurveCirculator curveSegment2Begin() { return myIt2b; };


    private:
        friend class boost::iterator_core_access;

        void increment();

        bool equal(const Iterator &other) const;

        typename CurveCirculator::value_type &dereference() const;

        void decrement();


        CurveCirculator myIt1b, myIt1e, myIt2b, myIt2e;
        LinkIteratorType myItLb, myItLe;

        CurrentIteratorType<CurveCirculator, LinkIteratorType> currentIterator;

        SCell *element;

        char iteratorStage;

        bool myFlagIsValid;
    };
    
    #include "Iterator.hpp"
}


#endif //GLUED_CURVE_GLUEDCURVEITERATOR_H
