// $Id: OverlapRemovalIndicesTtres.cxx 639409 2015-01-14 12:56:37Z simon $
#include "TtResonancesTools/OverlapRemovalIndicesTtres.h"
#include "TopEvent/EventTools.h"

#include <list>

namespace top {

  OverlapRemovalIndicesTtres::OverlapRemovalIndicesTtres() {
  }
  
  void OverlapRemovalIndicesTtres::overlapremoval(xAOD::ElectronContainer* el,
                                              xAOD::MuonContainer* mu,
                                              xAOD::JetContainer* jet,
                                              xAOD::JetContainer* ljet,
                                              std::shared_ptr<std::vector<unsigned int>> OUT_el,
                                              std::shared_ptr<std::vector<unsigned int>> OUT_mu,
                                              std::shared_ptr<std::vector<unsigned int>> OUT_jet,
                                              std::shared_ptr<std::vector<unsigned int>> OUT_ljet,
                                              const bool isLoose)                                                 
  {
      // Work internally with std::list
      // What passed the pre-overlap removal selection?
      std::vector<unsigned int> IN_el,IN_mu,IN_jet,IN_ljet;
      std::list<unsigned int> l_el,l_mu,l_jet,l_ljet;
      unsigned int index_el(0),index_mu(0),index_jet(0),index_ljet(0);
     
      std::string passTopCuts("");
      if (isLoose) {
        passTopCuts = "passPreORSelectionLoose";
      }
      if (!isLoose) {
        passTopCuts = "passPreORSelection";
      }     

      if (el) {
          for( auto x : *el ){
              if( x->auxdataConst< char >(passTopCuts) == 1 ){
                  IN_el.push_back(index_el);
                  l_el.push_back(index_el);
              }
              ++index_el;
          }
      }

      if (mu) {
          for( auto x : *mu ){
              if( x->auxdataConst< char >(passTopCuts) == 1 ){
                  IN_mu.push_back(index_mu);
                  l_mu.push_back(index_mu);
              }
              ++index_mu;
          }
      }

      if (jet) {
          for( auto x : *jet ){
              if( x->auxdataConst< char >(passTopCuts) == 1 ){
                  IN_jet.push_back(index_jet);
                  l_jet.push_back(index_jet);
              }
              ++index_jet;
          }
      }

      if (ljet) {
          for( auto x : *ljet ){
              if( x->auxdataConst< char >(passTopCuts) == 1 ){
                  IN_ljet.push_back(index_ljet);
                  l_ljet.push_back(index_ljet);
              }
              ++index_ljet;
          }
      }

      // Jets and Muons - remove muon with dR < 0.4
      for( auto j : IN_jet ){
          for( auto m : IN_mu ){
              if( top::deltaR( *(jet->at(j) ) , *(mu->at(m)) ) < 0.04 + 10e3/((mu->at(m))->pt()) ){
                  l_mu.remove( m );
              }
          }
      }

      // Save what's left of the std::lists into the OUT vectors;
      OUT_el->clear();
      OUT_mu->clear();
      OUT_jet->clear();
      OUT_ljet->clear();

      for( auto i : l_el  ){OUT_el->push_back(i); }
      for( auto i : l_mu  ){OUT_mu->push_back(i); }
      for( auto i : l_jet ){OUT_jet->push_back(i);}
      for( auto i : l_ljet ){OUT_ljet->push_back(i);}
  }

  void OverlapRemovalIndicesTtres::print(std::ostream& os) const {
      os << "fill in\n";
  }
}
