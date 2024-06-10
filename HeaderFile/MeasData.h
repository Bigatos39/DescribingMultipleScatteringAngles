#ifndef MEASDATA_H
#define MEASDATA_H

#include "MeasTrack.h"

class GetData
{
	public:
		void GetDataFromRootFile(MeasTrack &measTrack) const;
		void CaculateAndSaveScatter(MeasTrack &measTrack) const;
		void CaculateVariance(MeasTrack &measTrack) const;
		void SetjEvent(int &j);
		void SetiDet(int &i);
	private:
		int iDet, jEvent;
};

#endif // 0
