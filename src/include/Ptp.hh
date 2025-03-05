#ifndef __PTP_Ptp__
#define __PTP_Ptp__

#include <Config.hh>
#include <RAT/Rat.hh>
#include <RAT/AnyParse.hh>
#include <RAT/ProcBlockManager.hh>
#include <RAT/ProcAllocator.hh>
#include <RAT/GLG4Gen.hh>
#include <RAT/Factory.hh>
#include <GeoPtpFactory.hh>
//#include <DichroiconArrayFactory.hh>
#include <GeoPTPCoatingFactory.hh>
#include <HitmanProc.hh>
#include <NtupleProc.hh>
#include <LaserballGenerator.hh>
#include <string>

namespace PTP {

class Ptp : public RAT::Rat {
 public:
  Ptp(RAT::AnyParse* parser, int argc, char** argv);
};

}  // namespace PTP

#endif
