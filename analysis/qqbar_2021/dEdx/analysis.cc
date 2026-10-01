#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString file, TString output, bool ignoreoverlay, bool angularcorrection){
  // /data/dust/user/marquezh/QQbar250_NTuples/Standard/Big/2f_hadronic/eL_pR/merged_2f_eLpR.root
  cout<< " "<<endl;
  cout<< file << endl;
  TString folder="/data/dust/user/marquezh/QQbar250_NTuples/Standard/Big/2f_hadronic/eL_pR/";
  file=folder+file;
  observable ss3(file);
  ss3.dEdx(-1,output,true,ignoreoverlay,angularcorrection);
  ss3.dEdx(-1,output,false,ignoreoverlay,angularcorrection);
  
  gSystem->Exit(0);

  return 0;
}
