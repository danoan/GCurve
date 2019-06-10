#include "gcurve/GluedCurve.h"

using namespace GCurve;

GluedCurve::GluedCurve(const Seed& seed):seed(seed)
{
    itBegin =  GluedCurve::MyGluedLinelsIterator (seed.linkLinels.begin(),
                                                  seed.linkLinels.end()-1,
                                                  seed.outCirculatorBegin,
                                                  seed.outCirculatorEnd,
                                                  seed.inCirculatorBegin,
                                                  seed.inCirculatorEnd,
                                                  false);

    itEnd =  GluedCurve::MyGluedLinelsIterator (seed.linkLinels.begin(),
                                                seed.linkLinels.end()-1,
                                                seed.outCirculatorBegin,
                                                seed.outCirculatorEnd,
                                                seed.inCirculatorBegin,
                                                seed.inCirculatorEnd,
                                                true);
}

