
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


R__LOAD_LIBRARY(/sphenix/u/verkest/tim_signal_analysis/build/lib/libanalysis.so)





void Fun4All_analysis(const int nEvents = 1,
    const char * inputFile =
        // Let's take a look at run 668, which is -24 GeV/c secondary beam centered on EMCal tower 18.
        // More runs are produced in data production: https://wiki.bnl.gov/sPHENIX/index.php/2018_calorimeter_beam_test/Data_Production_and_Analysis#Production_output
		      "/sphenix/data/data02/sphenix/t1044/production/production_0506/beam_00002099-0000.root"
		      // "/sphenix/data/data02/sphenix/t1044/production/production_0306/beam_00000688-0000.root"
)
{

  //---------------
  // Load libraries
  //---------------
//  gSystem->Load("libPrototype4.so");
  gSystem->Load("libfun4all.so");
//  gSystem->Load("libPrototype4.so");
//  gSystem->Load("libPrototype4_io.so");

  // gSystem->Load("libanalysis.so");

  //libFun4All.so");	// framework + reco modules

  //---------------
  // Fun4All server
  //---------------

  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(0);

  //-------------- 
  // IO management
  //--------------

  // Hits file
  Fun4AllInputManager *hitsin = new Fun4AllDstInputManager("DSTin");
  hitsin->fileopen(inputFile);
//  hitsin->AddListFile(inputFile); // you can also choose this and give a list of DST file names in the file.
  se->registerInputManager(hitsin);

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
