#include "CMGTools/Common/interface/PFJetFactory.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include <iostream>

using namespace std;

cmg::PFJetFactory::PFJetFactory(const edm::ParameterSet& ps):
  jetLabel_(ps.getParameter<edm::InputTag>("inputCollection")),
  baseJetFactory_(ps.getParameter<edm::ParameterSet>("baseJetFactory")), 
  puVariables_(ps.getParameter<edm::InputTag>("puVariables")), 
  puMvas_(ps.getParameter<std::vector<edm::InputTag> >("puMvas")), 
  puIds_(ps.getParameter<std::vector<edm::InputTag> >("puIds")), 
  useConstituents_(ps.getParameter<bool>("useConstituents")) 
{
  // PU discrimination
  // Make sure that MVAs and IDs are in synch and match expectations
  assert( puMvas_.size() <= cmg::PFJet::PuIdArray::static_size && 
	  puMvas_.size() == puIds_.size() );
  for(size_t ii=0; ii<puIds_.size(); ++ii){
    std::string mvaLabel = puMvas_[ii].instance();
    std::string idLabel = puIds_[ii].instance();
    mvaLabel = mvaLabel.substr(0, mvaLabel.find("Discriminant")); 
    idLabel  = idLabel.substr(0, idLabel.find("Id")); 
    assert( mvaLabel == idLabel );
    puNames_.push_back(mvaLabel);
  }
  std::cout<<"jet collection in the PFJetFactory = "<<jetLabel_<<std::endl;
}

cmg::PFJetFactory::event_ptr cmg::PFJetFactory::create(const edm::Event& iEvent, 
						       const edm::EventSetup&){
  
  edm::Handle<pat::JetCollection> jetCands;
  
  cmg::PFJetFactory::event_ptr result(new cmg::PFJetFactory::collection);
  iEvent.getByLabel(jetLabel_,jetCands);
  
  // Read PU identification inputs
  edm::Handle<edm::ValueMap<StoredPileupJetIdentifier> > puVariables;
  iEvent.getByLabel(puVariables_,puVariables);
  vector<edm::Handle<edm::ValueMap<int> > > puIds(puIds_.size());
  vector<edm::Handle<edm::ValueMap<float> > > puMvas(puMvas_.size());
  for(size_t ii=0; ii<puIds_.size(); ++ii ) {
    iEvent.getByLabel(puIds_[ii],puIds[ii]);
    iEvent.getByLabel(puMvas_[ii],puMvas[ii]);
  }
  
    
  long unsigned index = 0;
  for(pat::JetCollection::const_iterator mi = jetCands->begin();
      mi != jetCands->end(); ++mi, ++index ){

    pat::JetPtr jetPtr( jetCands, index ); 
    
    cmg::PFJet cmgjet( jetPtr );
    //set the basejet properties first
    baseJetFactory_.set(jetPtr,&cmgjet);
    
    const pat::Jet& jet = *mi;

    // THIS MUST BE CALLED AFTER baseJetFactory_.set!!
    setPFproperties(jet, &cmgjet, useConstituents_);
    
    // Fill PU discrimination variables
    cmgjet.rms_  = (*puVariables)[jetPtr].dR2Mean();
    cmgjet.beta_ = (*puVariables)[jetPtr].beta();
    for(size_t ii=0; ii<puIds_.size(); ++ii ) {
      cmgjet.puIdNames_[ii] = puNames_[ii];
      cmgjet.puIds_[ii]  = (*puIds[ii])[jetPtr];
      cmgjet.puMvas_[ii] = (*puMvas[ii])[jetPtr];
    } 

    result->push_back(cmgjet);
  }

  return result;
}

