// g++ histo_ldf.cxx `root-config --cflags --libs` -O3 -o histo_ldf
// Execute with ./histo_ldf Run008.root
// Adapted for xia4ids from the histogram code for Nikita's 128Cd decay at GRIFFIN :-)
// More info in xiaids/inc/define_root.hh, read_ldf.hh, and even_builder_tree.hh

#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <cstdio>

#include "TROOT.h"
#include "TTree.h"
#include "TTreeIndex.h"
#include "TVirtualIndex.h"
#include "TChain.h"
#include "TFile.h"
#include "TList.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TStopwatch.h"
#include "TMath.h"
#include "TVectorD.h"

#include "../xia4ids/inc/xia4ids.hh"


///////////////////////////////////// SETUP ///////////////////////////////////////
// Global helpers
TChain    *gChain = 0;
TList    *outlist = 0;

// Histogram paramaters
Int_t nchan       = 17;
Double_t nbinsE   = 1000;
Double_t lowE     = 2;
Double_t highE    = 4002;
Double_t nbinsT   = 500;
Double_t lowT     = -500;
Double_t highT    = 500;

// Coincidence Parameters
Double_t ggTlow   = 0.;   	// Times are in 4-ns steps (timestamp)
Double_t ggThigh  = 200.;
Double_t ggBGlow  = 300.; 
Double_t ggBGhigh = 500.; 
Double_t ggScale  = (ggThigh - ggTlow)/(ggBGhigh - ggBGlow);


///////////////////////////////////// FUNCTIONS ///////////////////////////////////////
void Subtract(const char *mat1,const char *mat2,const char *name,const char *title,double scale) {
  TH1 *m1 = (TH1*)outlist->FindObject(mat1);
  TH1 *m2 = (TH1*)outlist->FindObject(mat2);
  TH1 *m3 = (TH1*)m1->Clone(name);
  m3->SetNameTitle(name,title);
  m3->Add(m2,-scale);
  outlist->Add(m3); 
}

void FillHist(const char *name,const char *title,int xbin,double xlow, double xhigh,double xvalue,
    int ybin=0,double ylow=0.0,double yhigh=0.0,double yvalue=0.0) {
  if(!outlist)
    outlist = new TList;
  TH1 *hist = (TH1*)outlist->FindObject(name);
  if(!hist) {
    if(ybin) 
      hist = new TH2D(name,title,xbin,xlow,xhigh,ybin,ylow,yhigh);
    else
      hist = new TH1D(name,title,xbin,xlow,xhigh);
    outlist->Add(hist);
  }
  if(ybin)
    hist->Fill(xvalue,yvalue);
  else
    hist->Fill(xvalue);
}

void FillHist(const char *name,const char *title,int xbin,double xlow, double xhigh,const char *xvalue,
    int ybin=0,double ylow=0.0,double yhigh=0.0,double yvalue=0.0) {
  if(!outlist)
    outlist = new TList;
  TH1 *hist = (TH1*)outlist->FindObject(name);
  if(!hist) {
    if(ybin) 
      hist = new TH2D(name,title,xbin,xlow,xhigh,ybin,ylow,yhigh);
    else
      hist = new TH1D(name,title,xbin,xlow,xhigh);
    outlist->Add(hist);
  }
  if(ybin)
    ((TH2*)hist)->Fill(xvalue,yvalue,1);
  else
    hist->Fill(xvalue,1);
}

void FillHistSym(const char *name,const char *title,int xbin,double xlow, double xhigh,double xvalue,
    int ybin,double ylow,double yhigh,double yvalue) {
  if(!outlist)
    outlist = new TList;
  TH1 *hist = (TH1*)outlist->FindObject(name);
  if(!hist) {
    if(ybin) 
      hist = new TH2D(name,title,xbin,xlow,xhigh,ybin,ylow,yhigh);
    else
      hist = new TH1D(name,title,xbin,xlow,xhigh);
    outlist->Add(hist);
  }
  hist->Fill(xvalue,yvalue);
  hist->Fill(yvalue,xvalue);
}

