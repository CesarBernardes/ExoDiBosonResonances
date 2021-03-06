import FWCore.ParameterSet.Config as cms
maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ('PoolSource',fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_23_1_pN0.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_24_1_3yy.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_26_1_JKP.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_25_1_7AX.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_28_1_5pN.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_27_1_CPS.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_29_1_jvm.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_2_1_a2O.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_30_1_JTL.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_31_1_JKG.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_32_1_deT.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_33_1_Pug.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_34_1_dve.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_35_1_HBi.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_36_1_Eti.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_37_1_wWz.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_3_1_nqr.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_38_1_npA.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_40_1_hzP.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_5_1_bWI.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_7_1_BUa.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_8_1_rH6.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_9_1_sdY.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_6_1_g3u.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_4_1_mPa.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_42_1_sM4.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_41_1_aMs.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_39_1_xea.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_21_1_yS8.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_20_1_gRR.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_1_1_fx6.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_19_1_ZC2.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_18_1_49u.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_17_1_Ofi.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_16_1_IVI.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_14_1_2LL.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_13_1_Waj.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_12_1_56E.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_11_1_jI2.root",
"/store/user/tomei/JHU_Bulk1000_ZZ_c1_v2/JHU_Bulk1000_ZZ_c1_STEP3/c8f8ed334db8a7d6f56c62266b1dfa5b/RSWW_AODSIM_10_1_r94.root"
]);
