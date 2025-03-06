void plotAllMaterials() {
  // Global style: make titles and labels large and remove stats box
  gStyle->SetTitleSize(0.06, "XYZ");
  gStyle->SetLabelSize(0.06, "XYZ");
  gStyle->SetOptStat(0);

  TCanvas *c1 = new TCanvas("c1", "Optics Properties", 1200, 800);
  double eff_x[] = {100.0, 120.0, 140.0, 160.0, 180.0, 200.0, 220.0, 240.0, 260.0, 280.0, 
                    300.0, 320.0, 340.0, 360.0, 380.0, 400.0, 420.0, 440.0, 460.0, 480.0, 
                    500.0, 520.0, 540.0, 560.0, 580.0, 600.0, 620.0, 640.0, 660.0, 680.0, 
                    700.0, 720.0, 740.0, 760.0, 780.0, 800.0, 820.0, 840.0, 860.0, 880.0};
  double eff_y[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.065, 0.14, 
                    0.35, 0.42, 0.47, 0.515, 0.559, 0.61, 0.63, 0.61, 0.584, 0.552, 
                    0.52, 0.49, 0.46, 0.43, 0.4, 0.369, 0.338, 0.309, 0.29, 0.27, 
                    0.25, 0.23, 0.21, 0.19, 0.17, 0.15, 0.13, 0.11, 0.09, 0.07};
  int n_eff = sizeof(eff_x)/sizeof(double);
  c1->cd();
  TGraph *gr_eff = new TGraph(n_eff, eff_x, eff_y);
  gr_eff->SetTitle("EFFICIENCY (wavelength); wavelength; Efficiency");
  gr_eff->SetMarkerStyle(20);
  gr_eff->SetMarkerSize(1.2);
  gr_eff->Draw("APL");

  // ======================================================
  // Material: PTP
  // Properties: RINDEX, SCINTILLATION, SCINTILLATION_WLS, ABSLENGTH, RSLENGTH, REEMISSION_PROB
  // ======================================================
  TCanvas *cPTP = new TCanvas("cPTP", "Material: PTP", 1200, 800);
  // 6 pads: 2 rows x 3 columns
  cPTP->Divide(3,2);

  // --- 1) RINDEX (option: wavelength)
  cPTP->cd(1);
  double ptp_rindex_x[] = {106.0, 128.0, 160.0, 305.0, 340.0, 400.0, 425.0, 530.0};
  double ptp_rindex_y[] = {1.65, 1.65, 1.65, 1.65, 1.65, 1.65, 1.65, 1.65};
  int n_ptp_rindex = sizeof(ptp_rindex_x)/sizeof(double);
  TGraph *gr_ptp_rindex = new TGraph(n_ptp_rindex, ptp_rindex_x, ptp_rindex_y);
  gr_ptp_rindex->SetTitle("PTP RINDEX (wavelength); wavelength; RINDEX");
  gr_ptp_rindex->SetMarkerStyle(20);
  gr_ptp_rindex->SetMarkerSize(1.2);
  gr_ptp_rindex->Draw("APL");

  // --- 2) SCINTILLATION (option: dy_dwavelength)
  cPTP->cd(2);
  double ptp_scint_x[] = {200.0, 300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0};
  double ptp_scint_y[] = {0.0, 0.80, 0.60, 0.10, 0.0, 0.0, 0.0, 0.0};
  int n_ptp_scint = sizeof(ptp_scint_x)/sizeof(double);
  TGraph *gr_ptp_scint = new TGraph(n_ptp_scint, ptp_scint_x, ptp_scint_y);
  gr_ptp_scint->SetTitle("PTP SCINTILLATION (dy_dwavelength); dy_dwavelength; SCINTILLATION");
  gr_ptp_scint->SetMarkerStyle(20);
  gr_ptp_scint->SetMarkerSize(1.2);
  gr_ptp_scint->Draw("APL");

  // --- 3) SCINTILLATION_WLS (option: dy_dwavelength)
  cPTP->cd(3);
  double ptp_scintwls_x[] = {106.0, 128.0, 160.0, 305.0, 340.0, 400.0, 425.0, 530.0};
  double ptp_scintwls_y[] = {0.0, 0.0, 0.0, 0.0005, 0.022, 0.002, 0.0005, 0.0};
  int n_ptp_scintwls = sizeof(ptp_scintwls_x)/sizeof(double);
  TGraph *gr_ptp_scintwls = new TGraph(n_ptp_scintwls, ptp_scintwls_x, ptp_scintwls_y);
  gr_ptp_scintwls->SetTitle("PTP SCINTILLATION_WLS (dy_dwavelength); dy_dwavelength; SCINTILLATION_WLS");
  gr_ptp_scintwls->SetMarkerStyle(20);
  gr_ptp_scintwls->SetMarkerSize(1.2);
  gr_ptp_scintwls->Draw("APL");

  // --- 4) ABSLENGTH (option: wavelength)
  cPTP->cd(4);
  double ptp_abslength_x[] = {106.0, 128.0, 160.0, 305.0, 340.0, 400.0, 425.0, 530.0};
  double ptp_abslength_y[] = {5e-4, 5e-4, 5e-4, 0.187, 10000.0, 10000.0, 10000.0, 10000.0};
  int n_ptp_abslength = sizeof(ptp_abslength_x)/sizeof(double);
  TGraph *gr_ptp_abslength = new TGraph(n_ptp_abslength, ptp_abslength_x, ptp_abslength_y);
  gr_ptp_abslength->SetTitle("PTP ABSLENGTH (wavelength); wavelength; ABSLENGTH");
  gr_ptp_abslength->SetMarkerStyle(20);
  gr_ptp_abslength->SetMarkerSize(1.2);
  gr_ptp_abslength->Draw("APL");

  // --- 5) RSLENGTH (option: wavelength)
  cPTP->cd(5);
  double ptp_rs_x[] = {100.0, 200.0, 300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0};
  double ptp_rs_y[] = {2350, 37500, 190000, 600000, 1466000, 3040000, 5631000, 9607000, 15378000};
  int n_ptp_rs = sizeof(ptp_rs_x)/sizeof(double);
  TGraph *gr_ptp_rs = new TGraph(n_ptp_rs, ptp_rs_x, ptp_rs_y);
  gr_ptp_rs->SetTitle("PTP RSLENGTH (wavelength); wavelength; RSLENGTH");
  gr_ptp_rs->SetMarkerStyle(20);
  gr_ptp_rs->SetMarkerSize(1.2);
  gr_ptp_rs->Draw("APL");

  // --- 6) REEMISSION_PROB (option: wavelength)
  cPTP->cd(6);
  double ptp_reemission_x[] = {100.0, 345.0, 370.0, 800.0};
  double ptp_reemission_y[] = {0.9, 0.9, 0.9, 0.9};
  int n_ptp_reemission = sizeof(ptp_reemission_x)/sizeof(double);
  TGraph *gr_ptp_reemission = new TGraph(n_ptp_reemission, ptp_reemission_x, ptp_reemission_y);
  gr_ptp_reemission->SetTitle("PTP REEMISSION_PROB (wavelength); wavelength; REEMISSION_PROB");
  gr_ptp_reemission->SetMarkerStyle(20);
  gr_ptp_reemission->SetMarkerSize(1.2);
  gr_ptp_reemission->Draw("APL");

  cPTP->Update();


  // ======================================================
  // Material: Acrylic
  // Properties: RINDEX, SCINTILLATION, SCINTILLATION_WLS, ABSLENGTH, RSLENGTH, REEMISSION_PROB
  // ======================================================
  TCanvas *cAcrylic = new TCanvas("cAcrylic", "Material: Acrylic", 1200, 800);
  // 6 pads: 2 rows x 3 columns
  cAcrylic->Divide(3,2);

  // --- 1) RINDEX
  cAcrylic->cd(1);
  double acr_rindex_x[] = {106.0, 128.0, 160.0, 305.0, 340.0, 400.0, 425.0, 530.0};
  double acr_rindex_y[] = {1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5};
  int n_acr_rindex = sizeof(acr_rindex_x)/sizeof(double);
  TGraph *gr_acr_rindex = new TGraph(n_acr_rindex, acr_rindex_x, acr_rindex_y);
  gr_acr_rindex->SetTitle("Acrylic RINDEX (wavelength); wavelength; RINDEX");
  gr_acr_rindex->SetMarkerStyle(20);
  gr_acr_rindex->SetMarkerSize(1.2);
  gr_acr_rindex->Draw("APL");

  // --- 2) SCINTILLATION
  cAcrylic->cd(2);
  double acr_scint_x[] = {200.0, 300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0};
  double acr_scint_y[] = {0.0, 0.80, 0.60, 0.10, 0.0, 0.0, 0.0, 0.0};
  int n_acr_scint = sizeof(acr_scint_x)/sizeof(double);
  TGraph *gr_acr_scint = new TGraph(n_acr_scint, acr_scint_x, acr_scint_y);
  gr_acr_scint->SetTitle("Acrylic SCINTILLATION (dy_dwavelength); dy_dwavelength; SCINTILLATION");
  gr_acr_scint->SetMarkerStyle(20);
  gr_acr_scint->SetMarkerSize(1.2);
  gr_acr_scint->Draw("APL");

  // --- 3) SCINTILLATION_WLS
  cAcrylic->cd(3);
  double acr_scintwls_x[] = {106.0, 128.0, 160.0, 305.0, 340.0, 400.0, 425.0, 530.0};
  double acr_scintwls_y[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  int n_acr_scintwls = sizeof(acr_scintwls_x)/sizeof(double);
  TGraph *gr_acr_scintwls = new TGraph(n_acr_scintwls, acr_scintwls_x, acr_scintwls_y);
  gr_acr_scintwls->SetTitle("Acrylic SCINTILLATION_WLS (dy_dwavelength); dy_dwavelength; SCINTILLATION_WLS");
  gr_acr_scintwls->SetMarkerStyle(20);
  gr_acr_scintwls->SetMarkerSize(1.2);
  gr_acr_scintwls->Draw("APL");

  // --- 4) ABSLENGTH
  cAcrylic->cd(4);
  double acr_abs_x[] = {100.0, 200.0, 300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0};
  double acr_abs_y[] = {0.02, 0.5, 20, 500, 2000.0, 10000.0, 20000.0, 30000.0, 40000.0};
  int n_acr_abs = sizeof(acr_abs_x)/sizeof(double);
  TGraph *gr_acr_abs = new TGraph(n_acr_abs, acr_abs_x, acr_abs_y);
  gr_acr_abs->SetTitle("Acrylic ABSLENGTH (wavelength); wavelength; ABSLENGTH");
  gr_acr_abs->SetMarkerStyle(20);
  gr_acr_abs->SetMarkerSize(1.2);
  gr_acr_abs->Draw("APL");

  // --- 5) RSLENGTH
  cAcrylic->cd(5);
  double acr_rs_x[] = {100.0, 200.0, 300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0};
  double acr_rs_y[] = {2350.0, 37000.5, 190000.0, 600000.0, 1466000.0, 3040000.0, 5631000.0, 9607000.0, 15378000.0};
  int n_acr_rs = sizeof(acr_rs_x)/sizeof(double);
  TGraph *gr_acr_rs = new TGraph(n_acr_rs, acr_rs_x, acr_rs_y);
  gr_acr_rs->SetTitle("Acrylic RSLENGTH (wavelength); wavelength; RSLENGTH");
  gr_acr_rs->SetMarkerStyle(20);
  gr_acr_rs->SetMarkerSize(1.2);
  gr_acr_rs->Draw("APL");

  // --- 6) REEMISSION_PROB
  cAcrylic->cd(6);
  double acr_reemission_x[] = {200.0, 345.0, 370.0, 800.0};
  double acr_reemission_y[] = {1.0, 1.0, 1.0, 1.0};
  int n_acr_reemission = sizeof(acr_reemission_x)/sizeof(double);
  TGraph *gr_acr_reemission = new TGraph(n_acr_reemission, acr_reemission_x, acr_reemission_y);
  gr_acr_reemission->SetTitle("Acrylic REEMISSION_PROB (wavelength); wavelength; REEMISSION_PROB");
  gr_acr_reemission->SetMarkerStyle(20);
  gr_acr_reemission->SetMarkerSize(1.2);
  gr_acr_reemission->Draw("APL");

  cAcrylic->Update();


  // ======================================================
  // Material: eljen_WLSP
  // Properties: RINDEX, SCINTILLATION, SCINTILLATION_WLS, ABSLENGTH, SCINTWAVEFORM, SCINT_RISE_TIME, REEMISSION_PROB, SCINTMOD
  // ======================================================
  TCanvas *cEljen = new TCanvas("cEljen", "Material: eljen_WLSP", 1200, 800);
  // 8 pads: use a 2 rows x 4 columns layout
  cEljen->Divide(4,2);

  // --- 1) RINDEX
  cEljen->cd(1);
  double eljen_rindex_x[] = {430.0, 455.0, 480.0, 510.0, 545.0, 589.26};
  double eljen_rindex_y[] = {1.605, 1.6, 1.595, 1.59, 1.585, 1.58};
  int n_eljen_rindex = sizeof(eljen_rindex_x)/sizeof(double);
  TGraph *gr_eljen_rindex = new TGraph(n_eljen_rindex, eljen_rindex_x, eljen_rindex_y);
  gr_eljen_rindex->SetTitle("eljen_WLSP RINDEX (wavelength); wavelength; RINDEX");
  gr_eljen_rindex->SetMarkerStyle(20);
  gr_eljen_rindex->SetMarkerSize(1.2);
  gr_eljen_rindex->Draw("APL");

  // --- 2) SCINTILLATION
  cEljen->cd(2);
  double eljen_scint_x[] = {
    360.0,365.0,370.0,375.0,380.0,385.0,390.0,395.0,400.0,405.0,410.0,415.0,420.0,425.0,430.0,435.0,440.0,
    445.0,450.0,455.0,460.0,465.0,470.0,475.0,480.0,485.0,490.0,495.0,500.0,505.0,510.0,515.0,520.0,
    525.0,530.0
  };
  double eljen_scint_y[] = {
    0.0089,0.04,0.1082,0.38,0.6702,0.8,0.74,0.7118,0.8559,0.99,0.98,0.8,0.6667,0.645,0.623,0.57,0.4956,
    0.4,0.3289,0.28,0.2388,0.21,0.1848,0.15,0.1125,0.09,0.0721,0.06,0.0496,0.038,0.027,0.021,0.0181,
    0.01,0.0089
  };
  int n_eljen_scint = sizeof(eljen_scint_x)/sizeof(double);
  TGraph *gr_eljen_scint = new TGraph(n_eljen_scint, eljen_scint_x, eljen_scint_y);
  gr_eljen_scint->SetTitle("eljen_WLSP SCINTILLATION (dy_dwavelength); dy_dwavelength; SCINTILLATION");
  gr_eljen_scint->SetMarkerStyle(20);
  gr_eljen_scint->SetMarkerSize(1.2);
  gr_eljen_scint->Draw("APL");

  // --- 3) SCINTILLATION_WLS
  cEljen->cd(3);
  double eljen_scintwls_x[] = {
    360.0,365.0,370.0,375.0,380.0,385.0,390.0,395.0,400.0,405.0,410.0,415.0,420.0,425.0,430.0,435.0,440.0,
    445.0,450.0,455.0,460.0,465.0,470.0,475.0,480.0,485.0,490.0,495.0,500.0,505.0,510.0,515.0,520.0,
    525.0,530.0
  };
  double eljen_scintwls_y[] = {
    0.0089,0.04,0.1082,0.38,0.6702,0.8,0.74,0.7118,0.8559,0.99,0.98,0.8,0.6667,0.645,0.623,0.57,0.4956,
    0.4,0.3289,0.28,0.2388,0.21,0.1848,0.15,0.1125,0.09,0.0721,0.06,0.0496,0.038,0.027,0.021,0.0181,
    0.01,0.0089
  };
  int n_eljen_scintwls = sizeof(eljen_scintwls_x)/sizeof(double);
  TGraph *gr_eljen_scintwls = new TGraph(n_eljen_scintwls, eljen_scintwls_x, eljen_scintwls_y);
  gr_eljen_scintwls->SetTitle("eljen_WLSP SCINTILLATION_WLS (dy_dwavelength); dy_dwavelength; SCINTILLATION_WLS");
  gr_eljen_scintwls->SetMarkerStyle(20);
  gr_eljen_scintwls->SetMarkerSize(1.2);
  gr_eljen_scintwls->Draw("APL");

  // --- 4) ABSLENGTH
  cEljen->cd(4);
  double eljen_abs_x[] = {
    280.0,285.0,290.0,295.0,300.0,305.0,310.0,315.0,320.0,325.0,330.0,
    335.0,340.0,345.0,350.0,355.0,360.0,365.0,370.0,375.0,380.0,385.0,390.0,395.0,400.0,405.0,410.0,
    415.0,420.0,425.0,430.0,435.0,440.0
  };
  double eljen_abs_y[] = {
    3.28817572011048,2.75133439718263,2.13990712803064,1.63409373161645,1.22558031227786,0.949388119357074,0.74896268667895,
    0.612790156138932,0.499310950887775,0.426624800552906,0.3643611110099,0.320985038887337,0.285622070588639,0.256788195960208,
    0.242907702360334,0.240738779165503,0.247364333031549,0.264081484983006,0.299585972186438,0.35950273581582,0.449379631418826,
    0.601847672354127,0.842587755514737,1.3481449525453,2.6962899050906,7.09521782318717,53.9257981018119,963.391136801541,
    2450.98039215686,4484.30493273543,9615.38461538462,33333.3333333333,142857.142857143
  };
  int n_eljen_abs = sizeof(eljen_abs_x)/sizeof(double);
  TGraph *gr_eljen_abs = new TGraph(n_eljen_abs, eljen_abs_x, eljen_abs_y);
  gr_eljen_abs->SetTitle("eljen_WLSP ABSLENGTH (wavelength); wavelength; ABSLENGTH");
  gr_eljen_abs->SetMarkerStyle(20);
  gr_eljen_abs->SetMarkerSize(1.2);
  gr_eljen_abs->Draw("APL");

  // --- 5) SCINTWAVEFORM (single point)
  cEljen->cd(5);
  double eljen_wave_x[] = {-1.1};
  double eljen_wave_y[] = {1.0};
  TGraph *gr_eljen_wave = new TGraph(1, eljen_wave_x, eljen_wave_y);
  gr_eljen_wave->SetTitle("eljen_WLSP SCINTWAVEFORM; SCINTWAVEFORM; Value");
  gr_eljen_wave->SetMarkerStyle(20);
  gr_eljen_wave->SetMarkerSize(1.2);
  gr_eljen_wave->Draw("APL");

  // --- 6) SCINT_RISE_TIME (scalar value displayed as text)
  cEljen->cd(6);
  TLatex *tex_rise = new TLatex(0.1, 0.5, "SCINT_RISE_TIME = 0.1");
  tex_rise->SetTextSize(0.06);
  tex_rise->Draw();

  // --- 7) REEMISSION_PROB
  cEljen->cd(7);
  double eljen_reem_x[] = {280.0, 530.0};
  double eljen_reem_y[] = {0.92, 0.92};
  int n_eljen_reem = sizeof(eljen_reem_x)/sizeof(double);
  TGraph *gr_eljen_reem = new TGraph(n_eljen_reem, eljen_reem_x, eljen_reem_y);
  gr_eljen_reem->SetTitle("eljen_WLSP REEMISSION_PROB (wavelength); wavelength; REEMISSION_PROB");
  gr_eljen_reem->SetMarkerStyle(20);
  gr_eljen_reem->SetMarkerSize(1.2);
  gr_eljen_reem->Draw("APL");

  // --- 8) SCINTMOD (single point)
  cEljen->cd(8);
  double eljen_scintmod_x[] = {1.0};
  double eljen_scintmod_y[] = {0.0};
  TGraph *gr_eljen_scintmod = new TGraph(1, eljen_scintmod_x, eljen_scintmod_y);
  gr_eljen_scintmod->SetTitle("eljen_WLSP SCINTMOD; SCINTMOD_value1; SCINTMOD_value2");
  gr_eljen_scintmod->SetMarkerStyle(20);
  gr_eljen_scintmod->SetMarkerSize(1.2);
  gr_eljen_scintmod->Draw("APL");

  cEljen->Update();
}

