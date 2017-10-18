#ifndef Compute_dEdxProcessor_hh
#define Compute_dEdxProcessor_hh 1


#include <string>
#include <random>
#include <marlin/Processor.h>
#include <EVENT/LCCollection.h>

using namespace lcio ;
using namespace marlin ;

class Compute_dEdxProcessor : public Processor{
public:
  virtual Processor*  newProcessor() { return new Compute_dEdxProcessor ; }
  Compute_dEdxProcessor();
  virtual void init() ;
  virtual void processRunHeader( LCRunHeader* run);
  virtual void processEvent( LCEvent * evt );
  virtual void check( LCEvent * evt );
  virtual void end();
 
private:
  //ComputeddEdx *_mydEdx;
  float *CalculateEnergyLoss(TrackerHitVec& hitVec, Track* trk);  
  float getNormalization(double dedx, float hit, double trkcos);
  float getSmearing(float dEdx);

  float _TPC_inner;
  std::string _description;
  std::string _LDCTrackCollection;
  float _energyLossErrorTPC;
  LCCollection* _LDCCol;

  //for smearing
  std::random_device seed_gen;
  std::default_random_engine *engine;
  std::uniform_real_distribution<> dist;
  bool _isSmearing;
  float _smearingFactor;
  
};

#endif
