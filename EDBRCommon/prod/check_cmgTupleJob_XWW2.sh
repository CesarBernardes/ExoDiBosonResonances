#! /bin/bash


SAMPLE_ARRAY1=()
OUTPATH=""
LOGDIR="./logs/"
if [ $# -lt 1 ]
then
    echo need at least one input, a string that is either \"DATA\" or \"MC\". 
    echo Second \(optional\) input is an integer that if it is \>0 resubmits the failed jobs.
    exit
fi

RESUB=0
if [ $# -ge 2 ]
    then
    RESUB=$2
fi


if [ $1 == "DATA" ]
    then
    echo "Checking data"
#    SAMPLE_ARRAY1=(DoubleMu_Run2012A_13Jul2012 DoubleMu_Run2012A_recover DoubleMu_Run2012B_13Jul2012 DoubleMu_Run2012C_24Aug2012 DoubleMu_Run2012D_PRv1 DoublePhotonHighPt_Run2012B_13Jul2012 DoublePhotonHighPt_Run2012C_24Aug2012 DoublePhotonHighPt_Run2012C_PRv2 DoublePhotonHighPt_Run2012D_PRv1 Photon_Run2012A_13Jul2012 Photon_Run2012A_recover )  #ZjetsMadgraph WZPythia ZZPythia )
    SAMPLE_ARRAY1=(  SingleElectron_Run2012A_13Jul2012_xww  SingleElectron_Run2012A_recover_xww SingleElectron_Run2012B_13Jul2012_xww SingleElectron_Run2012C_24Aug2012_xww SingleElectron_Run2012C_PromptReco_xww SingleElectron_Run2012D_PromptReco_xww  )
    OUTPATH="/store/group/phys_exotica/leptonsPlusJets/ExoDiBosonResonances/CMGtuple/Qiang/production0221/Run2012/presel/"
    LOGDIR="./logs/data12/"
fi

if [ $1 == "MC" ]
    then
    echo "Checking MC"
    SAMPLE_ARRAY1=(TTBAR_xww WZ_xww ZZ_xww  WW_xww WJetsPt50To70_xww WJetsPt70To100_xww WJetsPt100_xww  DYJetsPt50To70_xww DYJetsPt70To100_xww  DYJetsPt100_xww BulkG_WW_lvjj_c1p0_M1000_xww BulkG_WW_lvjj_c1p0_M1500_xww BulkG_WW_lvjj_c1p0_M600_xww RSG_WW_lvjj_c0p2_M1000_xww RSG_WW_lvjj_c0p2_M1500_xww RSG_WW_lvjj_c0p2_M600_xww  )
    OUTPATH="/store/group/phys_exotica/leptonsPlusJets/ExoDiBosonResonances/CMGtuple/productionV1/Run2012/presel/"
    LOGDIR="./logs/Summer12/"
fi




cd $LOGDIR

for sample in "${SAMPLE_ARRAY1[@]}"
do
  cd ./$sample
  if [ $? -ne 0 ]
      then
      echo "Directory $sample does not exist"
      continue
  fi

  echo I am in $(pwd):


  for job in $(/bin/ls -d Job*)
    do
    cd ./$job

    STATUS=0
    egrep exception -ir LSF*/* &> /dev/null
    if [ $? -eq 0 ]
	then 
	let STATUS=STATUS+1
    fi

    egrep segmentation -ir LSF*/* &> /dev/null
    if [ $? -eq 0 ]
	then 
	let STATUS=STATUS+1
    fi
 
   if [ $STATUS -gt 0 ]
	then
	echo 
	echo "+++"
	echo EXception in ./$sample/$job
	EXT=${job#"Job_"}
	if [ $RESUB -gt 0 ]
	    then
	    echo Removing ${OUTPATH}/${sample}/cmgTuple_${EXT}.root  
	    cmsRm ${OUTPATH}/${sample}/cmgTuple_${EXT}.root 
	    echo Resubmitting $job
	    bsub -q 8nh -J "${sample}_${job}" batchScript.sh
	    #rename dir with log for book-keeping
	    for lsfdir in $(/bin/ls -d LSF* )
	      do
	      mv $lsfdir old${lsfdir}
	    done
	fi

	echo "---"
    fi
    cd ../ &> /dev/null
  done

  cd ../

done