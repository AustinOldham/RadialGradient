//Copyright (C) 2019  Austin Oldham
//
//This file is part of Starogen.
//
//Starogen is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Starogen is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Starogen.  If not, see <https://www.gnu.org/licenses/>.

#ifndef RADIALGRADIENT_H_
#define RADIALGRADIENT_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>
#include <fstream>

template <class T>
class RadialGradient {
	public:
		const double PI = std::atan(1.0)*4;
		std::vector<std::vector<T>> gradient;
		RadialGradient();
		std::vector<std::vector<T>> getGradient();
		void altNormalRadialGradient(int width, int height, T smallest = 0, T largest = 255);
		void normalRadialGradient(int width, int height, T smallest = 0, T largest = 255);
		void ovalRadialGradient(int width, int height, T smallest = 0, T largest = 255);
		void squareRadialGradient(int width, int height, T smallest = 0, T largest = 255);
		void rectangularRadialGradient(int width, int height, T smallest = 0, T largest = 255);
		void decreasingRadialGradient(int width, int height, T smallest = 0, T largest = 255, double n = 2.0);
		void sharpRadialGradient(int width, int height, T smallest = 0, T largest = 255, double sharpMult = 0.5);
		void makeRinged();
		void replaceAbove(T threshold, T newValue);
		void invert();
		void grayscaleGradientToPPM(std::string fileName);
		static double adjustRange(double oldNum, double oldMin, double oldMax, double newMin, double newMax);
	private:
		T smallest;
		T largest;  // The largest number allowed for the color (e.g. 255)
		bool initialized;
		static double radialDistance(int x, int y, double centerX, double centerY);
		static double radialDistance(double x, double y, double centerX, double centerY);
		static double decreasingFunction(double oldNum, double oldMin, double oldMax, double newMin, double newMax, double n);
};

#endif  // RADIALGRADIENT_H_