int GetRunNumber(const std::string& fileName)
{
   if(fileName.length() == 0) {
      return 0;
   }
   std::size_t found = fileName.rfind(".root");
   if(found == std::string::npos) {
      return 0;
   }
   std::size_t found2 = fileName.rfind('-');

   if(found2 == std::string::npos) {
      found2 = fileName.rfind('n');
   }
   std::string temp;
   if(found2 == std::string::npos || fileName.compare(found2 + 2, 3, ".root") != 0) {
      temp = fileName.substr(found - 3, 3);
   } else {
      temp = fileName.substr(found - 7, 3);
   }
   return atoi(temp.c_str());
}



///////////////////////////////////// HISTOGRAMS ///////////////////////////////////////
void MakeHistos(long maxEntries=0) {

  gChain->SetBranchAddress("Multiplicity", &MULT_branch); // int
  gChain->SetBranchAddress("Time_vs_ref", &TIME_REF_branch); // ULong64_t
  gChain->SetBranchAddress("Timestamp", &TIME_RUN_branch); // ULong64_t
  gChain->SetBranchAddress("Energy_Chan", E_branch); // E_Chan[nchan] int array of nchan values, one per detector type
  gChain->SetBranchAddress("Time_Chan", T_branch); // T_Chan[nchan] int array of nchan values, one per detector type
  gChain->SetBranchAddress("Mult_Chan", &M_branch); // int, one per detector type


  std::cout<<std::fixed<<std::setprecision(1); //This just make outputs not look terrible

  if(maxEntries == 0 || maxEntries > gChain->GetEntries()) {
    maxEntries = gChain->GetEntries();
  }
  
  long entry = 0;
  for(entry = 0; entry < maxEntries; entry++) { // Loop over all entries
    gChain->GetEntry(entry);

    FillHist("Multiplicity", "Event Multiplicity; Multiplicity; Counts",
    nchan, 0, nchan, MULT_branch);

    FillHist("Time_vs_ref", "Time vs Reference; Time [4 ns]; Counts",
    nchan, -nchan, nchan, TIME_REF_branch);
    
    FillHist("Timestamp", "Timestamp; Time [4 ns]; Counts",
    400, 0, 400000000, TIME_RUN_branch);    

    FillHist("Mult_Chan", "Mult_Chan; Multiplicity; Counts",
    nchan, 0, nchan, M_branch[0]);


    for (int hit1 = 0; hit1 < nchan; hit1++) { // Loop over all channels (index)

      FillHist("HitPattern","Hit Pattern; Channel Number; Counts",
      nchan, 0, nchan, hit1);

      FillHist("Chan_Summary","Channel Summary; Energy [keV]; Channel Number",
      nbinsE, lowE, highE, E_branch[0][hit1], nchan, 0, nchan, hit1);

      FillHist(Form("Chan%02i_Singles", hit1), Form("Chan%02i_Singles; Energy [keV]; Counts", hit1), 
      nbinsE, lowE, highE, E_branch[0][hit1]);

      FillHist("ChanSum_Singles", "ChanSum_Singles; Energy [keV]; Counts", 
      nbinsE, lowE, highE, E_branch[0][hit1]); 

      FillHist("Time_Chan", "Time_Chan; Time [4 ns]; Counts", 
      nbinsE/10, lowE, highE, T_branch[0][hit1]);


        for (int hit2 = hit1; hit2 < nchan; hit2++) { // Loop over all channels a second time

              FillHist("TimeDiff_All","All Hit2 time - Hit1 time; Time Difference [4 ns]; Energy [keV]",  
              nbinsT, lowT, highT, (T_branch[0][hit2] - T_branch[0][hit1]), nbinsE, lowE, highE, E_branch[0][hit2]);

	    if(T_branch[0][hit2] != T_branch[0][hit1]) { // Maybe we need this to get rid of diagonal line at E1 = E2

              FillHistSym("Matrix_All","All Coincidence Matrix; Energy [keV]; Energy [keV]",
              nbinsE, lowE, highE, E_branch[0][hit1], nbinsE, lowE, highE, E_branch[0][hit2]);

            if((fabs(T_branch[0][hit2] - T_branch[0][hit1]) >= ggTlow) 
            && (fabs(T_branch[0][hit2] - T_branch[0][hit1]) <= ggThigh)) {

              FillHist("TimeDiff_Prompt","Prompt Gated Hit2 time - Hit1 time; Time Difference [4 ns]; Energy [keV]",  
              nbinsT, lowT, highT, (T_branch[0][hit2] - T_branch[0][hit1]), nbinsE, lowE, highE, E_branch[0][hit2]);

              FillHistSym("Matrix_Prompt","Prompt Coincidence Matrix; Energy [keV]; Energy [keV]",
              nbinsE, lowE, highE, E_branch[0][hit1], nbinsE, lowE, highE, E_branch[0][hit2]);
            }
            
            if((fabs(T_branch[0][hit2] - T_branch[0][hit1]) >= ggBGlow) 
            && (fabs(T_branch[0][hit2] - T_branch[0][hit1]) <= ggBGhigh)) {

              FillHist("TimeDiff_Random","Random Gated Hit2 time - Hit1 time; Time Difference [4 ns]; Energy [keV]",  
              nbinsT, lowT, highT, (T_branch[0][hit2] - T_branch[0][hit1]), nbinsE, lowE, highE, E_branch[0][hit2]);

              FillHistSym("Matrix_Random","Random Background Coincidence Matrix; Energy [keV]; Energy [keV]",
              nbinsE, lowE, highE, E_branch[0][hit1], nbinsE, lowE, highE, E_branch[0][hit2]);
            } 
	  }
        } // End hit2 loop
		
    } // End hit1 loop

    if((entry%15000)==0) {
      printf("Working on ...   %lu / %lu   entries           \r", entry, maxEntries);
      fflush(stdout);
    }

  } //End entry loop

  printf("Working on ...   %lu / %lu   entries           \n", entry, maxEntries);
  fflush(stdout);


  Subtract("Matrix_Prompt","Matrix_Random","Matrix_Sub","Background Subtracted Coincidence Matrix; Energy [keV]; Energy [keV]", ggScale);

  return;
}

