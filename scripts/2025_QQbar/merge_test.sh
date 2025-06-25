#!/bin/bash

if [ ! -e small_test_NTuples ]; then
    mkdir small_test_NTuples
fi

hadd small_test_NTuples/eL_pR_2f_hadronic_merged.root eL_pR_2f_hadronic*.root 
hadd small_test_NTuples/eR_pL_2f_hadronic_merged.root eR_pL_2f_hadronic*.root 

hadd small_test_NTuples/eL_pR_4f_WW_hadronic_merged.root eL_pR_4f_WW_hadronic*.root 
hadd small_test_NTuples/eR_pL_4f_WW_hadronic_merged.root eR_pL_4f_WW_hadronic*.root 

hadd small_test_NTuples/eL_pR_4f_ZZ_hadronic_merged.root eL_pR_4f_ZZ_hadronic*.root 
hadd small_test_NTuples/eR_pL_4f_ZZ_hadronic_merged.root eR_pL_4f_ZZ_hadronic*.root 
