
const std::string myOutDir="FitSidebandsMJJ_CA8_WW_V24/";
const string inDirSIG="/afs/cern.ch/work/s/shuai/public/diboson/trees/productionv9/AnaSigTree/";
const string inDirSB ="/afs/cern.ch/work/s/shuai/public/diboson/trees/productionv9/AnaSBTree/";

unsigned int jetCats = 1;//1 for only 1 jet case, 2 for both
bool isZZChannel=false;//this will change only the file list
string leptType="ELE";//"MU" //"ELE"//"ALL"
const std::string InTreeName="SelectedCandidates";
const bool useAlphaVV=false;
const unsigned int nToys = 500;
const float lumi =19531.85;//for ele
//const float lumi =19538.85;//for mu


const bool doPseudoExp=true; //if true, for for different psuedo-alpha 
const bool unblind=true;//default is not to plot the data in signal region
const bool decorrLevExpo=true;
const bool plotDecorrLevExpoMain=true;//choose what to plot as main fit function
std::string channel_marker="xww";

const bool alphaPoisson=false;//use Poisson errors for alpha uncertainties


std::string bkgd_decorr_name="levexp_dcr_xww";


const std::string datacardDir("DataCards_XWW_V24/");
float mZZmax_=3000;

//**********systematics***********
////0) Lepton trigger and id
const double CMS_trigger_e = 1.01; 
const double CMS_eff_e = 1.03;//from T.Williams

const double CMS_trigger_m = 1.01; //it is 3% at very large eta, otherwise less
const double CMS_eff_m = 1.01; //2% eff from T&P, + 2% conservative for boosted topology

////1) Jet energy scale and resoluation
//signal efficiency
const double CMS_scale_j_up= 1.03;
const double CMS_scale_j_down= 0.97;
//signal shape: p1 for mean and p2 for sigma
const double CMS_sig1J_p1_jes = 0.013;
const double CMS_sig1J_p2_jes = 0.04;
const double CMS_sig1J_p1_jer = 0.001;
const double CMS_sig1J_p2_jer = 0.03;

////2) Electron energy scale and resoluation
//signal efficiency
const double CMS_scale_e = 1.002;
//signal shape: p1 for mean and p2 for sigma
const double CMS_sig1Je_p1_scale = 0.001 ;
const double CMS_sig1Je_p2_scale = 0.001 ;

////3) Mu energy scale and resoluation
//signal efficiency
const double CMS_scale_m = 1.007;
//signal shape: p1 for mean and p2 for sigma
const double CMS_sig1Jm_p1_scale = 0.001;
const double CMS_sig1Jm_p2_scale = 0.005;


////4) Btagging scale: negligible











