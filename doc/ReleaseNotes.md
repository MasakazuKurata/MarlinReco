# v01-18

* 2017-03-30 Andre Sailer ([PR#4](https://github.com/iLCSoft/MarlinReco/pull/4))
  - RecoMCTruthLinker: move encoder initialisation from constructor to function body to avoid accessing encoding_string too early

* 2017-03-24 Emilia Leogrande ([PR#2](https://github.com/iLCSoft/MarlinReco/pull/2))
  - Replace ILDCellID0 to LCTrackerCellID

* 2017-04-12 Shaojun Lu ([PR#5](https://github.com/iLCSoft/MarlinReco/pull/5))
  - update to latest changes in LCIO
         - removed deprecated SimTrackerHit::setCellID
         - don't use assignment for CellIDDecoder

# v01-17

S. Lukic
  - Adding SiPID package to MarlinReco. 
    For the moment it contains the processor which calculates dE/dx for 
    a silicon tracker and writes it to the lcio file.
    Primarily intended for CLICdet but generally applicable. 
    DD4hep is used to access geometry.
    CMakeLists.txt in MarlinReco was adjusted. The package is added only
    if DD4hep and MarlinTrk are found.

M.Petric
  - fix in TruthVertexFinder
 
D. Jeans
  - copy calodigi documentation into Realistic package (+ a few changes to help latex compile)

S. Lu
  - comment out 'ADD_MARLINRECO_PKG( ./Clustering/BCalReco)' for solving
    '*** Break *** segmentation violation' at the end of Marlin run.
    ToDo: To ckeck which ilcsoft package use the same resource (maybe root resource). 



# v01-16

A.Ebrahimi
  - add package ErrorFlow
    - the ErrorFlow processor computes jet-specific energy uncertainty
      by summing up the uncertainty of individual particles clustered
      in a jet object.


# v01-15

M. Kurata
   - Include dEdx angular correction, which is a feedback from Sviatoslav
   - add PDF creation processor and steering file
   - add hadron type likelihood and probability
   - PIDTools: Adding PIDVariables and PIDParticles to trunk
   - assign 999 to likelihood when cannot perform PID

F. Gaede
   - introduced anonymous namespace to compile w/ -pedantic
   -  made compatible with c++11
   - removed -ansi -pedantic -Wno-long-long
   - build sub-package Relaistic only if DD4hep is found
   - added implementation of getExtension() - copied from DDMarlinPandora
  
D. Jeans
   - introduction of RealisticCaloDigi/Reco processors: refactorisation and cleaning up of ILDCaloDigi
   - gap corrections split off into BruteForceEcalGapFiller processor; change to setup of reco hit relations
   - fixed logic in determination of calibration by layer

M. Chera
   - fixed bug such that the processor now skips events with empty PFO collections without crashing
   

# v01-14

M. Berggren
   - Much ameliorated linking for clusters, taking back-scattering and
     decays in flight into account in a more correct way when finding
     what MCP to connect to a sim-hit.
     Work-around for the inverted meaning of the vertexIsNotEndpointOfParent
     method in Mokka. Set processor parameter  InvertedNonDestructiveInteractionLogic
     to activate the work-around (default is false)
     More consistent debugging. All levels from 0 to 9 used.

   - improved RecoMCTruthLinker
     Changed weight in hit<->mcparticle relation to the CaloHit energy (instead of the
     SimHit one). Also means the sim-hits not digitised (ie. without related CaloHit)
     are ignored. This also feeds through to the weights in the Cluster<->MCparticle
     relation, which should now be more correct: correct calibration factors applied
     for each hit.
     When doing the final relinking in problematic cases, explicitly check *only* back-scatters.
     Added MCP->cluster link for the case with the fixup of the missing truth-link for
     the LCAL in the DBD samples. Before only cluster->MCP was filled in this case.
   - Correted the true-particle to calorimeter-hit link for the case that
     the original true particle has been squeezed out by the cluster-linker,
     typically because it was created before the calorimeter, but after the
     last sensitive layer in the tracker.


  - AddClusterProperties:
     Use the PFO energy (not the cluster) when assign the PFO 4-momentum.
     Also add the sum of weights (=hit energy) to the cluster shape parameters.
     (In the DBD production, this is the same as the cluster energy, but it
     is not guaranteed to be the case).
   - Better/safer use of collection-parameters for indexing in sub-detector energy and shape-parameter arrays.
   - Different/simpler(?) calculation of Cov(4mom) in PFO.

F.Gaede 
 - changed log level for "processing event" from MESSAGE to DEBUG8
   in TPCDigiProcessor.cc
   -> use Statusmonitor instead



G.Wilson
   - added GammaGammaCandidateTruthFilter
    New processor to select those GammaGammaCandidates (fitted pairs of Pandora PFO photons) based 
    on MC information indicating actual parentage from a true pi0, eta or eta' meson decaying to gamma gamma.
    Output collections are called TrueGammaGammaPi0s etc.
    Cuts are made on the parent meson being prompt (production vertex distance < 10 cm), and the amount of the PFO 
    energy coming from the MC photon following similar criteria developed in ILDPerformance/pi0.
    This aspect will need some further investigation/tuning.


J.List
 - improve TrueJet:
 - First version that runs also over Higgs samples. No crash/obvious problem in several 1000s of events, 
   but more sophisticated checks pending. When running with full RecoMCTruthLink, estimate of of seen of true 
   energy needs fix, both on standard Whizard and Higgs samples


 M. Kurata
    - change overall structure for particle ID in LikelihoodPIDProcessor
    - change dEdx error estimation

 
M.Berggren:

    Added AddClusterProperties processor, a processor that adds cluster
    position and direction (w/uncertainties) to clusters, energy error 
    (if not already set) to clusters and 4-mom (w/ covariance)
    to neutral PFOs. Depends on a new MarlinUtil class (WeightedPoints3D),
    so for now, the processor is out-commented in CMakeLists.txt, to
    avoid problems if MarlinUtil isnot up-to-date !


G.Wilson 
  - update GammaGammaCandidateFinder
    - compute and fill ReconstructedParticle covariance matrix
  - Add GammaGammaSolutionFinder and DistilledPFOCreator processors
  - Add some steering options - and fit quality checks
  - Add 1st implementation of graph based solution finding in GammaGammaSolutionFinder - depends on BOOST

T.Calancha
  - The correlations of the energy (e) with x,y,z,e were stored in the wrong position of the matrix
    in FourMomentumCovMat. Thx to Ali Ebrahimi.

D.Jeans 
  -  electronics dynamic range applied before unfolding of PPD saturation
    in ILDCaloDigi.cc /  ScintillatorPpdDigi.cc

H.Sert
  - a separate algorithm was created for low P mu-pi ID in LikelihoodPIDProcessor.cc

 J.Tian
 - leave skipping or not an event without isolep to user in IsolatedLeptonTaggingProcessor.cc

T.Suehara
  -  bugfix on track charge in TrackToRecoParticleConverter

 J.List
  - added dummy error functions to ClusterShapesMR for MarlinPandora development, to be filled with life once proper calculations 
    are available
  - made SimpleFCalDigi use MarlinUtil:caloTypeFromString(_caloType)


# v01-13

  F.Gaede
   - renamed SimpleLHCalDigi to SimpleFCalDigi
   - deleted SimpleLCalDigi
   => old steering files need to be updated !!

  M. Berggren 
   - added  parameter FixLCalHits SimpleLHCalDigi in order to:
    - fix of the wrong xyz for hits in LCal. LCal CaloHits (collection LCAL) 
      are now within a few micron of their correct position. LCal SimCaloHits 
      (collection LumiCalCollection) still have the flawed xyz.

  J.List
  - updated SimpleLHCalDigi to include functionality fromm SimpleLCalDigi
   -> can be used for all fwd calos

  J.Tian
   - added new package:
     Analysis/OverlayRemoval

  H.Sert
  - new processor low momentum pi/mu separation:
    Analysis/PIDTools/LowMomentumMuPiSeparationPID_BDTG

  G.Wilson
  - new photon finder package: 
    Analysis/GammaGammaCandidateFinder
    - provides a 4-vector w/  mass-constrained fit (using MarlinKinfit  - new dependency )

  M Berggren
  - fixed links in RecoMCTruthLink/src/RecoMCTruthLinker.cc
  - full links in both directions (true->seen, seen->true) for PFOs, Tracks and Clusters.



# v01-12

  J.Tian
   - added new Analysis/IsolatedLeptonTagging
      MVA based isolated lepton finder

  T.Calancha
    - fixes for Analysis/FourMomentumCovMat
       - printout and read-only exception

  M.Kurata
  - update PIDTools for several kinds of likelihood calculation

  S.Bilokin
   - added Analysis/VertexChargeRecovery

  T.Suehara:
   - Analysis/TauFinder added

  F.Gaede

  - added copy of ClusterShapes from MarlinUtil 
    -> use "include "ClusterShapesMR.hh"
       and marlinreco::ClusterShapes
  - applied to ComputeShowerShapesProcessor.cc
  - eventuall changes should be merged back to MarlinUtil
  
  - fixed warning  -Wc++11-narrowing in TPCDigitizer




# v01-11

     LDCCaloDigi/ILDCaloDigi: D.Jeans & O. Hartbrich
     - improved realism of silicon and sintillator/PPD calorimeter hit digitisation
     - ScintillatorPpdDigi class defines PPD response model
     - default behaviour is no realism: must be switched on in steering file
     - added documentation (also described in LC-TOOL-2014-011)
     - can regroup the virtual cells of a scintillator strip
     
     Clustering/hybridEcalSplitter: D. Jeans
     - can deal with scintillator strips with >1 virtual cells

    - S.Bilokin: new package TruthVertexFinder added 
      ( see ./Analysis/TruthVertexFinder )

    - M.Berggren: added new packages TrueJet and TrueJet_Parser 
      (./Analysis/TrueJet, ./Analysis/TrueJet_Parser)

    - F.Gaede: add parameter DontEncodeSide to TPCDigiProcessor
        - allows to process old Mokka and new DD4hep based simulation 
       
    - F.Gaede: modified calo digitizers in CaloDigi/LDCCaloDigi:
      ILDCaloDigi, NewLDCCaloDigi, SimpleLCalDigi, SimpleLHCalDigi, SimpleMuonDigi
      added parameters
        CellIDLayerString, CellIDModuleString, CellIDStaveString
      to allow to switch between old cellId encoding string
      using K/K-1,M,S and new one using layer,module,sensor
      ( additionally added CellIDIndexIString, CellIDIndexJString to ILDCaloDigi)
  
    - C.Calancha: new package Analysis/FourMomentumCovMat
 
    - M.Kurata: new package Analysis/PIDTools: TPC track dEdx calculation, 
      Cluster shower profile extraction, and Likelihood Particle Identification

 
# v01-10
    - no release notes, use 
       svn -v log 
      to see changes ... 


# v01-09

     - improved SDHCAL digitizer (G.Grenier):
        charge simulation : simplifies Polya function. 
	Charge dispatching on pads : fix integration if using functions (slows the process)
	and add new dispatching using sum of Erf functions (recommended option)


# v01-08

 - John Marshall:
			Update fillECALGaps function, so that it remains identical to that implemented in NewLDCCaloDigi processor (i.e. copy the NewLDCCaloDigi updates from 9th Jan 2013).
			Apply HCAL "other" calibration constant to both ring and plug calorimeter hit types.


# v01-07
   
  - Manqi Ruan: added new clas G2D:
     Include G2CD, a general digitizer for gaseous hadron calorimeter. It takes 1mm simulated Hcal hits as input,
     and output digitized hits with tunable sell size. Efficiency and Multiplicity effects are also taken into 
     account, which can be adjusted in the steering file
  
  - J.List: fixed BCalTagEfficiency:
      adapted efficiency parametrisation for ECM=1TeV

  - Katsushige Coterra: updated NewLDCCaloDigi.cc
    for the Scintillator Strip Ecal reconstruction


# v01-06
   - updated IsolatedLeptonfinder (T.Tanabe)
     - LAL Lepton Finder included in IsolatedLeptonFinderProcessor

   - updated BCalTagEfficiency (J.List)
     - new option in BCalTagEfficiency: allows topick correct MCParticles from BCALMCTruthLink collection written by SGV

  - updated FPCCDClustering (D.Kamai)
     -  t.mori enable to difine pixel size for each layer.


  - fixed memory leak in BCalReco - fix provided by D.Jeans 
      - (loop variable in BCalReconstruction::Free3DArray )

# v01-05

   - BCalReco (A.Rosca)
     - in BCalReco.h reduce memory use: #define MAXNENTR 80000	      
     - introduced new variable EdepErr.
     - small changes to read new variable, EdepErr, from the background map.
     - fixed bug in SearchTowers().
     - write also empty BCal collections
     - fixed several programming flaws/reimplemented parts of code

   - BCalTagEfficiency (J.List)
     - removed local copy of TDR background map, updated README and bcal_ild_05_v05.xml
     - some minor clean-up of print statements, comments etc

# v01-04-02

    - BCalTagEfficiency:
        - threw out interpolation between BeamCal cells, introduced optional write-out of background map
        - uses LCRelationNavigator now, cleaned up example steering
        - write out also empty collections
        - added 3.5T background map and up to date example steering for ILD00

    - BCalReco:
        - improved calculation of Cartesian coordinates from cell position given
            in terms of ring/pad number.

    - RecoMCTruthLink:
        - exchanged ttrlcol and ctrlcol in makeSkim()
            ( will have no effect except code sanity )

    - LDCCaloDigi:
        - Bug fix to get output hits stored in output collection+increase speed of integration

    - FPCCDDigi:
        - t.mori enable to difine pixel size for each layer.


# v01-04-01
     - fixed TPCDigiProcessor :
        - added bfield correction factor to point resolution
          ( 4.0 / bField )

     - BCalRec (A.Rosca)
       - cleaned up code (removed unnecessary code)
       - introduced new default bg map file
       - enclosed code with  
             if( nHits > 0 ) {...}
         in order to prevent warning about missing CellIDEncoder string

       - fixed indentation of code (fg, using emacs defaults) (r4088)
         No code change, i.e. same code as r4087 (use this for diffs)

     - BCalTagEfficiency (J.List) 
       - veryfied unchanged performance on LoI samples (modulo a bug fix); steering flag for
         map format added


# v01-04

   - SiliconTracker, SiliconTrack_CLIC, TruthTracker: Corrected use of getPointOnCircle from HelixClass (MarlinUtil) 
     documentaion wrong said that a float[3] is required, when in fact a float[6] is needed. 

   - RecoMCTruthLinker: Improved Debug output for track mcparticle relations.
     			Fix for the case were no tracker collections are present.  

   - FPCCDDigitizer:    Bug fixed - process for the point on ladder edge.

   - BCalReco: 		Removed more uses of cout and cerr. Replaced with streamlog.
     			Corrected float instead of integer value for cluster position


# v01-03

   - added option to enable/disable output of root file containing histograms to BCalReco.cc
     (T.Tanabe)

   - fixed SIT parameters (new ZPlanarParameters )  in KinkFinder.cc (F.Gaede)

   - use streamlog for messages in EventShapes and SatoruJetFinder packages (T.Tanabe)

    - Analysis/RecoMCTruthLink: Corrected track <-> mcparticle weight regarding space points, nhits+=2. Reduce verbosity levels on MESSA
    GE.
    - Analysis/CLICPfoSelector: corrected logic to stop ihit90 index becoming negative.
    - removed/fixed several compiler/linker warnings


# v01-02

    - new package Analysis/IsolatedLeptonFinderProcessor
      (R. Yonamine, KEK, T. Tanabe, U.Tokiyo)
    - TrackDigi/FPCCDDigi/src/FPCCDDigitizer: bug fixed - unified the layer number in each function.
    - TrackDigi/TPCDigi/src/TPCDigiProcessor: use lcio::ILDDetID::barrel instead of 0
    - made compatible w/ clang++ compiler


# v01-01-01

    - bug fixes in Analysis/RecoMCTruthLink/src/RecoMCTruthLinker.cc:

        - The LCRelation Collections for TrackerHit to SimTrackerHits have been merged into a list of collections. Internally a single collection of LCRelations is created.
        - create track and cluster relations in any case as they are needed for the final recomctruth-link
	- The LCRelation Collections for TrackerHit to SimTrackerHits have been merged into a list of collections. 
	  Internally a single temporary collection of LCRelations is created.


# v01-01
      
      - RecoMCTruthLinker
        -  added mcTruthTrackLink: inverse relation from MCParticles to Tracks
           the weight will be the fraction of all sim-hits from the MCParticle
           that contributed to this track
        - changed weight definition for trackMCTruthLink:
          - weight is the fraction of all hits on the the track that have 
            contributions from this MCParticle
          - computed as sumSimHits_from_this_MCParticle/total_number_of_hits_on_track
             -> weight can be large than 1.0 (if more than one hit from an MCParticle
                would be used in a given layer (delta ray))
             -> this definition of weights is more accurate for defining the 'fake hit rate'
                as (1.-weight) in the case of many merged sim hits for a given track
         - changed steering logic, such that it can be more easily called for
           certain sub-tasks, eg. Track-MCTruth-Link only:
         - made the following output collections optional:
           trackMCTruthLink, clusterMCTruthLink, RecoMCTruthLink, calo-hit MCTruthLink, skimmed MCParticle
           -> collections won't be created if empty name specified (default)
         - removed options:
           OutputClusterRelation, OutputCalohitRelation, OutputTrackRelation
           they are now also based on name empty/not empty 
         - changed default for UseTrackerHitRelations to 'true'
            - print WARNING of set to false
           -- F.Gaede

      - LDCCaloDigi
          Implement use of LCIO calorimeter Hit step position for SDHCAL digitizer 
          (multiplicity simulation) and add parameters to the processor to better 
          control the digitization -- Gerald Grenier IPNL

      - TPCDigi
          Bug fix: added smearing of merged TPC hits
          (using rather large errors - which may have to be iterated on.)

       - BCalReconstruction
       	  Improved calibration (A.Rosca)

# v01-00-01


	- FPCCDDigi 
	  - Fixed setting of the cov matrix values.
	  - Modified to make link to mcp only for single particle event. 
	  - Chaged the algorithm to find pixels.

	- BCalReco
	  - Added reconstructed particle collection and check histograms.
	  - New parameter for bg map file: BackgroundFilename

# v01-00

	- General
	  - New release for preparation for the DBD.

	- Added hybridEcalSplitter (K. Kotera)

	- SiStripDigi: Processor to digitize and clusterize hits for the FTD subdtector
                       First release of the code, still missing full validation; (J. Duarte)

	- VTXDigiProcessor: corrected smearing to be along ladder, previously it was incorrectly perpendicular to the ladder, 
                            due to the use of the ladders phi angle instead of it angle of inclination

	- FPCCDDigitizer: Fixed bug in helix approximation.- in previous version the intersection between particle and ladder 
                          could be rotated to the opposite side.

        - RecoMCTruthLinker: Bug fix: protect against undefined mother pointer (T.Tanabe )
	  		     Modified to be able to use TrackerHit relations, though not yet the default. 
			     Enable by setting UseTrackerHitRelations true in steering file

	- TPCDigiProcessor: Corrected problem where hits from alternative z halves could be considered to be adjacent
	  		    Removed SimHits from RawHits and Used Relations. The deprecated feature to store them in the 
			    rawhits can be enabled by setting UseRawHitsToStoreSimhitPointer true. 

# v00-30

	- General
	  - Enabled build without cernlib/fortran (option MARLINRECO_FORTRAN=off) - e.g. for macos-64bit
	    sub packages (BrahmsTracking, Satoru, MarlinKinfit,...) that need cernlib will not be built

	- Clustering   
          - removed obsolete sub package ClusterCheater (ClusterCheater5_3 is newer)

          - deprecated TrackwiseClustering
            ( code still in repository, however not built by default )

          - added new sub package BCalReco 
            beam cal reconstruction (A.Rosca, DESY)


	- Pflow  
	  - deprecated Pflow package Wolf and TrackBasedPflow
            ( code still in repository, however not built by default )

	- CaloDigi
	  - added SimDigital processor to LDCCaloDigi 
            SDHCAL digitization (G.Grenier/R.Han, INPL)    

	- Analysis
	  - Removed MarlinKinfit processor

	  - RecoMCTruthLinker 
	    - Modification to allow Bremsstrahlung photons to be written to Skimmed list (off by default)

	- Tracking
	  - Use ILDCellID0 from lcio Util

	  - Removed deprecated setIsReferencePointPCA

	  - New processor FPCCDClustering.cc was added ( Daisuke Kamai )
        (FPCCDData and FPCCDPixelHit classes are in MarlinUtil )

	  - TPCDigiProcessor 
	    - Changed exception to warning for the case of points with the same x-y coordinates being passed to getPadTheta and getPadPhi. 
	      Corrected the check function which was previously using float == float, to use fabs(float-float) < tolerance. 
	      In this case tolerance has been set to a tenth of a micron


# v00-20

        - Tracking
          - MarlinTrackFit
           - Use double precision for the conversion from Tanagra to LC Track Parameters. Use of the HelixClass has been removed from the conversion.
          - FullLDCTracking
           - Use faster HelixClass::getDistanceToPoint where possible.
           - Improved dynamic mememory allocation
           - General clean-up and removal of redundant code.
          - LEPTracking 
           - Improved dynamic mememory allocation
           - Upper limit on track momentum now 2 TeV.
          - KinkFinder
           - Improved dynamic mememory allocation
           - Make sure prongDaughters[i] has entries.           
          - SiliconTracking
           - Protect against missing connection from SimTrackerHit to MCParticle.
           - Reducing maximum number of allowed FTD combinations
           - In case of many potential FTD hit combinations, iteratively adjust phi sectors for triplet formation to avoid long processing times 

        - TrackDigi
           - Improved dynamic mememory allocation

        - Analysis
          - MarlinKinfit
           - Added new test classes IterationScanner and ParameterScanner
           - Added NewFitterGSL.
          - CLICPfoSelector
           - Put in possibility of applying time of flight corrections to hit times: CorrectHitTimesForTimeOfFlight
           - Add one final cut to CLICPFOSelector to remove high energy neutral hadrons in the far forward region which are formed from mulitple background particles.
           - Improved monitoring of background/physics pfos.
           - Added simple analysis processor to loop over pfos separated in to "physics event" and background.
           - Create Selected PFO Collections as a subset of All PFOs.
          - RecoMCTruthLink
           - Use push_back instead of directly assigning entries to the vector, in case we run out of reserved space.
           - Output cluster truth linked collections for Clusters and Hits can only be created if there are clusters/hits.

# v00-19

 	  - added new sub package FPCCDDigi (Daisuke Kamai)

	  - Analysis/MarlinKinfit  (M.Beckmann) : 
            several updates, new RootTracer, name changes (PhotonFitObject ->
	    SimplePhotonFitObject, PhotonFitObjectPxyg -> ISRPhotonFitObject)

       - TPCDigitizer (S.Aplin) 
         - protected against accessing NULL pointer from getMCParticle
   	    - clean up unused variables and unneeded ifdefs
	    - fixed unsigned int == int comparison warnings
         - hit smearing (M.Thomson) 

       - NewFTDDigiProcessor
         - Add NewFTDTrackDigi with smearing for strips or Pixels, depending LayerID

       - ILDCaloDigi.cc ( M.Thomson )
         - Added new digitiser for ILD calorimeters with timing cuts and ability to 
           treat barrel and endcap differently

       - SimpleMuonDigi( M.Thomson) 
         - improve calibration of muon hits and set a maximum energy for a single hit (factor
	      two improvement in energy resolution). The defaults are appropriat e for ILD00       

       - MaterialDB
         - new version for CLIC CDR studies CLICCDRMaterialDB
         - made gear parameters for SIT/SET (support) layer thicknesses DoubleVec
         - increased the max number of tracking surfaces in F77, see fkparm.inc

       - BrahmsTracking
         - removed tpc Ionisation Potential in F77
         - increased the max number of tracking surfaces in F77, see fkparm.inc

       - FullLDCTracking ( M.Thomson )
         - modifications to reduce the number of split or "ghost" tracks

       - V0Finder (M.Thomson) 
         - improved checking to avoid false positives

 	    - BCalTagEfficiency.cc: fixed memory leak bug (C. Bartels)

        - RecoMCTruthLinker (M.Berggren)
         - added additional links (LCRelations) between ReconstructedParticles and Tracks and Clusters
         
          - code fixes (J.Engels) 
            - made gcc 4.4 compliant
	    - fixed various issues with gfortran and g2c
            - renamed get/setdEdx() to get/setEDep() in TrackDigitizers 
            - fixed cmake issues          


# v00-18
      - added new package Tracking/KinkFinder  (M.Thomson, J.Marshall)

      - moved sub-package BCalTagEfficiency from MarlinAna to ./Analysis

      - Tracking/V0Finder : fix for Lambda0bar (M.Thomson)

      - improved compatibility for gcc 4.x
        - g2c/gfortran in sl5 with gcc 4.1.1
        - fixed CaloDigi/LDCCaloDigi/src/CHT_helper.cc for gcc 4.4.3

     bug fixes:

      - CaloDigi/SimpleLHCalDigi.cc, CaloDigi/SimpleMuonDigi.cc,
         added missing output relation collection to the event

      - bug fixes in SimpleMuonDigi, (New)LDCCaloDigi wrt. to
        ecoding of calorimeter layout in CalorimeterHit::type 
        (was allways CHT::any)

      - fixed bug in TPCDigitizer with hit-MCParticle association

      - PFOID/src/PFOID.cc: addedd missing information
	that order of pdfs must be consistent with parameter
	EnergyBoundaries in parameter description   

      - TrackDigi/TPCDigi/src/TPCDigiProcessor.cc: fixed a bug in the
	logic when checking for hits from the same MCParticle 
        (last hit compared with itself)


# v00-17-02
     - made compatible with MacOS
     bug fixes: 
     - incorrect library version numbers
      


# v00-17
        removed dangerous revision of impact parameters 
        d0 and z0 in MarlinTrackFit.cc

# v00-16

     *	MarlinKinfit (boehmej, beckmann & K. Fujii)

      -	Global covariance matrix now also filled by NewtonFitter. 
      -	Added Tracer classes and access to global covariance matrix in
	BaseFitter, plus some bug fix in PhotonFitObjectPxyg and
	PhotonFitObject 

      -	Various bug fixes.

      -	Patches applied for compiling on mac osx.

	
     *	TrackDigi (gaede, aplin, raspereza, deMasi & fujii)

      -	VTXDigi, cluster parameter class for user extension of
	SimTrackerHits. 
      -	Introduced coordinate transform for direction
	vectors in VXDGeometry. New class for coordinate transform between
	ladder and lab frame. 
      -	Salt'n pepper noise hits with cluster
	parameters. 
      -	Only keep link to SimTrackerHit if MCParticle pointer
	is not null. 
      -	Evolved version of TPCDigi that provides additional functionality
	to deal with background. Coupled to the Mokka Sensitive Detector
	Driver. TPCSD03.cc. Plus considerable clean up.
      -	VTXDigitizer.cc, added possibility to store for each digitized
	tracker hit information on the fired pixels.
      -	Initial version of VTXBgClusters.
      -	ETDDigiProcessor, VTXDigiProcessor, patches applied for compiling 
	on mac osx. 

	
     * 	CaloDigi (thomson)
      -	Updates for digital and semi-digital HCAL readout of DHCAL 

	
     *	PFOID (aplin)

      -	Update the hcal calo type determintation to use Helper class from
	MarlinUtil for decoding/encoding lcio::CalorimeterHit types for
	the ILD. 


     *	ZFinder (thomson)

      -	New package for finding Z->l+l-.


     *	BrahmsTracking (aplin)

      -	Removed hardcoded cut of chi^2<300.


     * 	RecoMCTruthLink (gaede)

      -	Protect against MCParticle null pointers.

      -> see Changelog for details 

# v00-15
     * PFOID (A.Raspereza) 
       - Updated version of PFOID processor. Energy dependent scheme of 
         particle identification is implemented.
       - bug fix in Histogram.cc (array out of bounds)
       -  New pdf files for energy dependent particle ID procedure

# v00-14
   * modified calorimeter digitizers to encode CalorimeterHit types
     with CalorimeterHitType class from MarlinUtil ( need v00-13 or higher )

# v00-13
  * TrackDigi (F.Gaede)
    - ETDDigiProcessor/VTXDigiProcessor: 
      added active(SET)Layers parameter to mimic stereo layer readout by ignoring some layers

  * LDCCaloDigi  (M.Thomson)
     - SimpleMuonDigi:  fix default cell id encoding
     - SimpleLHCalDigi: new digitizer
     - NewLDCCaloDigi: improved Calo
       digitiser for ECAL and HCAL which writes out a single collection
       for each input collection to allow for possible CellID encoding

  * MarlinKinfit (M.Beckmann)
     - Replaced OPALFitter and NewtonFitter by OPALFitterGSL and
       NewtonFitterGSL. New PhotonFitObject to describe ISR photons.
       Several Bug Fixes.

  * bug fixes (J.Engels,S.Aplin)
    - removed compiler warnings in BrahmsTracking (cfortran.h,fkexts.inc)
    - CMake: bug fix: libg2c in 64 bit, added -m32 to global link flags
    - BrahmsTracking: fixed of bounds checking, buffer sizes


# v00-12-01
     - bug fix release:

      BrahmsTracking (S.Aplin)
       tflnks.F:  fixed a bug where a
	  number of TPC padrows between N*32+1 and N*32+4 caused division
	  by 0 when looking for hits in the last four padrows

       FullLDCTracking corrected the GEAR definition for the disk z positions

# v00-12-00

   * improved PFOID  (S.Aplin, A.Rasperezza) 
    - fixed to compile w/ gcc4.x 
    - output particle collection dropped - ParticleID object is assigned
      directly to ReconstructedParticle
    - improved documentation 

   TrackDigi/VTXDigi:
   * fixed bug in VTXNoiseHits (F.Gaede)

   * new processor CCDDigitizer (K.Harder)
     development version of vertex digitizier specific for CCD
     technology. written by Stefan Uebelacker (RAL) based on
     VTXDigitizer and on CCD digitizer code by Nick Sinev. not
     recommended for general use yet.

   * FullLDCTracking: New option for track fit included

   * made cmake 2.6 compliant
   * added 32 bit compatibility build option
   * added LIBRARY_DIRS

                                    
# v00-11-00

     * FullLDCTracking: (A.Raspereza)
        added cut on #Silicon hits if no TPC hits present - default: >=4

     * added code for PFOID  (M.Ohlerich et. al)
       particle id package
       -> experimental - does not compile and is not built into library

# v00-10-04
      
      * RecoMCTruthLinker (F.Gaede)
	  added paramater daughtersECutMeV for supressing low energy deltas od decays in flight

      * bug fixes and improvements in BrahmsTracking FullLDCTracking (S.Aplin)
        - splitted non-looping tracks based on hit-helix proximity 
        - corrected conversion of covariance matrix
        - added steering parameter AlwaysRunCurlKiller in BrahmsTracking
        - bug fix in  clear function of tkhitbank

        -> see Changelog for details 

# v00-10-03

	* bug fix SiliconTracking/LEPTrackingProcessor (S. Aplin)
          subdetectorHitNumbers  for ETD and SET hits

        * improved V0Finder (A.Raspereza)
          added cut on the mass of the candidate vertices

# v00-10-01

    * Tracking/FullLDCTracking/src/FullLDCTracking.cc: Si and TPC
      tracks are allowed to be merged if fit error = 0 ( proposed by
      Mark ).

# v00-10

    * new package Tracking/V0Finder  (A.Raspereza)
      processor to perform identification of neutral vertices,
      originating from photon conversions and decays of K0S and
      Lambda0

# v00-09-01
      fixed bug in RecoMCTruthLinker
	  and recover missing MCParticle link for Lcal clusters

# v00-09

    * RecoMCTruthLink:   (M.Beckmann, F.Gaede)
      - new processor MCTruthJetEnergy: adds colleciton parameter 'MCTruthJetEnergies'

    * TrackDigi/VTXDigitizer  (A.Raspereza)
      - bug fix for phi0 of gear::VXDParameters

    * BrahmsTracking/LEPTrackingProcessor 
      - bug fix w/ wrong TPCHit collection
      - changed default binning for the emoval of hits ala CurlKiller
      - bug fix for iteration of CurlKiller

# v00-08
     
    * TrackDigi: 
       - new processor VTXNoiseHits.cc   (F.Gaede)
       -> creates random noise hits with layer dependent density
          
       - added  ETDDigiProcessor (copy of FTDDigiProcessor w/simple
	  gaussian smearing in x-y )

    * improved LEPTracking (S.Aplin)	
      - error flag in LCIO event if patrec fails
      - produce only TPCTracks collection
      - functionality of CurlKiller moved into LEPTracking
      - improved log messages (streamlog/debug flags f77)
      - increased f77 array sizes for hits

    * improved FullLDCTracking (S.Aplin, M.Thomson)
       - correction for non looping split tracks
       - bug fixes

    
    * additional bug fixes

       -> see Changelog for details
 
# v00-07

     * improved FullLDCTracking (A.Raspereza)
       include SET and ETD in pattern recognition and fit

     * improved SiliconTracking (A.Raspereza, S.Aplin))
        - fixed/improved FTD geometry code 
        - improved efficiency in patrec
 
     * added LDCCaloDigi package (M.Thomson)
       calo digi code with gap corrections


     * additional bug fixes and code cleaning

       -> see Changelog for details

# v00-06
	 
    * improved LEPTracking and TPCDigi(S.Aplin)
	- reduced printout and moved cout to debug streamlog_out
        - corrected covariance matrix definition of TrackerHits
        - removed VTX and SIT Hits from LEPTracking

    * removed obsolete package VertexTracking (use SiliconTracking)

    * new package Analysis/RecoMCTruthLink (F.Gaede)
       - create link between ReconstructedParticles and MCParticles 
       - create skimmed MCparticle list

    * improved SiliconTracking (A.Raspereza)
       - reduced printout	
       - improved Silicon track finding efficiency (hit triplet fitting)
       - bug fix for correct assignment of left-over Silicon hits


     * additional bug fixes

       -> see Changelog for details

# v00-05-03

       bug fix release 

	* TrackDigi/TPCDigi/TPCDigiProcessor:    (S.Aplin)
	  - fixed several memory leaks 

	* Tracking/SiliconTracking/include/MaterialDB (A.Raspereza)
	  - added support structures for SIT
	  - included treatment of the first layer of heavy-weight Si for FTD
     	    detector


# v00-05-02
  
       bug fix release 

          !!! requires MarlinUtil v00-06 !!!!


	* TrackDigi/VTXDigi/VTXDigiProcessor: (C. Lynch)

	  - vertex hits are now smeared on ladders 
 
	* TrackDigi/TPCDigi/TPCDigiProcessor:    (S.Aplin)
          - new parametrization of r-phi and z resolution smearing (from LC-TPC group) 
          - bug fixes 
          - added expert check histograms (enable w/ -D EXPERTCHECKPLOTS)
          - covariance matrix of TrackerHit are now x,y,z (used to be cylindrical)

	* Analysis/MarlinKinfit:  (J.List) 
	  - added soft constraints
          - added more example fitters
          - bug fixes

# v00-05-01
       bug fix release

        - MarlinKinfit improved and new example (J.List) 

        - fixed LEPTracking for large #pad rows in TPC (S.Aplin)
          ( currently 512 pad rows are allowed - increase by
            setting the value of N32BITREG in padrow.inc )

        - dvips for documentation does not send to printer (J.Engels)

        - added simple digitizers SimpleLCalDigi and SimpleMuonDigi (by M.Thomson)

        - ...

# v00-05
       - new processor YThresh, calculates the yThresh variable(B. Hooberman)
         * in Analysis/EventShapes
         * see README and doxygen documentation
 
       - modified TPC digitization for new TPC driver (S.Aplin)
       - removed silicon tracking from BrahmsTracking

       - new package MarlinKinFit (J.List)
	 * Analysis/MarlinKinfit
         * kinematic fits with constraints
         * see doxygen documentation       

       - improved TrackBasedPFlow (O.Wendt)
	 * example steering file for the
	   Track-Based Particle Flow processor
	 * bug fixes and improved performance
         * LEPTracking: use TrackerHit::getCovMatrix for resolution

       - make consistent use of GEAR (K.Harder, C.Lynch) 
         * TrackDigi/VTXDigi: introduce gear
         * use global GEAR B field setting instead of TPC parameters setting in:
           Analysis/CheckPlots, Pflow/TrackBasedPFlow, Pflow/Wolf, Tracking/BrahmsTracking
         * updated example gear files (Bfield)
	 * Tracking/SiliconTracking: adjustments for new
	   GEAR file format as of Mokka v06-04-p02

       - improved FullLDCTracking (A.Raspereza)
         * some bugs fixed, e.g. wrong reference point
         * detailed users manual: doc/FullLDCTracking_Manual.pdf
         * consistent use of gear::BField 
       	 * TrackDigi/TPCDigi: Modified class for digitization of the
	   TPC hits. Spatial resolutions as well as parameters tpcPixRP and
	   tpcPixZ, representing the physical pad width and time binning
	   respectively, are passed to the processor as external parameters
	   (implemented by Clare Lynch)
         * example steering file
         * introduced various fit options
         * improved performance
         * digitization of laddered VXD detectors
  
       - improved code and cmake build files (J.Engels)
         * removed unused variables (compiler warnings)
         * install target for header files
         * fortran compiler flags and libg2c
            
       - improved documentation (F.Gaede)
	 * automatic generation of API doc (doxygen)


    -> see ChangeLog for details 

# v00-04
   - cmake is now default build tool:  (J.Engels)
        # edit BuildSetup.cmake as needed
        mkdir build ; cd build
        cmake -C ../BuildSetup.cmake ..
        make install
     -> creates plugin library $MarlinReco/lib/libMarlinReco.so
       

   - improved Tracking  (A.Raspereza)
       Extended version of TrackCheater, FullLDCTracking and SiliconTracking.
       The numbers of hits from different subdetectors are stored using
       TRACK:subdetectorHitNumbers. trackfit.F has been modified to
       account for curling tracks.

   -  Clustering/PhotonFinderKit/EMShowerFinder  (O.Wendt)
	  Processor to find electro-magnetic showers. 
          It is based on the KIT package and takes
	  only ECAL hits into account.	The output is a collection of
	  clusters in which the electro-magnetic shower are stored

   - TrackBasedPFlow (O.Wendt)
       + debugging and improvement of performance
       + included EMShowerFinder for improved efficiency to find
	 electromagnetic showers

   - bug fixes
       + made compliant with SL4 (gcc3.4) 
       +...

    -> see ChangeLog for details 

# v00-03
  - improved Full Tracking  (A.Raspereza)

  - initial version of TrackBasedPFA (O.Wendt)

  - PhotonFinderKit (P. Krstonosic)

  - added cmake support (epxerimental)
 

 for details see the ChangeLog file

