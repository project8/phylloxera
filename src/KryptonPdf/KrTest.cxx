// Your description goes here...

#include "Riostream.h"
#include "TROOT.h"

#include "KrTest.hh"
#include "RooAbsReal.h"
#include <math.h>
#include "TMath.h"

namespace Phylloxera
{
KrTest::KrTest(const char *name, const char *title,
               RooAbsReal &_KE) : RooAbsPdf(name, title),
                                  KE("KE", "KE", this, _KE)
{
}

KrTest::KrTest(const KrTest &other, const char *name) : RooAbsPdf(other, name),
                                                        KE("KE", this, other.KE)
{
}

Double_t KrTest::evaluate() const
{
    return TMath::Exp(-KE * KE);
}
}
