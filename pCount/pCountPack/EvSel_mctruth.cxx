#ifndef LARLITE_EVSEL_MCTRUTH_CXX
#define LARLITE_EVSEL_MCTRUTH_CXX

#include "EvSel_mctruth.h"

namespace larlite {

  bool EvSel_mctruth::initialize() {
    
    loop_index = 1;
    candidates = 0;
    return true;
  }
  
  bool EvSel_mctruth::analyze(storage_manager* storage) {
    std::cout << "Event Number: " << loop_index << std::endl;
    
    /// Get track data
    std::vector<mctrack> tracks;
    auto ev_mctracks = storage->get_data<event_mctrack>("mcreco");

    if (!ev_mctracks){
        std::cout << "MCTrack pointer invalid! Exiting..." << std::endl;
        exit(1);
    }
    
    int protons{0};

    /// Loop over tracks in the event
    for(auto const& mctrack : *ev_mctracks){
        // Check for protons
        if (mctrack.PdgCode() == 2212){
	    tracks.push_back(mctrack);
            protons++;
	}
    }

    std::cout << protons << " protons" << std::endl;
    std::cout << "------------------" << std::endl;
    loop_index++;
    return true;
  }

  bool EvSel_mctruth::finalize() {
    std::cout << "Number of candidate events in sample: " << candidates << std::endl;
    return true;
  }

}
#endif
