import os
import subprocess
import argparse
import shutil
import pysed

parser = argparse.ArgumentParser(description='Start and end of iteration')
parser.add_argument('--inputXML', type=str, default='qqbar250_steer.xml',
                    help='Input XML file')
parser.add_argument('--anaType',  type=int, required=True,
                    help='analysis type (signal: 0, background: -1)')
parser.add_argument('--logDir',  type=str, required=True,
                    help='log directory')
parser.add_argument('--xmlDir',  type=str, required=True,
                    help='steering file directory')
parser.add_argument('--rootOut',  type=str, required=True,
                    help='root file output directory')
parser.add_argument('--slcioOut',  type=str, required=True,
                    help='slcio file output directory')
parser.add_argument('--flist',  type=str, required=True,
                    help='file list with full path separated by comma')

args  = parser.parse_args()
flist = args.flist.split(",")

for ifile in flist:
  filename = os.path.splitext(os.path.basename(ifile))[0]

  lastxml = os.path.join(args.xmlDir, f'{filename}.xml')
  log     = os.path.join(args.logDir, f'{filename}.log')

  rootOutFile  = os.path.join(args.rootOut, f'{filename}.root')
  slcioOutFile = os.path.join(args.slcioOut, f'{filename}.slcio')

  shutil.copyfile(args.inputXML, lastxml)

  pysed.replace('<!-- INPUT.slcio -->',ifile,lastxml)
  pysed.replace('<!-- AnalysisType -->',f'{args.anaType}',lastxml)
  pysed.replace('<!-- OUTPUT2.root -->',rootOutFile,lastxml)
  pysed.replace('<!-- OUTPUT.slcio -->',slcioOutFile,lastxml)

  # subprocess.run(['Marlin',lastxml], stdout=open(log,'w'), stderr=subprocess.STDOUT)
  subprocess.run(['Marlin',lastxml])

