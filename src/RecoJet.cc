
#include "RecoJet.hh"
using EVENT::ReconstructedParticle;
using IMPL::ReconstructedParticleImpl;
using std::vector;
namespace QQbarProcessor
{
  RecoJet::RecoJet (ReconstructedParticle * rawjet, float btag, float ctag, float cattag, int number, 
    float ParT_b, float ParT_c, float ParT_s, float ParT_u, float ParT_d, 
    float ParT_bbar, float ParT_cbar, float ParT_sbar, float ParT_ubar, float ParT_dbar, 
    float ParT_g)
  //: IMPL::ReconstructedParticleImpl(rawjet)
  {
    myBTag = btag;
    myCTag = ctag;
    myCatTag = cattag;
    myNumber = number;
    myMCPDG = 0;
    myRecoVertices = NULL;
    myRawRecoJet = rawjet;
    // Part 11-category probabilities
    myParT_b = ParT_b;
    myParT_c = ParT_c;
    myParT_s = ParT_s;
    myParT_u = ParT_u;
    myParT_d = ParT_d;
    myParT_bbar = ParT_bbar;
    myParT_cbar = ParT_cbar;
    myParT_sbar = ParT_sbar;
    myParT_ubar = ParT_ubar;
    myParT_dbar = ParT_dbar;
    myParT_g = ParT_g;

    setMomentum(rawjet->getMomentum());

    setMass(rawjet->getMass());
    setEnergy(rawjet->getEnergy());
    _particles.reserve(rawjet->getParticles().size());
    _particles.insert(_particles.begin(),rawjet->getParticles().begin(),rawjet->getParticles().end());

  }
  RecoJet::RecoJet ()
  {
    myRecoVertices = NULL;
    myMCPDG = 0;
		
  }
  void RecoJet::SetRecoVertices(std::vector<  EVENT::Vertex * > * vertices)
  {
    myRecoVertices = vertices;
  }
  std::vector<  EVENT::Vertex * > * RecoJet::GetRecoVertices()
  {
    return myRecoVertices;
  }
  void RecoJet::SetBTag(float value)
  {
    myBTag = value;
  }
  void RecoJet::SetCTag(float value)
  {
    myCTag = value;
  }
  void RecoJet::SetCatTag(float value)
  {
    myCatTag = value;
  }
  void RecoJet::SetParTB(float value)
  {
    myParT_b = value;
  }
  void RecoJet::SetParTC(float value)
  {
    myParT_c = value;
  }
  void RecoJet::SetParTS(float value)
  {
    myParT_s = value;
  }
  void RecoJet::SetParTU(float value)
  {
    myParT_u = value;
  }
  void RecoJet::SetParTD(float value)
  {
    myParT_d = value;
  }
  void RecoJet::SetParTBbar(float value)
  {
    myParT_bbar = value;
  }
  void RecoJet::SetParTCbar(float value)
  { 
    myParT_cbar = value;
  }
  void RecoJet::SetParTSbar(float value)
  {
    myParT_sbar = value;
  }
  void RecoJet::SetParTUbar(float value)
  {
    myParT_ubar = value;
  } 
  void RecoJet::SetParTDbar(float value)
  {
    myParT_dbar = value;
  }
  void RecoJet::SetParTG(float value)
  {
    myParT_g = value;
  }

