
const std::string myOutDir="FitSidebandsMJJ_ZZ_20130726_prodv2d_ALL_MCHM/";//_Unblinded
const string inDirSIG="/afs/cern.ch/user/b/bonato/work/PhysAnalysis/EXOVV_2012/analyzer_trees/productionv2d/fullsig/";
const string inDirSB ="/afs/cern.ch/user/b/bonato/work/PhysAnalysis/EXOVV_2012/analyzer_trees/productionv2d/fullsb/";

unsigned int jetCats = 2;//1 for only 1 jet case, 2 for both
bool isZZChannel=true;//this will change only the file list
string leptType="ALL";//"MU" //"ELE"//"ALL"
const std::string InTreeName="SelectedCandidates";
const bool useAlphaVV=false;//include VV into alpha (true) or take it directly from MC (false)
const bool useMCHM=true;
const double DATAMC_HMSF[2]={1.0,0.5};//1JLP ; 1JHP
const unsigned int nToys = 500;
const float lumi =19770.0;


const bool doPseudoExp=false;//true; //if true, for for different psuedo-alpha 
const bool unblind=false;//default is not to plot the data in signal region
const bool decorrLevExpo=true;
const bool plotDecorrLevExpoMain=true;//choose what to plot as main fit function

const bool alphaPoisson=true;//use Poisson errors for alpha uncertainties
const bool plotFitPull=false;//plot pull plot with the fit result
const bool plotFixedBinning=false;//plot fit result with fixed binning
const double FixedBinWidth =50;

std::string channel_marker="xzz";

std::string bkgd_decorr_name="levexp_dcr_xzz";

std::string dims = "2d";


const std::string datacardDir("DataCards_XZZ_20130731_prodv2d_2DTestX");
float mZZmax_=2800;

//**********systematics***********

////0) Lepton trigger and id
const double CMS_trigger_e = 1.01; 
const double CMS_eff_e = 1.03;//from T.Williams

const double CMS_trigger_m = 1.03; //it is 3% at very large eta, otherwise less
const double CMS_eff_m = 1.04; //2% eff from T&P, + 2% conservative for boosted topology

////1) Jet energy scale and resoluation
//signal efficiency
const double CMS_scale_j_up= 1.01;
const double CMS_scale_j_down= 0.99;
//signal shape: p1 for mean and p2 for sigma
const double CMS_sig1J_p1_jes = 0.005;
const double CMS_sig1J_p2_jes = 0.02;
const double CMS_sig1J_p1_jer = 0.00;
const double CMS_sig1J_p2_jer = 0.02;

////2) Electron energy scale and resoluation
//signal efficiency
const double CMS_scale_e = 1.00;
//signal shape: p1 for mean and p2 for sigma
const double CMS_sig1Je_p1_scale = 0.005 ;
const double CMS_sig1Je_p2_scale = 0.0004 ;

////3) Mu energy scale and resoluation
//signal efficiency
const double CMS_scale_m = 1.01;
//signal shape: p1 for mean and p2 for sigma
const double CMS_sig1Jm_p1_scale = 0.006;
const double CMS_sig1Jm_p2_scale = 0.018;



