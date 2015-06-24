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
    // Get track data of the event
    auto ev_mctracks = storage->get_data<event_mctrack>("mcreco");

    // Check the pointer is valid
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
    // Loop over all unique tracks and determine which particles 
    // are present
    for(auto track : uniqueTracks){
      // If the type of particle has not yet been seen, then add 
      // its PDG to the usedPDG vector. Then tally up the particles
      int thisPDG = track.PdgCode();
      bool isNew{true};
      for (unsigned int i=0;i<usedPDG.size();i++){
        if (usedPDG[i] == thisPDG){
          isNew = false;
          particles[i]++;
        }
      }
      if (isNew){
        usedPDG.push_back(thisPDG);
        particles.push_back(1);
      }
    } 
    // Create the histogram
    TCanvas *c = new TCanvas();
    TH1D *h = new TH1D("h","Particles Found",usedPDG.size(),0,usedPDG.size());

    // Fill the histrogram and label the bins 
    for (unsigned int i=0;i<usedPDG.size();i++){
      std::cout << "Found " << particles[i] << " with PDG " << usedPDG[i] << std::endl;
      for(int j=0;j<particles[i];j++){
        h->Fill(i);
      }
      std::string s = std::to_string(usedPDG[i]);
      char const *label = s.c_str();
      h->GetXaxis()->SetBinLabel(i+1,label);
    }

    // Draw and save
    h->Draw();
    c->SaveAs("ParticlesFound.eps");

    return true;
  }
}
#endif
