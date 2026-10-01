#include "QQbarTools.hh"
using std::vector;
using std::string;

namespace QQbarProcessor 
{

  vector< RecoJet * > * QQbarTools::getJets(LCCollection * jetcol, LCCollection *jetrelcol)
  {
    int jetnumber = jetcol->getNumberOfElements();
    vector< RecoJet * > * result = new vector< RecoJet * >();
    LCRelationNavigator navigator(jetrelcol);
    PIDHandler pidh(jetcol);
    int alid = -1;
    int ParT_id = -1;
    try
      {
	    alid = pidh.getAlgorithmID("vtxrec");
      }
    catch(UTIL::UnknownAlgorithm &e)
      {
	    streamlog_out(DEBUG) << "No algorithm vtxrec!\n";
	    alid = -1;
      }
    if (alid < 0) 
    {
	    try
	    {
	      alid = pidh.getAlgorithmID("lcfiplus");
	    }
	    catch(UTIL::UnknownAlgorithm &e)
	    {
	      streamlog_out(DEBUG) << "No algorithm lcfiplus!\n";
	      alid = -1;
	    }	
    }
    try
	  {
	    ParT_id = pidh.getAlgorithmID("weaver");
	  }
	  catch(UTIL::UnknownAlgorithm &e)
	  {
	    streamlog_out(DEBUG) << "No algorithm weaver!\n";
	    ParT_id = -1;
	  }	

    streamlog_out(DEBUG) << "Algorithm id: " << jetnumber << "\n";
    streamlog_out(DEBUG) << "Algorithm alid: " << alid << "\n";
    streamlog_out(DEBUG) << "Algorithm ParT_id: " << ParT_id << "\n";
    for (int j = 0; j < jetnumber; j++) 
      {
	      ReconstructedParticle * jetpart = dynamic_cast< ReconstructedParticle * >(jetcol->getElementAt(j));
	      vector< Vertex * > * vertices = convert(navigator.getRelatedToObjects(jetpart));
	      const vector< ReconstructedParticle * > components = jetpart->getParticles();
	      int nvtx = vertices->size();
	      float btag = 0.0;
	      float ctag = 0.0;
        float cattag = -1.0;
        // 11-categories ParT
        float ParT_b = 0.0;
        float ParT_c = 0.0;
        float ParT_s = 0.0;
        float ParT_u = 0.0;
        float ParT_d = 0.0;
        float ParT_bbar = 0.0;
        float ParT_cbar = 0.0;
        float ParT_sbar = 0.0;
        float ParT_ubar = 0.0;
        float ParT_dbar = 0.0;
        float ParT_g = 0.0;

	      if (alid > -1) 
	      {
	        const ParticleID& pid = pidh.getParticleID(jetpart,alid);
	        vector<float> params = pid.getParameters();
	        btag = params[pidh.getParameterIndex(alid,"BTag")];
	        ctag = params[pidh.getParameterIndex(alid,"CTag")];
          cattag = params[pidh.getParameterIndex(alid,"Category")];
	      }
        if (ParT_id > -1) 
        {
          const ParticleID& pid = pidh.getParticleID(jetpart,ParT_id);
          vector<float> params = pid.getParameters();
          ParT_b = params[pidh.getParameterIndex(ParT_id,"mc_b")];
          ParT_c = params[pidh.getParameterIndex(ParT_id,"mc_c")];
          ParT_s = params[pidh.getParameterIndex(ParT_id,"mc_s")];
          ParT_u = params[pidh.getParameterIndex(ParT_id,"mc_u")];
          ParT_d = params[pidh.getParameterIndex(ParT_id,"mc_d")];
          ParT_bbar = params[pidh.getParameterIndex(ParT_id,"mc_bbar")];
          ParT_cbar = params[pidh.getParameterIndex(ParT_id,"mc_cbar")];
          ParT_sbar = params[pidh.getParameterIndex(ParT_id,"mc_sbar")];
          ParT_ubar = params[pidh.getParameterIndex(ParT_id,"mc_ubar")];
          ParT_dbar = params[pidh.getParameterIndex(ParT_id,"mc_dbar")];
          ParT_g = params[pidh.getParameterIndex(ParT_id,"mc_g")];
        }
	      RecoJet * jet = new RecoJet(jetpart, btag, ctag, cattag, nvtx, ParT_b, ParT_c, ParT_s, ParT_u, ParT_d, ParT_bbar, ParT_cbar, ParT_sbar, ParT_ubar, ParT_dbar, ParT_g);
	      jet->SetRecoVertices(vertices);
	      PrintJet(jet);
	      result->push_back(jet);
      }
    return result;
		
  }

