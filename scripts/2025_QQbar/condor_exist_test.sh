#!/bin/bash

path=$PWD

for pol in "eL_pR" #"eR_pL"
do
	for prod in "2f_hadronic" #"4f_WW_hadronic" "4f_ZZ_hadronic"
	do
    folder_name="/data/dust/user/marquezh/QQBar_data/small_test/${pol}/${prod}/"
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
	cp ${path}/test_default.xml ${path}/test_${pol}_${prod}_${name}.xml
	sed -i -e 's/xPOLx/'${pol}'/g' ${path}/test_${pol}_${prod}_${name}.xml
    sed -i -e 's/xPRODx/'${prod}'/g' ${path}/test_${pol}_${prod}_${name}.xml
	sed -i -e 's/xNFILENAMEx/'${f}'/g' ${path}/test_${pol}_${prod}_${name}.xml
	sed -i -e 's/xNFILEx/'${name}'/g' ${path}/test_${pol}_${prod}_${name}.xml	
	sed -i -e 's/xANATYPEx/'0'/g' ${path}/test_${pol}_${prod}_${name}.xml
	cp ${path}/run_default.sh ${path}/run_${pol}_${prod}_${name}.sh
	sed -i -e 's/xPOLx/'${pol}'/g' ${path}/run_${pol}_${prod}_${name}.sh
	sed -i -e 's/xPRODx/'${prod}'/g' ${path}/run_${pol}_${prod}_${name}.sh
	sed -i -e 's/xNFILEx/'${name}'/g' ${path}/run_${pol}_${prod}_${name}.sh
	cp ${path}/run_default.sub ${path}/run_${pol}_${prod}_${name}.sub
	sed -i -e 's/xPOLx/'${pol}'/g' ${path}/run_${pol}_${prod}_${name}.sub
    sed -i -e 's/xPRODx/'${prod}'/g' ${path}/run_${pol}_${prod}_${name}.sub
	sed -i -e 's/xNFILEx/'${name}'/g' ${path}/run_${pol}_${prod}_${name}.sub
	
	if [ -f ${path}/${pol}_${prod}_${name}.root ]; 
	then  
	    echo "Skip "${name} 
        else 
	    echo "Submit --- > " ${name}   
	    cd -
	    condor_submit run_${pol}_${prod}_${name}.sub
	    #sleep 0.1s 
	    cd -
	fi    
	#rm ${path}/run_${pol}_${prod}_${name}.sub
	#rm ${path}/run_${pol}_${prod}_${name}.sh
	i=$((i+1))
    done
    cd -
	done
done

for pol in "eL_pR" #"eR_pL"
do
	for prod in #"4f_WW_hadronic" "4f_ZZ_hadronic"
	do
    folder_name="/data/dust/user/marquezh/QQBar_data/small_test/${pol}/${prod}/"
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
	cp ${path}/test_default.xml ${path}/test_${pol}_${prod}_${name}.xml
	sed -i -e 's/xPOLx/'${pol}'/g' ${path}/test_${pol}_${prod}_${name}.xml
    sed -i -e 's/xPRODx/'${prod}'/g' ${path}/test_${pol}_${prod}_${name}.xml
	sed -i -e 's/xNFILENAMEx/'${f}'/g' ${path}/test_${pol}_${prod}_${name}.xml
	sed -i -e 's/xNFILEx/'${name}'/g' ${path}/test_${pol}_${prod}_${name}.xml	
	sed -i -e 's/xANATYPEx/'-1'/g' ${path}/test_${pol}_${prod}_${name}.xml
	cp ${path}/run_default.sh ${path}/run_${pol}_${prod}_${name}.sh
	sed -i -e 's/xPOLx/'${pol}'/g' ${path}/run_${pol}_${prod}_${name}.sh
	sed -i -e 's/xPRODx/'${prod}'/g' ${path}/run_${pol}_${prod}_${name}.sh
	sed -i -e 's/xNFILEx/'${name}'/g' ${path}/run_${pol}_${prod}_${name}.sh
	cp ${path}/run_default.sub ${path}/run_${pol}_${prod}_${name}.sub
	sed -i -e 's/xPOLx/'${pol}'/g' ${path}/run_${pol}_${prod}_${name}.sub
    sed -i -e 's/xPRODx/'${prod}'/g' ${path}/run_${pol}_${prod}_${name}.sub
	sed -i -e 's/xNFILEx/'${name}'/g' ${path}/run_${pol}_${prod}_${name}.sub
	
	if [ -f ${path}/${pol}_${prod}_${name}.root ]; 
	then  
	    echo "Skip "${name} 
        else 
	    echo "Submit --- > " ${name}   
	    cd -
	    condor_submit run_${pol}_${prod}_${name}.sub
	    #sleep 0.1s 
	    cd -
	fi    
	#rm ${path}/run_${pol}_${prod}_${name}.sub
	#rm ${path}/run_${pol}_${prod}_${name}.sh
	i=$((i+1))
    done
    cd -
	done
done
