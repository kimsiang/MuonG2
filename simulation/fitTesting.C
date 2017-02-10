void fitTesting(){

    TFile *file = new TFile("gm2ringsim_truth_1.6M.root");

    TH1D *xtalHit;

    TCanvas *c1 = new TCanvas("c1","c1",1800,1200);

    int i = 0; // calo 0
    int j = 26; // xtal 0

    xtalHit = (TH1D*) file->Get(Form("truthAnalyzer/calo%.2dxtalHit%.2d",i,j));

    xtalHit->Draw();

    xtalHit->GetXaxis()->SetRangeUser(0,3000);
    xtalHit->GetYaxis()->SetRangeUser(0.5,6000);
    xtalHit->GetXaxis()->SetNdivisions(5);
    xtalHit->GetXaxis()->SetLabelSize(0.04);
    xtalHit->GetYaxis()->SetLabelSize(0.04);

    int eStart = 500;
    int eRange = 600;

    TF1 *fit = new TF1("fit","[0]+[1]*x",eStart,eStart+eRange);
    xtalHit->Fit("fit","R");

    double y0 = - fit->GetParameter(0)/fit->GetParameter(1);

    cout<<y0<<endl;
}