void cmg::PFJetFactory::setPFproperties(const pat::Jet& jet, cmg::PFJet* cmgjet, bool useConstituents_) const
{
    int nCharged = 0;
    int nPhotons = 0;
    int nNeutral = 0;
    int nElectrons = 0;
    int nMuons = 0;
    int nHFHad = 0;
    int nHFEM = 0;
  
    float energyCharged = 0;
    float energyPhotons = 0;
    float energyNeutral = 0;
    float energyElectrons = 0;
    float energyMuons = 0;
    float energyHFHad = 0;
    float energyHFEM = 0;

    float ptCharged = 0;
    float ptPhotons = 0;
    float ptNeutral = 0;
    float ptElectrons = 0;
    float ptMuons = 0;
    float ptHFHad = 0;
    float ptHFEM = 0;
  
    float fractionCharged = 0;
    float fractionPhotons = 0;
    float fractionNeutral = 0;
    float fractionElectrons = 0;
    float fractionMuons = 0;
    float fractionHFHad = 0;
    float fractionHFEM = 0;
  
    float totalEnergyFromConst = 0; 

    float ptd = -1.0;

    //girth - See http://arxiv.org/abs/1106.3076v2 - eqn (2)
    double gsumcharged = 0.0;
    double gsum        = 0.0;

    if( useConstituents_ ) {

      std::vector<reco::PFCandidatePtr> pfCandPtrs = jet.getPFConstituents();

      //Alessio, implement ptd calculation here

      float sumpt2 = 0;
      float sumpt = 0;
      for(unsigned i=0; i<pfCandPtrs.size(); ++i) {
	const reco::PFCandidate& cand = *(pfCandPtrs[i]);
	// 	reco::Candidate::LorentzVector jetWithoutCand = jet.p4() - cand.p4();       

	//calculate girth 
	double dr_girth = reco::deltaR(cand,jet);
	gsum += (dr_girth*( cand.pt()/jet.pt() ) ); 
	if(cand.charge() == 0) continue;
	else gsumcharged += (dr_girth*( cand.pt()/jet.pt() ) );
	//end girth

	totalEnergyFromConst += cand.energy();

	sumpt2 += cand.pt() * cand.pt();
	sumpt += cand.pt();

	switch( cand.particleId() ) {
	case reco::PFCandidate::h: 
	  nCharged++;
	  energyCharged += cand.energy(); 
	  ptCharged += cand.pt(); 
	  break;
	case reco::PFCandidate::e: 
	  nElectrons++;
	  energyElectrons += cand.energy(); 
	  ptElectrons += cand.pt(); 
	  break;
	case reco::PFCandidate::mu:
	  // use of the muon selector not yet implemented
	  nMuons++;
	  energyMuons += cand.energy(); 
	  ptMuons += cand.pt(); 
	  break;
	case reco::PFCandidate::gamma:
	  nPhotons++;
	  energyPhotons += cand.energy(); 
	  ptPhotons += cand.pt(); 
	  break;
	case reco::PFCandidate::h0:
	  nNeutral++;
	  energyNeutral += cand.energy(); 
	  ptNeutral += cand.pt(); 
	  break;
	case reco::PFCandidate::h_HF:
	  nHFHad++;
	  energyHFHad += cand.energy(); 
	  ptHFHad += cand.pt(); 
	  break;
	case reco::PFCandidate::egamma_HF:
	  nHFEM++;
	  energyHFEM += cand.energy(); 
	  ptHFEM += cand.pt(); 
	  break;
	default: break;
	}
      }
      ptd = sqrt( sumpt2 ) / sumpt; 

      fractionCharged = energyCharged / totalEnergyFromConst;
      fractionElectrons = energyElectrons / totalEnergyFromConst;
      fractionMuons = energyMuons / totalEnergyFromConst;
      fractionPhotons = energyPhotons / totalEnergyFromConst;
      fractionNeutral = energyNeutral / totalEnergyFromConst;
      fractionHFEM = energyHFEM / totalEnergyFromConst;
      fractionHFHad = energyHFHad / totalEnergyFromConst;

//       if(fractionCharged!=jet.chargedHadronEnergyFraction())std::cout<<"ERROR from PFJetFactory! ChEnFrac mismatched: "<<fractionCharged<<"  "<<jet.chargedHadronEnergyFraction()<<std::endl;
//       if(fractionElectrons!=jet.electronEnergyFraction())std::cout<<"ERROR from PFJetFactory! EleEnFrac mismatched: "<<fractionElectrons<<"  "<<jet.electronEnergyFraction()<<std::endl;
//       if(fractionMuons!=jet.muonEnergyFraction())std::cout<<"ERROR from PFJetFactory! MuonEnFrac mismatched: "<<fractionMuons<<"  "<<jet.muonEnergyFraction()<<std::endl;
//       if(fractionPhotons!=jet.photonEnergyFraction())std::cout<<"ERROR from PFJetFactory! PhotonEnFrac mismatched: "<<fractionPhotons<<"  "<<jet.photonEnergyFraction()<<std::endl;
//       if(fractionNeutral!=jet.neutralHadronEnergyFraction())std::cout<<"ERROR from PFJetFactory! NeuEnFrac mismatched: "<<fractionNeutral<<"  "<<jet.neutralHadronEnergyFraction()<<std::endl;
//       //     if(fractionPhotons!=jet.photonEnergyFraction())std::cout<<"ERROR from PFJetFactory! PhotonEnFrac mismatched: "<<fractionPhotons<<"  "<<jet.photonEnergyFraction()<<std::endl;


    }
    else {
      // using the JetSpecific structure stored in the pat jet

      nCharged = jet.chargedHadronMultiplicity();
      nElectrons = jet.electronMultiplicity();
      nMuons = jet.muonMultiplicity();
      nPhotons = jet.photonMultiplicity();
      nNeutral = jet.neutralHadronMultiplicity();
      nHFEM = jet.HFEMMultiplicity();
      nHFHad = jet.HFHadronMultiplicity();
      
      ptCharged = jet.chargedHadronEnergyFraction() * jet.pt();
      ptElectrons = jet.electronEnergyFraction() * jet.pt();
      ptMuons = jet.muonEnergyFraction() * jet.pt();
      ptPhotons = jet.photonEnergyFraction() * jet.pt();
      ptNeutral = jet.neutralHadronEnergyFraction() * jet.pt();
      ptHFEM = jet.HFEMEnergyFraction() * jet.pt();
      ptHFHad = jet.HFHadronEnergyFraction() * jet.pt();
      
      energyCharged = jet.chargedHadronEnergyFraction() * jet.energy();
      energyElectrons = jet.electronEnergyFraction() * jet.energy();
      energyMuons = jet.muonEnergyFraction() * jet.energy();
      energyPhotons = jet.photonEnergyFraction() * jet.energy();
      energyNeutral = jet.neutralHadronEnergyFraction() * jet.energy();
      energyHFEM = jet.HFEMEnergyFraction() * jet.energy();
      energyHFHad = jet.HFHadronEnergyFraction() * jet.energy();
      
      fractionCharged = jet.chargedHadronEnergyFraction();
      fractionElectrons = jet.electronEnergyFraction();
      fractionMuons = jet.muonEnergyFraction();
      fractionPhotons = jet.photonEnergyFraction();
      fractionNeutral = jet.neutralHadronEnergyFraction();
      fractionHFEM = jet.HFEMEnergyFraction();
      fractionHFHad = jet.HFHadronEnergyFraction();	
    }

    cmgjet->components_[reco::PFCandidate::h].setNumber(nCharged);
    cmgjet->components_[reco::PFCandidate::e].setNumber(nElectrons);
    cmgjet->components_[reco::PFCandidate::mu].setNumber(nMuons);
    cmgjet->components_[reco::PFCandidate::gamma].setNumber(nPhotons);
    cmgjet->components_[reco::PFCandidate::h0].setNumber(nNeutral);
    cmgjet->components_[reco::PFCandidate::egamma_HF].setNumber(nHFEM);
    cmgjet->components_[reco::PFCandidate::h_HF].setNumber(nHFHad);

    cmgjet->components_[reco::PFCandidate::h].setPt(ptCharged);
    cmgjet->components_[reco::PFCandidate::e].setPt(ptElectrons);
    cmgjet->components_[reco::PFCandidate::mu].setPt(ptMuons);
    cmgjet->components_[reco::PFCandidate::gamma].setPt(ptPhotons);
    cmgjet->components_[reco::PFCandidate::h0].setPt(ptNeutral);
    cmgjet->components_[reco::PFCandidate::egamma_HF].setPt(ptHFEM);
    cmgjet->components_[reco::PFCandidate::h_HF].setPt(ptHFHad);

    cmgjet->components_[reco::PFCandidate::h].setEnergy(energyCharged);
    cmgjet->components_[reco::PFCandidate::e].setEnergy(energyElectrons);
    cmgjet->components_[reco::PFCandidate::mu].setEnergy(energyMuons);
    cmgjet->components_[reco::PFCandidate::gamma].setEnergy(energyPhotons);
    cmgjet->components_[reco::PFCandidate::h0].setEnergy(energyNeutral);
    cmgjet->components_[reco::PFCandidate::egamma_HF].setEnergy(energyHFEM);
    cmgjet->components_[reco::PFCandidate::h_HF].setEnergy(energyHFHad);

    cmgjet->components_[reco::PFCandidate::h].setFraction(fractionCharged);
    cmgjet->components_[reco::PFCandidate::e].setFraction(fractionElectrons);
    cmgjet->components_[reco::PFCandidate::mu].setFraction(fractionMuons);
    cmgjet->components_[reco::PFCandidate::gamma].setFraction(fractionPhotons);
    cmgjet->components_[reco::PFCandidate::h0].setFraction(fractionNeutral);
    cmgjet->components_[reco::PFCandidate::egamma_HF].setFraction(fractionHFEM);
    cmgjet->components_[reco::PFCandidate::h_HF].setFraction(fractionHFHad);

    cmgjet->ptd_ = ptd;
    cmgjet->girth_         = gsum;
    cmgjet->girth_charged_ = gsumcharged;


    cmgjet->setUncOnFourVectorScale(jet.userFloat("jecUnc"));

    cmgjet->ptd_qc_             = jet.userFloat("ptD_QC");
    cmgjet->vtxpt_              = jet.userFloat("vtxPt");
    cmgjet->vtx3dL_             = jet.userFloat("vtx3dL");
    cmgjet->vtx3deL_            = jet.userFloat("vtx3deL");
    cmgjet->axis_major_         = jet.userFloat("axis1");
    cmgjet->axis_minor_         = jet.userFloat("axis2"); 
    cmgjet->axis_major_qc_      = jet.userFloat("axis1_QC");
    cmgjet->axis_minor_qc_      = jet.userFloat("axis2_QC"); 
    cmgjet->pt_max_             = jet.userFloat("ptMax");
    cmgjet->tana_               = jet.userFloat("tana");
    cmgjet->ttheta_             = jet.userFloat("ttheta");
    cmgjet->pull_               = jet.userFloat("pull");
    cmgjet->pull_qc_            = jet.userFloat("pull_QC");
    cmgjet->fmax_               = jet.userFloat("jetR");
    cmgjet->fmax_charged_       = jet.userFloat("jetRchg");
    cmgjet->fmax_charged_qc_    = jet.userFloat("jetRchg_QC");
    cmgjet->fmax_neutral_       = jet.userFloat("jetRneutral");
    cmgjet->n_charged_          = jet.userInt("nChg");
    cmgjet->n_charged_ptcut_    = jet.userInt("nChg_ptCut");
    cmgjet->n_charged_qc_       = jet.userInt("nChg_QC");
    cmgjet->n_charged_ptcut_qc_ = jet.userInt("nChg_ptCut_QC");
    cmgjet->n_neutral_          = jet.userInt("nNeutral");
    cmgjet->n_neutral_ptcut_    = jet.userInt("nNeutral_ptCut");      
}
