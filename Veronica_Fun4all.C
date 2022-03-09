
/*!
 * \file Fun4All_analysis.C
 * \brief // this macro is part of analysis tutorial: https://wiki.bnl.gov/sPHENIX/index.php/2017_calorimeter_beam_test/Tutorial#Level_2:_formal_analysis_via_analysis_module
 * \author Jin Huang <jhuang@bnl.gov>
 * \version $Revision:   $
 * \date $Date: $
 */

#include <fun4all/Fun4AllServer.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllDstInputManager.h>
#include <G4_Jets.C>
#include <G4_HIJetReco.C>

R__LOAD_LIBRARY(libanalysis.so)

R__LOAD_LIBRARY(libfun4all.so)

void Veronica_Fun4all(const int nEvents = 1,
    vector<string> myInputLists = {"dst_bbc_g4hit.list", "dst_calo_cluster.list", "dst_calo_g4hit.list", "dst_tracks.list", "dst_trkr_g4hit.list", "dst_trkr_hit.list", "dst_truth.list", "dst_truth_g4hit.list", "dst_vertex.list", "g4hits.list"}
    )
{

  //---------------
  // Load libraries
  //---------------
  gSystem->Load("libg4dst");

  //---------------
  // Fun4All server
  //---------------

  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(1);

  //-------------- 
  // IO management
  //--------------

  //Add all required input files
  for (unsigned int i = 0; i < myInputLists.size(); ++i)
  {
    Fun4AllInputManager *infile = new Fun4AllDstInputManager("DSTin_" + to_string(i));
    infile->AddListFile(myInputLists[i]);
    se->registerInputManager(infile);
  }

  Jet_Reco();
  HIJetReco(); 

  //load your analysis module's lib

  //load your analysis module.
  // This one is an example defined in ../analysis/
  // SubsysReco 
   analysis* emcal_ana = new analysis(
       "test.root");
  se->registerSubsystem(emcal_ana);

  se->run(nEvents);
  se->End();
  
  std::cout << "All done" << std::endl;
  delete se;
  gSystem->Exit(0);
}
