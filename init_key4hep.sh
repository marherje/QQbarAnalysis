#!/bin/bash

# This script sets up the Key4hep software stack from CVMFS for the stable releases
source /cvmfs/sw-nightlies.hsf.org/key4hep/setup.sh

# For ParT LCFIPlus
export ONNXRUNTIMEPATH="/cvmfs/sw.hsf.org/key4hep/releases/2024-10-03/x86_64-almalinux9-gcc14.2.0-opt/py-onnxruntime/1.17.1-s4gp4m"

#--------------------------------------------------------------------------------
#     ILCUTIL
#--------------------------------------------------------------------------------
export ilcutil="/cvmfs/sw-nightlies.hsf.org/key4hep/releases/2025-10-31/x86_64-almalinux9-gcc14.2.0-opt/ilcutil/0636dc8c54831fb4b91020f7bcb47fd613563404_develop-u5su52/"
# --- additional ILCUTIL commands ------- 
export ILCUTIL_DIR="$ilcutil"
export LD_LIBRARY_PATH="$ilcutil/lib:$LD_LIBRARY_PATH"
export CMAKE_PREFIX_PATH="$ilcutil:$CMAKE_PREFIX_PATH"

