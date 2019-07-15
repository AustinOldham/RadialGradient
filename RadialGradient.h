//Copyright 2019 Austin Oldham
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef RADIALGRADIENT_H_
#define RADIALGRADIENT_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>
#include <fstream>

class RadialGradient {
	public:
		const double PI = std::atan(1.0)*4;
		RadialGradient();
		std::vector<std::vector<int>> getGradient();
		void altNormalRadialGradient(int width, int height, int smallest = 0, int largest = 255);
		void normalRadialGradient(int width, int height, int smallest = 0, int largest = 255);
		void ovalRadialGradient(int width, int height, int smallest = 0, int largest = 255);
		void squareRadialGradient(int width, int height, int smallest = 0, int largest = 255);
		void rectangularRadialGradient(int width, int height, int smallest = 0, int largest = 255);
		void decreasingRadialGradient(int width, int height, int smallest = 0, int largest = 255, double n = 2.0);
		void replaceAbove(int threshold, int newValue);
		void invert();
		void grayscaleGradientToPPM(std::string fileName);
		static double adjustRange(double oldNum, double oldMin, double oldMax, double newMin, double newMax);
	private:
		std::vector<std::vector<int>> gradient;
		int smallest;
		int largest;  // The largest number allowed for the color (e.g. 255)
		bool initialized;
		static double radialDistance(int x, int y, double centerX, double centerY);
		static double radialDistance(double x, double y, double centerX, double centerY);
		static double decreasingFunction(double oldNum, double oldMin, double oldMax, double newMin, double newMax, double n);
};

#endif  // RADIALGRADIENT_H_
