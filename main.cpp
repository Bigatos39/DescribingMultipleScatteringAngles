#include <iostream>

#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TMath.h"
#include "TRint.h"

#include "./HeaderFile/MeasTrack.h"
#include "MeasData.cc"

double GausFunc(double *x, double *par)
{
	return ((1.0 / (par[1] * sqrt(2 * TMath::Pi()))) * exp(-0.5 * pow((x[0] - par[0]) / par[1], 2)) * par[2]);
}
double GaussianSumFilterW3(double *x, double *par) // w = 3
{
	return GausFunc(x, par) + GausFunc(x, &par[3]) + GausFunc(x, &par[6]);
}
double GaussianSumFilterW4(double *x, double *par) // w = 4
{
	return GausFunc(x, par) + GausFunc(x, &par[3]) + GausFunc(x, &par[6]) + GausFunc(x, &par[9]);
}
double GaussianSumFilterW5(double *x, double *par) // w = 5
{
	return GausFunc(x, par) + GausFunc(x, &par[3]) + GausFunc(x, &par[6]) + GausFunc(x, &par[9]) + GausFunc(x, &par[12]);
}
double GaussianSumFilterW6(double *x, double *par) // w = 6
{
	return GausFunc(x, par) + GausFunc(x, &par[3]) + GausFunc(x, &par[6]) + GausFunc(x, &par[9]) + GausFunc(x, &par[12]) + GausFunc(x, &par[15]);
}

int main()
{
	TRint app("myApp",0,0);
	int Det = 10;
	MeasTrack measTrack;
	measTrack.Track.resize(Det);

	GetData gd;
	gd.GetDataFromRootFile(measTrack);

	TCanvas *c = new TCanvas();
	TH1 *h1 = new TH1F("","",100,-1.5,1.5);

	// Get Meas State Vector: r(x, tx)
	for (int i = 0; i < Det; i++)
	{
		int Nevent = measTrack.Track[i].x.size();
		gd.SetiDet(i);

		for (int j = 0; j < Nevent; j++)
		{
			gd.SetjEvent(j);

			if (i == 9)
			{
				break;
			}
			gd.CaculateAndSaveScatter(measTrack);

			h1 -> Fill(atan(measTrack.Track[i].tx[j]));
		}
	}
	float sigmaScatter = h1 -> GetStdDev();
	TF1 *fitFunc3 = new TF1("fitFunc3", GaussianSumFilterW3, -1.5, 1.5, 9);
	double param3[] = {0., sigmaScatter, 1, 0., sigmaScatter * 10, 1, 0., sigmaScatter * 30, 1};
	fitFunc3 -> SetParameters(param3);

	TF1 *fitFunc4 = new TF1("fitFunc4", GaussianSumFilterW4, -1.5, 1.5, 13);
	double param4[] = {0., sigmaScatter, 1, 0., sigmaScatter * 10, 1, 0., sigmaScatter * 30, 1, 0., sigmaScatter * 60, 1};
	fitFunc4 -> SetParameters(param4);

	TF1 *fitFunc5 = new TF1("fitFunc5", GaussianSumFilterW5, -1.5, 1.5, 16);
	double param5[] = {0., sigmaScatter, 1, 0., sigmaScatter * 10, 1, 0., sigmaScatter * 30, 1, 0., sigmaScatter * 60, 1, 0., sigmaScatter * 90, 1};
	fitFunc5 -> SetParameters(param5);

	TF1 *fitFunc6 = new TF1("fitFunc6", GaussianSumFilterW6, -1.5, 1.5, 19);
	double param6[] = {0., sigmaScatter, 1, 0., sigmaScatter * 10, 1, 0., sigmaScatter * 30, 1, 0., sigmaScatter * 60, 1, 0., sigmaScatter * 90, 1, 0., sigmaScatter * 120, 1};
	fitFunc6 -> SetParameters(param6);

	c -> cd();
	h1 -> Draw();
//	h1 -> Fit(fitFunc3);
//	fitFunc3 -> Draw("same");
//	fitFunc3 -> SetLineColor(kBlue);

//	h1 -> Fit(fitFunc4);
//	fitFunc4 -> Draw("same");
//	fitFunc4 -> SetLineColor(kGreen + 2);

	// fith Gaus Function is the best
	h1 -> Fit(fitFunc5);
	fitFunc5 -> Draw("same");
	fitFunc5 -> SetLineColor(kRed);
	fitFunc5 -> SetLineWidth(4);

//	h1 -> Fit(fitFunc6);
//	fitFunc6 -> Draw("same");
//	fitFunc6 -> SetLineColor(kYellow);

	gPad -> SetLogy();
	c -> SaveAs("Figures/Coulomb Multiple Scattering-GSF.png");

	c -> Modified();
	c -> Update();

//	std::cout << "Chi2 (w = 3): " << fitFunc3 -> GetChisquare() << std::endl;
//	std::cout << "Chi2 (w = 4): " << fitFunc4 -> GetChisquare() << std::endl;
	std::cout << "Chi2 (w = 5): " << fitFunc5 -> GetChisquare() << std::endl;
//	std::cout << "Chi2 (w = 6): " << fitFunc6 -> GetChisquare() << std::endl;

	// Result ChiSquare of GaussianSumFilter with W = 5 is the Min of all
	// Fifth Gaus Function is the best of GaussianSumFilter (W = 5)

	app.Run();
	return 0;
}