  const float RecoJet::GetBTag() const
  {
    return myBTag;
  }
  const float RecoJet::GetCTag() const
  {
    return myCTag;
  }
  const float RecoJet::GetCatTag() const
  {
    return myCatTag;
  }
  const float RecoJet::GetParTB() const
  {
    return myParT_b;
  }
  const float RecoJet::GetParTC() const
  {
    return myParT_c;
  }
  const float RecoJet::GetParTS() const
  {
    return myParT_s;
  }
  const float RecoJet::GetParTU() const
  {
    return myParT_u;
  }
  const float RecoJet::GetParTD() const
  {
    return myParT_d;
  }
  const float RecoJet::GetParTBbar() const
  {
    return myParT_bbar;
  }
  const float RecoJet::GetParTCbar() const
  {
    return myParT_cbar;
  }
  const float RecoJet::GetParTSbar() const
  {
    return myParT_sbar;
  }
  const float RecoJet::GetParTUbar() const
  {
    return myParT_ubar;
  }
  const float RecoJet::GetParTDbar() const
  {
    return myParT_dbar;
  }
  const float RecoJet::GetParTG() const
  {
    return myParT_g;
  }
  int RecoJet::GetNumberOfVertices()
  {
    if (myRecoVertices) 
      {
	return myRecoVertices->size();
      }
    return myNumber;
  }
  int RecoJet::GetNumberOfVertexParticles()
  {
    int sum = -1;
    if (myRecoVertices) 
      {
	sum = 0;
	for (unsigned int i = 0; i < myRecoVertices->size(); i++) 
	  {
	    sum += myRecoVertices->at(i)->getAssociatedParticle()->getParticles().size();
	  }
      }
    return sum;
  }
  ReconstructedParticle * RecoJet::GetRawRecoJet()
  {
    return myRawRecoJet;
  }
  float RecoJet::GetCostheta()
  {
    float costheta1 =  -2.0;
    vector<float> d1;
    /*if (myRecoVertices && myRecoVertices->size() > 0) 
      {
      double * pos = MathOperator::toDoubleArray(myRecoVertices->at(0)->getPosition(),3);
      d1 = MathOperator::getDirection(pos);
      delete pos;
      }
      else*/ 
    {
      d1 = MathOperator::getDirection(getMomentum());
    }
    costheta1 =  std::cos( MathOperator::getAngles(d1)[1] );
    return costheta1;
  }
  float RecoJet::GetHadronCharge(bool weight)
  {
    float charge = -5.0;
    if (myRecoVertices && myRecoVertices->size() > 0) 
    {
     charge = 0.0;
     for (unsigned int i = 0; i < myRecoVertices->size(); i++) 
     {
       charge += myRecoVertices->at(i)->getAssociatedParticle()->getCharge();
     }
     if (weight) 
     {
       charge = 0.0;
       for (unsigned int i = 0; i < myRecoVertices->size(); i++) 
       {
        ReconstructedParticle * vtx = myRecoVertices->at(i)->getAssociatedParticle();
        for (unsigned int j = 0; j < vtx->getParticles().size(); j++) 
        {
          float p = MathOperator::getModule(vtx->getParticles()[j]->getMomentum());
          charge += vtx->getParticles()[j]->getCharge() * p;
        }
      }
    }
  }
  return charge;
}
  float RecoJet::GetHadronMomentum()
  {
    float momentum = -1.0;
    if (myRecoVertices) 
      {
	momentum = 0.0;
	for (unsigned int i = 0; i < myRecoVertices->size(); i++)
	  {
	    momentum += MathOperator::getModule(myRecoVertices->at(i)->getAssociatedParticle()->getMomentum()); // CRUNCH!!!
	  }
      }
    return momentum;
  }
  float RecoJet::GetMinHadronDistance()
  {
    float mindistance = 1000.;
    if (myRecoVertices && myRecoVertices->size() > 0) 
      {
	for (unsigned int i = 0; i < myRecoVertices->size(); i++) 
	  {
	    float distance = MathOperator::getModule(myRecoVertices->at(i)->getPosition()); // CRUNCH!!!
	    if (distance < mindistance) 
	      {
		mindistance = distance;
	      }
	  }
      }
    return mindistance;
  }
  float RecoJet::GetMaxHadronDistance()
  {
    float maxdistance = 0.;
    if (myRecoVertices && myRecoVertices->size() > 0) 
      {
	for ( unsigned int i = 0; i < myRecoVertices->size(); i++) 
	  {
	    float distance = MathOperator::getModule(myRecoVertices->at(i)->getPosition()); // CRUNCH!!!
	    if (distance > maxdistance) 
	      {
		maxdistance = distance;
	      }
	  }
      }
    return maxdistance;
  }
  const float RecoJet::__GetMCCharge() const
  {
    return myMCCharge;
  }
  void RecoJet::__SetMCCharge( float charge)
  {
    myMCCharge = charge;
  }
  const int RecoJet::__GetMCNtracks() const
  {
    return myMCNtracks;
  }
  void RecoJet::__SetMCNtracks(int n)
  {
    myMCNtracks = n;
  }
  float RecoJet::GetHadronMass()
  {
    float mass = -1.0;
    if (myRecoVertices) 
      {
	mass = 0.0;
	for ( unsigned int i = 0; i < myRecoVertices->size(); i++) 
	  {
	    mass += myRecoVertices->at(i)->getAssociatedParticle()->getMass();
	  }
      }
    return mass;
  }
	
  int RecoJet::GetMCPDG()
  {
    return myMCPDG;
  }
  void RecoJet::SetMCPDG(int pdg)
  {
    myMCPDG = pdg;
  }
  const int RecoJet::__GetMCOscillation() const
  {
    return myMCOscillation;
  }
  void RecoJet::__SetMCOscillation(int n)
  {
    myMCOscillation = n;
  }
  JetCharge & RecoJet::GetComputedCharge()
  {
    return myComputedCharge;
  }

}
