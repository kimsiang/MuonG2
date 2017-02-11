void fitESpectrum(){

    // Read from a root file
    TFile *file = new TFile("gm2ringsim_truth_1.6M.root");

    // Declare a histogram to store xtalHit from the file
    TH1D *xtalHit;

    // Open a new TCanvas named c1
    TCanvas *c1 = new TCanvas("c1","c1",800,600);

    // Specify which calo and which crystal here
    int i = 0; // calo 0
    int j = 26; // xtal 26

    // Get the xtal hit from here
    xtalHit = (TH1D*) file->Get(Form("truthAnalyzer/calo%.2dxtalHit%.2d",i,j));

    // Get all the xtal hits (sum over 1,296 crystals)
    //xtalHit = (TH1D*) file->Get("truthAnalyzer/xtalhit_edep");

    // Set some ranges and sizes here for better visualization
    xtalHit->GetXaxis()->SetTitle("E [MeV]");
    xtalHit->GetXaxis()->SetRangeUser(0,3500);
    xtalHit->GetXaxis()->SetNdivisions(6);
    xtalHit->GetXaxis()->SetLabelSize(0.04);
    xtalHit->GetYaxis()->SetLabelSize(0.04);

    // Draw the histogram
    xtalHit->Draw();

    /// Starting from here is for the spectrum fitting purpose

    // Specify fit starting point and the range
    int eStart = 800;
    int eRange = 600;

    // Construct a fit function with the eStart and eRange above
    TF1 *fit = new TF1("fit","[0]+[1]*x",eStart,eStart+eRange);

    // Fit the xtalHit histogram with above function
    xtalHit->Fit("fit","REMQ");

    // Extract the crossing point on x-axis (y[x=0] = -a0/a1)
    double y0 = - fit->GetParameter(0)/fit->GetParameter(1);
    
    cout<<"The crossing point on x-axis is "<<y0<<" MeV"<<endl;

    // Draw 2 lines to indicate the start and the end of fitting range
    double yStart = fit->GetParameter(0) + fit->GetParameter(1)*eStart;

    TLine *l1 = new TLine(eStart,0,eStart,2*yStart);
    TLine *l2 = new TLine(eStart+eRange,0,eStart+eRange,2*yStart);
    l1->SetLineWidth(2);
    l2->SetLineWidth(2);
    l1->Draw();
    l2->Draw();

    // Redraw the fit function until the crossing point
    fit->SetRange(eStart,y0);
    fit->Draw("same");
 
    // Indicating the crossing point value on the TPad
    TLatex latex;
    latex.SetTextSize(0.03);
    latex.SetTextColor(2);
    latex.DrawLatex(y0, 0.5*yStart, Form("%4.1f MeV",y0));

}
