void plot_xtalHit_byCalo(){


    gStyle->SetOptStat(0);
    gStyle->SetTitleH(0.0);
    TFile *file = new TFile("gm2ringsim_truth_32M.root");

    TH1D *xtalHit[24][54];
    TPaveStats *st[54];


    TCanvas *c1 = new TCanvas("c1","c1",800,600);
    c1->SetLogy();
   
    int xtalNum = 30;

    for(int i =0 ; i<24; i++){
        for(int j =0 ; j<54; j++){
            xtalHit[i][j] = (TH1D*) file->Get(Form("truthAnalyzer/calo%.2dxtalHit%.2d",i,j));
            xtalHit[i][j]->SetBinContent(1,0);
            xtalHit[i][j]->SetTitle("");
            xtalHit[i][j]->SetName(Form("Calo%.2dXtal%.2d",i+1,j));
            xtalHit[i][j]->GetXaxis()->SetRangeUser(0,3000);
            xtalHit[i][j]->GetYaxis()->SetRangeUser(0.5,200000);
            xtalHit[i][j]->GetXaxis()->SetNdivisions(5);
            xtalHit[i][j]->SetLineWidth(2);
            xtalHit[i][j]->GetXaxis()->SetTitle("Edep [MeV]");
            xtalHit[i][j]->GetYaxis()->SetTitle("Count/20 MeV");
        }
    }


    TLegend *leg = new TLegend(0.4,0.5,0.9,0.9);
    leg->SetNColumns(4);
    for(int i=0;i<24;i++){
        if(i==0){    xtalHit[i][xtalNum]->Draw();}
        else xtalHit[i][xtalNum]->Draw("same");
        xtalHit[i][xtalNum]->SetLineColor(i%2+1);
        xtalHit[i][xtalNum]->SetLineColor(i%2+1);
        leg->AddEntry(xtalHit[i][xtalNum],xtalHit[i][xtalNum]->GetName(),"l");
    }

    leg->SetTextSize(0.02);
    leg->Draw();
   
    c1->Print(Form("ESpecXtal%.2dByCalo.pdf",xtalNum));

}
