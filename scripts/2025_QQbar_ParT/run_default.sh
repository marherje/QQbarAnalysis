#!/bin/bash
# file name: kt_xNAMEfile.sh

path="/data/dust/user/marquezh/QQbarAnalysis2025/scripts/2025_QQbar_ParT"
source $path/init_key4hep.sh
cp -r ${path}/data $PWD/.
cp -r ${path}/lib $PWD/.
cp -r ${path}/lcfiweights $PWD/.
cp -r ${path}/HighLevelReco $PWD/.
# cp -r ${path}/TMVA_BDT_MC_12bins $PWD/.
# cp ${path}/CPID_weights.root $PWD/.
# cp ${path}/Ref.12bins.txt $PWD/.

# ROOT warning handling
export ROOT_ERROR_IGNORE_LEVEL=2000  # Suprimir warnings
export ROOT_INFO_LEVEL=3000   

#cp ${path}/GearOutput.xml $PWD/.
cp ${path}/test_xPROCx_xPOLx_xPRODx_xNFILEx.xml .
export MARLIN_DLL=$(echo $MARLIN_DLL | sed 's|:[^:]*libLCFIPlus\.so[^:]*||g' | sed 's|^[^:]*libLCFIPlus\.so[^:]*:||')

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libQQbarProcessor.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libLCFIPlus.so"
echo $PWD
Marlin ${PWD}/test_xPROCx_xPOLx_xPRODx_xNFILEx.xml
