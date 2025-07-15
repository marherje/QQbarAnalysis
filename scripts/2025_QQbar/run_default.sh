#!/bin/bash
# file name: kt_xNAMEfile.sh

path="/data/dust/user/marquezh/QQbarAnalysis2025/scripts/2025_QQbar"
source $path/init_ilcsoft.sh
cp -r ${path}/data $PWD/.
cp -r ${path}/lib $PWD/.
cp -r ${path}/lcfiweights $PWD/.
#cp ${path}/GearOutput.xml $PWD/.
cp ${path}/test_xPROCx_xPOLx_xPRODx_xNFILEx.xml .

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libQQbarProcessor.so"
#export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libReconstructedParticleImpl_CopyProcessor.so"
echo $PWD
Marlin ${PWD}/test_xPROCx_xPOLx_xPRODx_xNFILEx.xml
