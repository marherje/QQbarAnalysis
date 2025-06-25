import os
import subprocess
import argparse
from processDict import production

model = 'l5'

for key, val in production.items():

  process=key[0]
  chiral =key[1]
  processID =val[0]
  prodIDList=val[1]

  for prodID in prodIDList:

    pathRoot =f"/group/ilc/users/yokugawa/QQbar250/{model}/{process}/{chiral}/{processID}/{prodID}/dEdx_corr/QQbarProcessor_out"
    pathSlcio=f"/hsm/ilc/users/yokugawa/QQbar250/{model}/{process}/{chiral}/{processID}/{prodID}/000"
  
    print(pathSlcio)

    subprocess.run(f"mkdir -p {pathRoot}",shell=True)
    subprocess.run(f"mkdir -p {pathSlcio}",shell=True)
