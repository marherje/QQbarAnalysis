#!/bin/bash

if [ ! -e NTuples ]; then
    mkdir NTuples
fi

if [ ! -e NTuples/Big ]; then
    mkdir NTuples/Big
fi

#rm NTuples/Big/


#hadd -f NTuples/Big/eL_pR_2f_hadronic_merged.root 2f_hadronic_eL_pR*.root 
#hadd -f NTuples/Big/eR_pL_2f_hadronic_merged.root 2f_hadronic_eR_pL*.root 

#hadd -f NTuples/Big/eL_pR_4f_WW_hadronic_merged.root 4f_WW_hadronic*eL_pR*.root 
#hadd -f NTuples/Big/eR_pL_4f_WW_hadronic_merged.root 4f_WW_hadronic*eR_pL*.root 

#hadd -f NTuples/Big/eL_pR_4f_ZZ_hadronic_merged.root 4f_ZZ_hadronic*eL_pR*.root 
#hadd -f NTuples/Big/eR_pL_4f_ZZ_hadronic_merged.root 4f_ZZ_hadronic*eR_pL*.root 

#hadd -f NTuples/Big/eL_pR_ZH_hadronic_merged.root ZH*eL_pR*.root 
#hadd -f NTuples/Big/eR_pL_ZH_hadronic_merged.root ZH*eR_pL*.root 
