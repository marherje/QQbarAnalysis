#!/bin/bash

path=$PWD

filelimit=10

##### Signal
##### 2f_hadronic
##### 946G (x2)
for pol in "eL_pR"
do
	for proc in "2f_hadronic"
	do
		for prod in "00015273" #"00015467"
		do
			folder_name="/pnfs/desy.de/ilc/prod/ilc/mc-2020/ild/dst-merged/250-SetA/${proc}_${pol}/ILD_l5_o1_v02/v02-02/${prod}/000"
			cd $folder_name
			echo $folder_name
			FILES=*
			i=0
			for f in $FILES
			do
				name="00"$i
				if [ $i -gt 9 ]; then
					name="0"$i
				fi
				if [ $i -gt 99 ]; then
					name=$i
				fi
				fullfilename="${folder_name}/${f}"
				cp ${path}/test_default.xml ${path}/test_${proc}_${pol}_${prod}_${name}.xml
				sed -i -e 's/xPROCx/'${proc}'/g' ${path}/test_${proc}_${pol}_${prod}_${name}.xml
				sed -i -e 's/xPOLx/'${pol}'/g' ${path}/test_${proc}_${pol}_${prod}_${name}.xml
				sed -i -e 's/xPRODx/'${prod}'/g' ${path}/test_${proc}_${pol}_${prod}_${name}.xml
				sed -i -e 's:xFULLFILENAMEx:'${fullfilename}':g' ${path}/test_${proc}_${pol}_${prod}_${name}.xml
				sed -i -e 's/xNFILEx/'${name}'/g' ${path}/test_${proc}_${pol}_${prod}_${name}.xml	
				sed -i -e 's/xANATYPEx/'0'/g' ${path}/test_${proc}_${pol}_${prod}_${name}.xml
				cp ${path}/run_default.sh ${path}/run_${proc}_${pol}_${prod}_${name}.sh
				sed -i -e 's/xPOLx/'${pol}'/g' ${path}/run_${proc}_${pol}_${prod}_${name}.sh
				sed -i -e 's/xPROCx/'${proc}'/g' ${path}/run_${proc}_${pol}_${prod}_${name}.sh
				sed -i -e 's/xPRODx/'${prod}'/g' ${path}/run_${proc}_${pol}_${prod}_${name}.sh
				sed -i -e 's/xNFILEx/'${name}'/g' ${path}/run_${proc}_${pol}_${prod}_${name}.sh
				cp ${path}/run_default.sub ${path}/run_${proc}_${pol}_${prod}_${name}.sub
				sed -i -e 's/xPOLx/'${pol}'/g' ${path}/run_${proc}_${pol}_${prod}_${name}.sub
				sed -i -e 's/xPROCx/'${proc}'/g' ${path}/run_${proc}_${pol}_${prod}_${name}.sub
				sed -i -e 's/xPRODx/'${prod}'/g' ${path}/run_${proc}_${pol}_${prod}_${name}.sub
				sed -i -e 's/xNFILEx/'${name}'/g' ${path}/run_${proc}_${pol}_${prod}_${name}.sub
				cd $path
				echo $PWD
				if [ -f ${path}/${proc}_${pol}_${prod}_${name}.root ]; 
				then  
					echo "Skip "${name}
				else 
					echo "Submit --- > " ${name}
					condor_submit run_${proc}_${pol}_${prod}_${name}.sub
					sleep 0.1s
				fi
				if [ $i -ge $filelimit ]; then
					break
				fi    
				i=$((i+1))
			done
		done
	done
done
