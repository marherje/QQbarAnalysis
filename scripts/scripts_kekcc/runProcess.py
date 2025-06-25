import os
import sys
import subprocess
import glob
import argparse
import shutil
from pathlib import Path

from processDict import production
projectDir = Path(__file__).parent.absolute()

parser = argparse.ArgumentParser(description='Run QQbarAnalysis')
parser.add_argument('--inputXML', type=str, default='qqbar250_steer.xml',
                    help='Input XML file')
parser.add_argument('--process', type=str, required=True,
                    help='Production process (P2f_z_h, P4f_ww_h, P4_zz_h, Pe1e1h)')
parser.add_argument('--chiral',  type=str, required=True,
                    help='Polarization of beam (eLpR or eRpL)')

args  = parser.parse_args()

model = 'l5'

# anaType: 0 (signal), -1 (background)
if args.process == 'P2f_z_h':
  anaType = 0
else:
  anaType = -1

nfirst    = 1    # first file
nlast_set = -1   # -1: all files
nrun      = 11  # number of runs per job

isAll = False
if nlast_set <= 0:
  isAll = True

chi_ral = {
  'eLpL' : 'eL_pL',
  'eLpR' : 'eL_pR',
  'eRpL' : 'eR_pL',
  'eRpR' : 'eR_pR' 
}

dirinPre = '/group/ilc/grid/storm/prod/ilc/mc-2020/ild/dst-merged/250-SetA/'
dirinMid = '/ILD_l5_o1_v02/v02-02/'

processName = {
  'P2f_z_h'  : f'2f_hadronic_{chi_ral[args.chiral]}',
  'P4f_ww_h' : '4f_WW_hadronic',
  'P4f_zz_h' : '4f_ZZ_hadronic',
  'Pqqh'     : 'higgs'
}

logDir = os.path.join(projectDir,'log')
xmlDir = os.path.join(projectDir,'myxml')

# if os.path.isdir(logDir):
#   shutil.rmtree(logDir)
# if os.path.isdir(xmlDir):
#   shutil.rmtree(xmlDir)

# os.makedirs(logDir)
# os.makedirs(xmlDir)

processID  = production[args.process, args.chiral][0]
prodIDList = production[args.process, args.chiral][1]

print(processName[args.process], args.chiral, processID)
print(prodIDList)

for prodID in prodIDList:

  dirinSuff = ''
  if args.process == 'P2f_z_h' or args.process == 'P4f_ww_h':
    dirinSuff = f'/000{prodID}/000/'

  dirin = f'{dirinPre}/{processName[args.process]}/{dirinMid}/{dirinSuff}/'

  if not os.path.isdir(dirin):
    sys.exit(f'Directory {dirin} does not exist.')

  file_list = []
  try:
    pattern = os.path.join(dirin, f'*I{processID}*{prodID}*.slcio')
    file_list = sorted(glob.glob(pattern))
  except subprocess.CalledProcessError as e:
    print(f"Error: {e}")
    file_list = []

  nf = len(file_list)
  print("number of files for process:", nf)

  nlast = nlast_set
  if isAll or nlast_set >= nf:
    nlast = nf

  njobs = (nlast - nfirst) // nrun + 1
  print("processID {}, prodID {}: nlast {}, nfirst {}, nrun {}, njobs {}".format(processID,prodID, nlast, nfirst, nrun, njobs))
  seqlist = range(1, njobs + 1)
  for seq in seqlist:
    nrun0 = nfirst + nrun * (seq - 1)
    nrun1tmp = nrun0 + nrun - 1

    if nrun1tmp <= nlast:
      nrun1 = nrun1tmp
    else:
      nrun1 = nlast

    print(prodID, nrun0, nrun1, nrun, njobs)

    sub_flist = file_list[nrun0 - 1:nrun1]
    arg_flist = ",".join(sub_flist)

    rootOut  = f"/group/ilc/users/yokugawa/QQbar250/{model}/{args.process}/{args.chiral}/{processID}/{prodID}/dEdx_corr/QQbarProcessor_out/"
    slcioOut = f"/hsm/ilc/users/yokugawa/QQbar250/{model}/{args.process}/{args.chiral}/{processID}/{prodID}/000/"

    subprocess.run(['bsub', '-q', 's', '-J', f'ana_{processID}_{seq:03d}',
                    'python3', 'runMarlin.py',
                    '--inputXML', args.inputXML,
                    '--anaType', f'{anaType}',
                    '--logDir', logDir,
                    '--xmlDir', xmlDir,
                    '--rootOut', rootOut,
                    '--slcioOut', slcioOut,
                    '--flist', arg_flist])
