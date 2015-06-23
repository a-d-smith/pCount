/**
 * \file EvSel_mctruth.h
 *
 * \ingroup pCountPack
 * 
 * \brief Class def header for a class EvSel_mctruth
 *
 * @author hep
 */

/** \addtogroup pCountPack

    @{*/

#ifndef LARLITE_EVSEL_MCTRUTH_H
#define LARLITE_EVSEL_MCTRUTH_H

#include "Analysis/ana_base.h"
#include "DataFormat/mctrack.h"

namespace larlite {
  /**
     \class EvSel_mctruth
     User custom analysis class made by SHELL_USER_NAME
   */
  class EvSel_mctruth : public ana_base{
  
  public:

    /// Default constructor
    EvSel_mctruth(){ _name="EvSel_mctruth"; _fout=0;}

    /// Default destructor
    virtual ~EvSel_mctruth(){}

    /** IMPLEMENT in EvSel_mctruth.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in EvSel_mctruth.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in EvSel_mctruth.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();
    
    int loop_index;
    int protonTotal;
    int neutronTotal;
    int protons;
    int neutrons;
  protected:
    
  };
}
#endif
//**************************************************************************
// 
// For Analysis framework documentation, read Manual.pdf here:
//
// http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
//
//**************************************************************************

/** @} */ // end of doxygen group 
