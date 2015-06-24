#ifndef LARLITE_EVSEL_MCTRUTH_CXX
#define LARLITE_EVSEL_MCTRUTH_CXX

#include "EvSel_mctruth.h"
#include <sstream>


namespace larlite {

  // Initialization
  bool EvSel_mctruth::initialize() {    
    loop_index = 1;
    return true;
  }
  
  // This runs for each event in the supplied root file
  bool EvSel_mctruth::analyze(storage_manager* storage) {
    std::cout << "Event Number: " << loop_index << std::endl;
   
    // Get track data of the event
    auto ev_mctracks = storage->get_data<event_mctrack>("mcreco");

    if (!ev_mctracks){
        std::cout << "MCTrack pointer invalid! Exiting..." << std::endl;
        exit(1);
    }
        
    // Loop over tracks in the event
    for(auto const& mctrack : *ev_mctracks){
      // Determine if the track ID has already been counted
      unsigned int thisID = mctrack.TrackID();
      bool isNew{true};
      for (unsigned int ID : usedID){
        if (thisID == ID){
	  isNew = false;
	}
      }
      // If this is a new track add it to the vector
      // of unique tracks
      if (isNew){
       	usedID.push_back(thisID);
	uniqueTracks.push_back(mctrack);
      }
    }

    
    loop_index++;
    return true;
  }

  // This runs after all of the events have been loaded
  bool EvSel_mctruth::finalize() {
    /*
    TCanvas *c = new TCanvas();
    TH1D *h = new TH1D("h","h",100,-3,3);
    h->FillRandom("gaus",10000);
    h->Draw();
    c->SaveAs("test.eps");
    */
    
    
    // Loop over all unique tracks and determine which particles 
    // are present
    for(auto track : uniqueTracks){
      // If the type of particle has not yet been seen, then add 
      // its PDG to the usedPDG vector
      int thisPDG = track.PdgCode();
      bool isNew{true};
      for (int PDG : usedPDG){
        if (PDG == thisPDG){
          isNew = false;
        }
      }
      if (isNew){
        usedPDG.push_back(thisPDG);
      }
    }
    
    // Create the histogram
    TCanvas *c = new TCanvas();
    TH1D *h = new TH1D("h","Particles Found",usedPDG.size(),0,usedPDG.size());

    // Fill the histrogram
    for(auto track : uniqueTracks){      
      // Find the index of the particle (position in the usedPDG
      // vector)
      int thisPDG = track.PdgCode();
      int particleIndex{-1};
      for (unsigned int i=0;i<usedPDG.size();i++){
        if (usedPDG[i] == thisPDG){
          particleIndex = i;
        }
      }

      // Fill the histogram
      h->Fill(particleIndex);
    }
    
    // Label the bins 
    for (unsigned int i=0;i<usedPDG.size();i++){
      std::string s = std::to_string(usedPDG[i]);
      char const *label = s.c_str();
      h->GetXaxis()->SetBinLabel(i+1,label);
    }

    h->Draw();
    c->SaveAs("ParticlesFound.eps");

    return true;
  }
}
#endif
