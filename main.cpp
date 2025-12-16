#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <math.h>

#define G 9.8
#define PI 3.14159265358979323846

void printPoints(std::map<int, std::vector<std::vector<double>>>* dict)
{
	for (auto& item : *dict)
	{
		std::cout << std::setw(6) << std::left << item.first;
		std::cout << "X = " << std::setw(10) << std::left << item.second[0][0];
		std::cout << std::setw(4) << std::right << " Z = " << std::setw(10) << std::left << item.second[0][1];
		std::cout << std::setw(4) << std::right << "Vx = " << std::setw(10) << std::left << item.second[1][0];
		std::cout << std::setw(4) << std::right << " Vz = " << std::setw(10) << std::left << item.second[1][1] << std::endl;
	}
}

int main()
{
	typedef std::map<int, std::vector<std::vector<double>>> Mydict;	// { X, Z } { Vx, Vz }
	Mydict dict;

	const int initial_speed = 600; // m/s
	const int angle = 45;	// degrees
	const int freq = 100;

	double radian = angle * (PI / 180);
	double time = 2 * initial_speed * sin(radian) / G;

	dict[0] = { {0, 0}, {initial_speed * cos(radian), initial_speed * sin(radian)} };

	double X = 0;
	double Z = 0;
	double Vx = 0;
	double Vz = 0;

	for (int i = 1; i <= freq; i++)
	{
		X = dict.at(i - 1)[0][0] + dict.at(i - 1)[1][0] * time / freq;
		Z = dict.at(i - 1)[0][1] + dict.at(i - 1)[1][1] * time / freq;
		Vx = dict.at(i - 1)[1][0];
		Vz = dict.at(i - 1)[1][1] - G * time / freq;

		dict[i] = { {X, Z}, {Vx, Vz} };
	}

	printPoints(&dict);

	double height = (initial_speed * initial_speed * sin(radian) * sin(radian)) / (2 * G);
	std::cout << "Height = " << height << std::endl;

	double S = initial_speed * initial_speed * sin(2 * radian) / G;
	std::cout << "S = " << S;

	return 0;
}