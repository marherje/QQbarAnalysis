for file in 000 
do
    root -l -q analysis.cc\(\"2f_hadronic_eL_pR_00015273_new_"$file".root\",\"${file}\",true,true\) > log_correction_${file} 
done