  vector< Vertex * > * QQbarTools::convert(const std::vector< LCObject * > & objs)
  {
    std::vector< Vertex * > * result = new std::vector< Vertex * >();
    for (unsigned int i = 0; i < objs.size(); i++) 
      {
	result->push_back(dynamic_cast< Vertex * >(objs[i]));
      }
    return result;
  }

  void QQbarTools::PrintJet(RecoJet * jet)
  {
    streamlog_out(DEBUG) << "Jet E: " << jet->getEnergy()
			 << " m: " << jet->getMass()
			 << " btag: " << jet->GetBTag()
			 << " costheta: " << jet->GetCostheta()
			 << " p_B: " << jet->GetHadronMomentum()
			 << " ntracks: " << jet->GetNumberOfVertexParticles()
			 << "\n";
  }

  void QQbarTools::PrintParticle(ReconstructedParticle * jet)
  {
    streamlog_out(DEBUG) << "E: " << jet->getEnergy()
			 <<" m: " << jet->getMass()
			 <<" PDG: " << jet->getType()
			 << "\n";
  }

  void QQbarTools::PrintParticle(MCParticle * jet)
  {
    streamlog_out(DEBUG) << "E: " << jet->getEnergy()
			 <<" m: " << jet->getMass()
			 <<" q: " << jet->getCharge()
			 <<" PDG: " << jet->getPDG()
			 << "\n";
  }

  void QQbarTools::PrintJets(std::vector< RecoJet * > *jets)
  {
    for (unsigned int i = 0; i < jets->size(); i++) 
      {
	PrintJet(jets->at(i));
      }
  }


  /*  vector<float> QQbarTools::getThrust(vector<float> & thrust, LCCollection * pfos)
  {
    streamlog_out(DEBUG) << "Size: " << thrust.size() << "\n";
    double taxis[3];
    taxis[0] = thrust[0]; taxis[1] = thrust[1]; taxis[2] = thrust[2];
    vector<float> direction = MathOperator::getDirection(thrust);
    float axisAngle = MathOperator::getAngles(direction)[1];
    streamlog_out(DEBUG) << "THRUST COS0: " << std::cos(axisAngle) << "\n";
    int nparticles = pfos->getNumberOfElements();
    int counter = 0;
    vector< ReconstructedParticle * > jetPositive;
    vector< ReconstructedParticle * > jetNegative;
    for (unsigned int i = 0; i < nparticles; i++) 
      {
	ReconstructedParticle * particle = dynamic_cast< ReconstructedParticle * >(pfos->getElementAt(i));
	float angle = MathOperator::getAngleBtw(taxis, particle->getMomentum());
	//streamlog_out(DEBUG) << "Angle: " << angle << "\n";
	if (angle > 3.1416/2) 
	  {
	    jetPositive.push_back(particle);
	    counter++;
	  }
	else 
	  {
	    jetNegative.push_back(particle);
	  }
      }
    streamlog_out(DEBUG) << "In positive direction " << counter << " particles, in negative - " << nparticles - counter << "\n";
    //_stats._ZZMass1 = getMass(jetPositive);
    //_stats._ZZMass2 = getMass(jetNegative);
    vector<float> masses;
    masses.push_back(getMass(jetPositive));
    masses.push_back(getMass(jetNegative));

    streamlog_out(DEBUG) << "Mass_+: " << masses.at(0) << " Mass_-: " << masses.at(1) << "\n";
    }*/


}


