#ifndef MEASTRACK_H
#define MEASTRACK_H

#include <vector>

struct MeasPoint
{
	std::vector<float> x;
	std::vector<float> tx; // tan(scatter)
};

struct MeasTrack
{
	std::vector<MeasPoint> Track;
};

#endif // 0