std::vector<std::string> RootFiles;

class Notifier : public TObject {
  public:
    Notifier() { }
    ~Notifier() { }

    void AddChain(TChain *chain)       { fChain = chain; }
    void AddRootFile(std::string name) { RootFiles.push_back(name); }

  private:
    TChain *fChain;
    std::vector<std::string> RootFiles;
};


Notifier *notifier = new Notifier;
void OpenRootFile(std::string filename) {
  TFile f(filename.c_str());
  if(f.Get("ids")) {
    if(!gChain) {
      gChain = new TChain("ids");
      notifier->AddChain(gChain);
      gChain->SetNotify(notifier);
    }
    gChain->Add(filename.c_str());
    std::cout << "Added: " << filename << std::endl;
  }

}


void AutoFileDetect(std::string filename)  {
  size_t dot_pos = filename.find_last_of('.');
  std::string ext = filename.substr(dot_pos+1);
  if(ext=="root") {
    OpenRootFile(filename);
  } else {
    fprintf(stderr,"discarding unknown file: %s\n",filename.c_str());
  }
}

#ifndef __CINT__
int main(int argc,char **argv) {
  for(int i=1;i<argc;i++) 
    AutoFileDetect(argv[i]); 

  if(!gChain || !gChain->GetEntries()) {
    fprintf(stderr,"failed to find stuff to sort, exiting.\n");
    return 0;
  }
  std::string fname = gChain->GetCurrentFile()->GetName();
  int runnum = GetRunNumber(fname.c_str());

  printf("\nStarting Run %03i with %i file(s) \n\n",runnum,gChain->GetNtrees()); fflush(stdout);

  MakeHistos(); 

  if(outlist && outlist->GetEntries()>0) {
    TFile *file = new TFile(Form("histo_%03i.root",runnum),"recreate");
    outlist->Sort();

    TIter iter(outlist);
    while(TObject *obj = iter.Next()) {
      printf("Writing %s\n",obj->GetName()); fflush(stdout);
      obj->Write();
    }
    file->Close();
  }

  return 0;
}

#endif


