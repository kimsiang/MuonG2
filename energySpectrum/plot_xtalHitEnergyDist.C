void plot_xtalHitEnergyDist(){


    gStyle->SetOptStat(1110);
    gStyle->SetTitleH(0.1);
    TFile *file = new TFile("gm2ringsim_truth_32M.root");

    TH1D *xtalHit[24][54];
    TPaveStats *st[54];

    for(int i =0 ; i<24; i++){

	TCanvas *c1 = new TCanvas("c1","c1",1800,1200);
	c1->Divide(9,6);

	for(int j =0 ; j<54; j++){

	    xtalHit[i][j] = (TH1D*) file->Get(Form("truthAnalyzer/calo%.2dxtalHit%.2d",i,j));

	    cout<<xtalHit[i][j]->GetTitle()<<endl;
	    c1->cd(54-j);
	    c1->cd(54-j)->SetLogy();
	    cout<<"entries(before): "<<xtalHit[i][j]->GetEntries()<<endl;
	    xtalHit[i][j]->SetBinContent(1,0);
	    xtalHit[i][j]->ResetStats();
	    cout<<"entries(after): "<<xtalHit[i][j]->GetEntries()<<endl;
	    xtalHit[i][j]->Rebin(1);
	    xtalHit[i][j]->Draw();
	    xtalHit[i][j]->SetLineColor(1);
	    xtalHit[i][j]->SetFillColor(5);
	    xtalHit[i][j]->GetXaxis()->SetRangeUser(0,3000);
	    xtalHit[i][j]->GetYaxis()->SetRangeUser(0.5,40000);
	    xtalHit[i][j]->GetXaxis()->SetNdivisions(5);
	    xtalHit[i][j]->GetXaxis()->SetLabelSize(0.06);
	    xtalHit[i][j]->GetYaxis()->SetLabelSize(0.06);
	    gPad->Modified();
	    gPad->Update();
	    st[j] = (TPaveStats*)c1->cd(54-j)->GetPrimitive("stats");
	    st[j]->SetX1NDC(0.4);
	    st[j]->SetX2NDC(0.9);
	    st[j]->SetY1NDC(0.6);
	    st[j]->SetY2NDC(0.9);
	}

	c1->Print(Form("calo%.2dxtalHitMap.pdf",i));
//delete c1;   
    }

}
