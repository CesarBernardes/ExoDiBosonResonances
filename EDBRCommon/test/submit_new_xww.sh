#! /bin/bash

########## EDIT THIS PART ################

SampleName=( SingleMu_Run2012A_13Jul2012_xww  SingleMu_Run2012A_recover_xww SingleMu_Run2012B_13Jul2012_xww SingleMu_Run2012C_24Aug2012_xww SingleMu_Run2012C_PromptReco_xww SingleMu_Run2012D_PromptReco_xww TTBAR_xww WZ_xww ZZ_xww  WW_xww WJetsPt50To70_xww WJetsPt70To100_xww WJetsPt100_xww  DYJetsPt50To70_xww DYJetsPt70To100_xww  DYJetsPt100_xww BulkG_WW_lvjj_c1p0_M1000_xww BulkG_WW_lvjj_c1p0_M1500_xww BulkG_WW_lvjj_c1p0_M600_xww RSG_WW_lvjj_c0p2_M1000_xww RSG_WW_lvjj_c0p2_M1500_xww RSG_WW_lvjj_c0p2_M600_xww  SingleElectron_Run2012A_13Jul2012_xww  SingleElectron_Run2012A_recover_xww SingleElectron_Run2012B_13Jul2012_xww SingleElectron_Run2012C_24Aug2012_xww SingleElectron_Run2012C_PromptReco_xww SingleElectron_Run2012D_PromptReco_xww SingleTopBarSchannel_xww SingleTopBarTWchannel_xww SingleTopBarTchannel_xww SingleTopSchannel_xww SingleTopTWchannel_xww SingleTopTchannel_xww )

type="fullsig" #### 'type' could be fullsideband or fullsig or presel, denpending on analyzerEDBR_zz2l2j_tpl.py
OUTDIR=/afs/cern.ch/work/s/shuai/public/diboson/trees/productionv6/$type/

QUEUE=2nd

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

	#submit the job there, and put the log also there
	sed -e s%'<sample>'%${sample}%g  < ${MYWORKAREA}/ExoDiBosonResonances/EDBRCommon/test/run_new.sh > run_new_temp.sh
	sed -e s%'<type>'%${type}%g  < run_new_temp.sh > run_new.sh
	rm run_new_temp.sh
	chmod 755 run_new.sh	
	bsub -q $QUEUE  -J "treeEDBR_${type}_${sample}"  run_new.sh  $OUTDIR
	#./run_new.sh
done

