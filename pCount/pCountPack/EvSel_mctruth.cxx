#ifndef LARLITE_EVSEL_MCTRUTH_CXX
#define LARLITE_EVSEL_MCTRUTH_CXX

#include "EvSel_mctruth.h"

namespace larlite {

  bool EvSel_mctruth::initialize() {
    
    loop_index = 1;
    protonTotal = 0;
    neutronTotal = 0;
    return true;
  }
  
  bool EvSel_mctruth::analyze(storage_manager* storage) {
    std::cout << "Event Number: " << loop_index << std::endl;
    
    /// Get track data
    std::vector<mctrack> pTracks;
    std::vector<int> nTracksID;

    auto ev_mctracks = storage->get_data<event_mctrack>("mcreco");

    if (!ev_mctracks){
        std::cout << "MCTrack pointer invalid! Exiting..." << std::endl;
        exit(1);
    }
        
    protons  = 0;
    neutrons = 0;    

    /// Loop over tracks in the event
    for(auto const& mctrack : *ev_mctracks){
        /// Check for protons
        if (mctrack.PdgCode() == 2212){
	    pTracks.push_back(mctrack);
            protons++;
	}
    }


    /// Free neutron almost always decays to a proton and some
    // leptons. So loop over all proton tracks and check for a
    // neutron mother.
    
    for (auto track : pTracks){
	if (track.MotherPdgCode() == 2112){
            nTracksID.push_back(track.MotherTrackID());
 	    neutrons++;
	}
    }

    protonTotal += protons;
    neutronTotal += neutrons;

    std::cout << protons << " protons, " << neutrons << " neutrons" << std::endl;
    std::cout << "------------------" << std::endl;
    loop_index++;
    return true;
  }

  bool EvSel_mctruth::finalize() {
    std::cout << "Total protons found : " << protonTotal << std::endl
;
    std::cout << "Total neutrons found : " << neutronTotal << std::endl;
    return true;
  }

}
#endif
