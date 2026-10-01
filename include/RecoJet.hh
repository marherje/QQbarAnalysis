#include "MathOperator.hh"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/ReconstructedParticleImpl.h>
#include <EVENT/Vertex.h>

#ifndef _RecoJet_hh
#define _RecoJet_hh
namespace QQbarProcessor 
{
	struct JetCharge
	{
		JetCharge()
		{
			ByTVCM = NULL;
			ByTrackCount = NULL;
			ByLepton = NULL;
		}
		~JetCharge()
		{
			delete ByTVCM;
			delete ByTrackCount;
			delete ByLepton;
		}

		int * ByTVCM;
		int * ByTrackCount;
		int * ByLepton;
	};
	class RecoJet : public IMPL::ReconstructedParticleImpl
	{
		public:
			//
			//	Constants
			//

			//
			//	Constructors
			//
			RecoJet (EVENT::ReconstructedParticle * rawjet, float btag, float ctag, float cattag, int number, float parT_b, float parT_c, float parT_s, float parT_u, float parT_d, float parT_bbar, float parT_cbar, float parT_sbar, float parT_ubar, float parT_dbar, float parT_g);// : IMPL::ReconstructedParticleImpl(rawjet);
			RecoJet ();
			virtual ~RecoJet () {};
			//
			//	Methods
			//
			JetCharge & GetComputedCharge();
			const float GetBTag() const;
			const float GetCTag() const;
			const float GetCatTag() const;
			const float GetParTB() const;
			const float GetParTC() const;
			const float GetParTS() const;
			const float GetParTU() const;
			const float GetParTD() const;
			const float GetParTBbar() const;
			const float GetParTCbar() const;
			const float GetParTSbar() const;
			const float GetParTUbar() const;
			const float GetParTDbar() const;
			const float GetParTG() const;
			void SetBTag(float value);
			void SetCTag(float value);
			void SetCatTag(float value);
			void SetParTB(float value);
			void SetParTC(float value);
			void SetParTS(float value);
			void SetParTU(float value);
			void SetParTD(float value);
			void SetParTBbar(float value);
			void SetParTCbar(float value);
			void SetParTSbar(float value);
			void SetParTUbar(float value);
			void SetParTDbar(float value);
			void SetParTG(float value);
			void SetRecoVertices(std::vector<  EVENT::Vertex * > * vertices);
			std::vector<  EVENT::Vertex * > * GetRecoVertices();
			int GetNumberOfVertices();
			int GetNumberOfVertexParticles();
			float GetHadronCharge(bool weight = false);
			float GetHadronMomentum();
			float GetHadronMass();
			EVENT::ReconstructedParticle * GetRawRecoJet();
			float GetCostheta();
			float GetMinHadronDistance();
			float GetMaxHadronDistance();
			const double * GetMomentum();
			int GetMCPDG();
			void SetMCPDG(int pdg);


			const float __GetMCCharge() const;
			void __SetMCCharge(float charge);
			const int __GetMCNtracks() const;
			void __SetMCNtracks(int n);
			const int __GetMCOscillation() const;
			void __SetMCOscillation(int n);

		protected:
			//
			//	Data
			//
			float myBTag;
			float myCTag;
			float myCatTag;
			float myParT_b;
			float myParT_c;
			float myParT_s;
			float myParT_u;
			float myParT_d;
			float myParT_bbar;
			float myParT_cbar;
			float myParT_sbar;
			float myParT_ubar;
			float myParT_dbar;
			float myParT_g;
			int myNumber;
			int myMCPDG;
			float myMCCharge;
			int myMCNtracks;
			int myMCOscillation;
			JetCharge myComputedCharge;
			EVENT::ReconstructedParticle * myRawRecoJet;
			std::vector<  EVENT::Vertex * > * myRecoVertices;
			//
			//	Private methods
			//
	};
}
#endif
