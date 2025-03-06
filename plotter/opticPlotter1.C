// plotProperties_Log.C
// ROOT macro to plot refractive index, emission spectrum, Rayleigh scattering length, and absorption length
// for BK270, EJ286, and PTP over the wavelength range 100 nm to 900 nm.
// The y-axis is set to logarithmic scale and grids are enabled for both x and y.

#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TStyle.h"

void opticPlotter1() {

   // Set some style options
   gStyle->SetOptStat(0);
   gStyle->SetLegendBorderSize(0);

   // Create a canvas divided into 2x2 pads
   TCanvas *c = new TCanvas("c", "Material Properties", 1200, 800);
   c->Divide(2,2);

   // ======================================================
   // 1. Refractive Index vs. Wavelength
   // ------------------------------------------------------
   const Int_t nPoints1 = 9;
   Double_t wave1[nPoints1]  = {100,200,300,400,500,600,700,800,900};
   // Refractive index values (extrapolated in the deep UV for BK270, EJ286, and PTP)
   Double_t n_BK270[nPoints1] = {1.82, 1.64, 1.55, 1.523, 1.515, 1.510, 1.506, 1.504, 1.502};
   Double_t n_EJ286[nPoints1] = {1.63, 1.61, 1.59, 1.58, 1.575, 1.57, 1.565, 1.562, 1.560};
   Double_t n_PTP[nPoints1]   = {1.70, 1.67, 1.66, 1.65, 1.645, 1.640, 1.635, 1.630, 1.628};

   c->cd(1);
   gPad->SetLogy();
   gPad->SetGridx();
   gPad->SetGridy();

   TGraph *grBK270 = new TGraph(nPoints1, wave1, n_BK270);
   grBK270->SetLineColor(kRed);
   grBK270->SetMarkerColor(kRed);
   grBK270->SetMarkerStyle(20);
   grBK270->SetTitle("Refractive Index vs. Wavelength;Wavelength (nm);Refractive Index");
   grBK270->Draw("ALP");

   TGraph *grEJ286 = new TGraph(nPoints1, wave1, n_EJ286);
   grEJ286->SetLineColor(kBlue);
   grEJ286->SetMarkerColor(kBlue);
   grEJ286->SetMarkerStyle(21);
   grEJ286->Draw("LP same");

   TGraph *grPTP = new TGraph(nPoints1, wave1, n_PTP);
   grPTP->SetLineColor(kGreen+2);
   grPTP->SetMarkerColor(kGreen+2);
   grPTP->SetMarkerStyle(22);
   grPTP->Draw("LP same");

   TLegend *leg1 = new TLegend(0.15,0.70,0.35,0.85);
   leg1->AddEntry(grBK270,"BK270","lp");
   leg1->AddEntry(grEJ286,"EJ286","lp");
   leg1->AddEntry(grPTP,"PTP","lp");
   leg1->Draw();

   // ======================================================
   // 2. Emission Spectrum vs. Wavelength
   // ------------------------------------------------------
   const Int_t nPoints2 = 17;
   Double_t wave2[nPoints2] = {100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900};
   // Relative emission intensities (normalized to peak=1.0)
   // BK270: no emission; EJ286: broad emission peaking near 450 nm; PTP: peak near 350 nm.
   // For logarithmic display, replace zeros with a small number (e.g., 1e-5) if desired.
   Double_t em_BK270[nPoints2] = {1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5};
   Double_t em_EJ286[nPoints2] = {1e-5,1e-5,1e-5,0.10,0.30,0.70,0.95,1.00,0.80,0.50,0.20,0.10,0.05,0.02,1e-5,1e-5,1e-5};
   Double_t em_PTP[nPoints2]   = {1e-5,1e-5,1e-5,0.10,0.80,1.00,0.60,0.30,0.10,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5,1e-5};

   c->cd(2);
   gPad->SetLogy();
   gPad->SetGridx();
   gPad->SetGridy();

   TGraph *grEmBK270 = new TGraph(nPoints2, wave2, em_BK270);
   grEmBK270->SetLineColor(kRed);
   grEmBK270->SetMarkerColor(kRed);
   grEmBK270->SetMarkerStyle(20);
   grEmBK270->SetTitle("Emission Spectrum vs. Wavelength;Wavelength (nm);Relative Intensity");
   grEmBK270->Draw("ALP");

   TGraph *grEmEJ286 = new TGraph(nPoints2, wave2, em_EJ286);
   grEmEJ286->SetLineColor(kBlue);
   grEmEJ286->SetMarkerColor(kBlue);
   grEmEJ286->SetMarkerStyle(21);
   grEmEJ286->Draw("LP same");

   TGraph *grEmPTP = new TGraph(nPoints2, wave2, em_PTP);
   grEmPTP->SetLineColor(kGreen+2);
   grEmPTP->SetMarkerColor(kGreen+2);
   grEmPTP->SetMarkerStyle(22);
   grEmPTP->Draw("LP same");

   TLegend *leg2 = new TLegend(0.15,0.70,0.35,0.85);
   leg2->AddEntry(grEmBK270,"BK270 (No Emission)","lp");
   leg2->AddEntry(grEmEJ286,"EJ286","lp");
   leg2->AddEntry(grEmPTP,"PTP","lp");
   leg2->Draw();

   // ======================================================
   // 3. Rayleigh Scattering Length vs. Wavelength
   // ------------------------------------------------------
   const Int_t nPoints3 = 17;
   Double_t wave3[nPoints3] = {100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900};
   // Scattering lengths in meters (order-of-magnitude estimates)
   Double_t sc_BK270[nPoints3] = {4.45, 22.5, 71.2, 174, 360, 667, 1139, 1824, 2780, 4069, 5768, 7944, 10680, 14080, 18220, 23242, 29165};
   Double_t sc_EJ286[nPoints3] = {3.31, 16.8, 52.9, 129, 268, 496, 847, 1358, 2067, 3026, 4287, 5910, 7944, 10470, 13550, 17282, 21662};
   Double_t sc_PTP[nPoints3]   = {2.35, 11.9, 37.5, 91.6, 190, 353, 600, 961, 1466, 2145, 3040, 4192, 5631, 7424, 9607, 12255, 15378};

   c->cd(3);
   gPad->SetLogy();
   gPad->SetGridx();
   gPad->SetGridy();

   TGraph *grScBK270 = new TGraph(nPoints3, wave3, sc_BK270);
   grScBK270->SetLineColor(kRed);
   grScBK270->SetMarkerColor(kRed);
   grScBK270->SetMarkerStyle(20);
   grScBK270->SetTitle("Rayleigh Scattering Length vs. Wavelength;Wavelength (nm);Scattering Length (m)");
   grScBK270->Draw("ALP");

   TGraph *grScEJ286 = new TGraph(nPoints3, wave3, sc_EJ286);
   grScEJ286->SetLineColor(kBlue);
   grScEJ286->SetMarkerColor(kBlue);
   grScEJ286->SetMarkerStyle(21);
   grScEJ286->Draw("LP same");

   TGraph *grScPTP = new TGraph(nPoints3, wave3, sc_PTP);
   grScPTP->SetLineColor(kGreen+2);
   grScPTP->SetMarkerColor(kGreen+2);
   grScPTP->SetMarkerStyle(22);
   grScPTP->Draw("LP same");

   TLegend *leg3 = new TLegend(0.15,0.70,0.35,0.85);
   leg3->AddEntry(grScBK270,"BK270","lp");
   leg3->AddEntry(grScEJ286,"EJ286","lp");
   leg3->AddEntry(grScPTP,"PTP","lp");
   leg3->Draw();

   // ======================================================
   // 4. Absorption Length vs. Wavelength
   // ------------------------------------------------------
   const Int_t nPoints4 = 17;
   Double_t wave4[nPoints4] = {100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900};
   // Absorption lengths in meters (hypothetical values)
   Double_t abs_BK270[nPoints4] = {1e-4, 5e-4, 1e-3, 5e-3, 0.10, 10, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
   Double_t abs_EJ286[nPoints4] = {5e-5, 2e-4, 1e-3, 5e-3, 0.05, 0.20, 1, 2, 5, 10, 15, 20, 25, 30, 35, 40, 45};
   Double_t abs_PTP[nPoints4]   = {2e-5, 1e-4, 5e-4, 2e-3, 0.02, 0.10, 0.5, 1, 2, 5, 10, 15, 20, 25, 30, 35, 40};

   c->cd(4);
   gPad->SetLogy();
   gPad->SetGridx();
   gPad->SetGridy();

   TGraph *grAbsBK270 = new TGraph(nPoints4, wave4, abs_BK270);
   grAbsBK270->SetLineColor(kRed);
   grAbsBK270->SetMarkerColor(kRed);
   grAbsBK270->SetMarkerStyle(20);
   grAbsBK270->SetTitle("Absorption Length vs. Wavelength;Wavelength (nm);Absorption Length (m)");
   grAbsBK270->Draw("ALP");

   TGraph *grAbsEJ286 = new TGraph(nPoints4, wave4, abs_EJ286);
   grAbsEJ286->SetLineColor(kBlue);
   grAbsEJ286->SetMarkerColor(kBlue);
   grAbsEJ286->SetMarkerStyle(21);
   grAbsEJ286->Draw("LP same");

   TGraph *grAbsPTP = new TGraph(nPoints4, wave4, abs_PTP);
   grAbsPTP->SetLineColor(kGreen+2);
   grAbsPTP->SetMarkerColor(kGreen+2);
   grAbsPTP->SetMarkerStyle(22);
   grAbsPTP->Draw("LP same");

   TLegend *leg4 = new TLegend(0.15,0.70,0.35,0.85);
   leg4->AddEntry(grAbsBK270,"BK270","lp");
   leg4->AddEntry(grAbsEJ286,"EJ286","lp");
   leg4->AddEntry(grAbsPTP,"PTP","lp");
   leg4->Draw();

   // Update canvas and optionally save the plot
   c->Update();
   // c->SaveAs("MaterialProperties_Log.png");
}

