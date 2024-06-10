#include "./HeaderFile/MeasTrack.h"
#include "./HeaderFile/MeasData.h"
#include <iostream>

#include "TFile.h"
#include "TString.h"
#include "TTree.h"


const int Det = 10; // const

void GetData::SetiDet(int &i)
{
	iDet = i;
}
void GetData::SetjEvent(int &j)
{
	jEvent = j;
}

void GetData::GetDataFromRootFile(MeasTrack &measTrack) const // Save value Position x
{
	TFile *f = new TFile("scattering.root");
	for (int i = 0; i < Det; i++)
	{
		TString treeName = Form("VirtualDetector/Det%d", i + 1);
		TTree *tree = static_cast<TTree*> (f -> Get(treeName));
		for (int entry = 0; entry < tree -> GetEntries(); entry++)
		{
			float xMeas;
			tree -> SetBranchAddress("x", &xMeas);
			tree -> GetEntry(entry);

			measTrack.Track[i].x.push_back(xMeas);
		}
	}
}

void GetData::CaculateAndSaveScatter(MeasTrack &measTrack) const // tx = deltaX / deltaZ
{
	float txMeas;
	int dz = 300; // const in g4beamline (z2 - z1 = 300)

	float x1 = measTrack.Track[iDet].x[jEvent];
	float x2 = measTrack.Track[iDet + 1].x[jEvent];

	txMeas = (x2 - x1) / dz;

	measTrack.Track[iDet].tx.push_back(txMeas);
}

void GetData::CaculateVariance(MeasTrack &measTrack) const
{
	float Variance = 0;
	float StdDevTx = 0;
	float xMean = 0;
	float txMean = 0;

	for (int i = 0; i < measTrack.Track[iDet].tx.size(); i++)
	{
		xMean += measTrack.Track[iDet].tx[i];
		txMean += atan(measTrack.Track[iDet].tx[i]);
	}
	xMean = xMean / measTrack.Track[iDet].tx.size();
	txMean = txMean / measTrack.Track[iDet].tx.size();

	for (int i = 0; i < measTrack.Track[iDet].tx.size(); i++)
	{
		Variance += pow(measTrack.Track[iDet].tx[i] - xMean, 2);
		StdDevTx += pow(txMean - atan(measTrack.Track[iDet].tx[i]), 2);
	}
	Variance = Variance / measTrack.Track[iDet].tx.size();
	Variance = sqrt(Variance);

	StdDevTx = StdDevTx / measTrack.Track[iDet].tx.size();
	StdDevTx = sqrt(StdDevTx);

//	std::cout << "Variance of Det" << iDet + 1 << ": " << Variance << "\n";
	std::cout << "StdDev of scatter in Det " << iDet + 1 << ": " << StdDevTx << "\n";
}
