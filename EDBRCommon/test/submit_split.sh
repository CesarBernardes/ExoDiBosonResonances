#! /bin/bash

########## EDIT THIS PART ################

SampleName=( SingleMu_Run2012A_13Jul2012_xww  SingleMu_Run2012A_recover_xww SingleMu_Run2012B_13Jul2012_xww SingleMu_Run2012C_24Aug2012_xww SingleMu_Run2012C_PromptReco_xww SingleMu_Run2012C_EcalRecove_xww  SingleMu_Run2012D_PromptReco_xww  SingleElectron_Run2012A_13Jul2012_xww SingleElectron_Run2012A_recover_xww SingleElectron_Run2012B_13Jul2012_xww SingleElectron_Run2012C_24Aug2012_xww SingleElectron_Run2012C_EcalRecove_xww   SingleElectron_Run2012C_PromptReco_xww SingleElectron_Run2012D_PromptReco_xww TTBAR_xww TTBARpowheg_xww  WZ_xww ZZ_xww  WW_xww WJetsPt50To70_xww WJetsPt70To100_xww WJetsPt100_xww  WJetsPt180_xww  DYJetsPt50To70_xww DYJetsPt70To100_xww  DYJetsPt100_xww BulkG_WW_lvjj_c1p0_M1000_xww BulkG_WW_lvjj_c1p0_M1500_xww BulkG_WW_lvjj_c1p0_M600_xww RSG_WW_lvjj_c0p2_M1000_xww RSG_WW_lvjj_c0p2_M1500_xww RSG_WW_lvjj_c0p2_M600_xww SingleTopBarSchannel_xww SingleTopBarTWchannel_xww SingleTopBarTchannel_xww SingleTopSchannel_xww SingleTopTWchannel_xww SingleTopTchannel_xww BulkG_WW_lvjj_c0p2_M1000_xww BulkG_WW_lvjj_c0p2_M1100_xww  BulkG_WW_lvjj_c0p2_M1200_xww BulkG_WW_lvjj_c0p2_M1300_xww BulkG_WW_lvjj_c0p2_M1400_xww BulkG_WW_lvjj_c0p2_M1500_xww BulkG_WW_lvjj_c0p2_M1600_xww BulkG_WW_lvjj_c0p2_M1700_xww BulkG_WW_lvjj_c0p2_M1800_xww BulkG_WW_lvjj_c0p2_M1900_xww BulkG_WW_lvjj_c0p2_M2000_xww BulkG_WW_lvjj_c0p2_M2100_xww BulkG_WW_lvjj_c0p2_M2200_xww BulkG_WW_lvjj_c0p2_M2300_xww BulkG_WW_lvjj_c0p2_M2400_xww BulkG_WW_lvjj_c0p2_M2500_xww BulkG_WW_lvjj_c0p2_M600_xww BulkG_WW_lvjj_c0p2_M700_xww BulkG_WW_lvjj_c0p2_M800_xww BulkG_WW_lvjj_c0p2_M900_xww  )

type="fullallrange" #### 'type' could be fullsideband or fullsig or presel or fullallrange, denpending on analyzerEDBR_zz2l2j_tpl.py
OUTDIR=/afs/cern.ch/work/s/shuai/public/diboson/trees/productionv7_newMJ/$type/

QUEUE=2nd

NFILES=20  #number of files to run in each job

##########################################

mkdir -p $OUTDIR
mkdir -p $OUTDIR/logs

echo OutDir is $OUTDIR

eval `scram runtime -sh`
MYWORKAREA=$CMSSW_BASE/src/
cd $MYWORKAREA
eval `scram runtime -sh`

for sample in  "${SampleName[@]}"
do
	echo '###################'
	echo Doing $sample
	 
	#create log dir for each sample
	mkdir -p $OUTDIR/logs/$sample
	echo $OUTDIR/logs/$sample created

	#create the cfg in the log dir of the sample
	cd $OUTDIR/logs/$sample
	sed -e "s/<SAMPLE>/${sample}/g" < ${MYWORKAREA}/ExoDiBosonResonances/EDBRCommon/test/analyzerEDBR_zz2l2j_tpl.py >  analyzerEDBR_${type}_${sample}_cfg.py
	echo Config file created

	#submit the job there, using cmsBatch
	${MYWORKAREA}/ExoDiBosonResonances/EDBRCommon/test/cmsBatch.py $NFILES analyzerEDBR_${type}_${sample}_cfg.py  -b "bsub -q "$QUEUE" -J "treeEDBR_${type}_${sample}" < batchScript.sh"
done

