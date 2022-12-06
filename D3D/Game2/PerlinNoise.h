#pragma once
class PerlinNoise
{
	vector<int> p;
private:

	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y);
	double grad(int hash, double x, double y, double z);
public:
	PerlinNoise();
	PerlinNoise(unsigned int seed);
	double noise(double x, double y);
	double noise(double x, double y, double z);
};

