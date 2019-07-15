//Copyright 2019 Austin Oldham
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "RadialGradient.h"

using std::vector;
using std::pow;
using std::abs;
using std::sqrt;
using std::atan2;
using std::cout;
using std::string;

RadialGradient::RadialGradient() : smallest(-1), largest(-1), initialized(false) {}

vector<vector<int>> RadialGradient::getGradient() {
	return gradient;
}

void RadialGradient::altNormalRadialGradient(int width, int height, int smallest, int largest) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<int>(width, 0));

	double centerX = width / 2.0;
	double centerY = height / 2.0;

	double tempDistanceX = pow(centerX, 2);
	double tempDistanceY = pow(centerY, 2);
	double max = sqrt(tempDistanceX + tempDistanceY);

	for (int y = 0; y < gradient.size(); y++) {
		for (int x = 0; x < gradient[0].size(); x++) {
			double distance = RadialGradient::radialDistance(x, y, centerX, centerY);
			double value = RadialGradient::adjustRange(distance, 0, max, smallest, largest);
			gradient[y][x] = static_cast<int>(value);
		}
	}
}

void RadialGradient::normalRadialGradient(int width, int height, int smallest, int largest) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<int>(width, 0));

	double centerX = width / 2.0;
	double centerY = height / 2.0;

	double max;  // Maximum allowed value, not the max of centerX and centerY
	if (centerX > centerY) {
		max = centerY;
	} else {
		max = centerX;
	}

	for (int y = 0; y < gradient.size(); y++) {
		for (int x = 0; x < gradient[0].size(); x++) {
			double distance = RadialGradient::radialDistance(x, y, centerX, centerY);
			if (distance > max) {
				distance = max;
			}
			double value = RadialGradient::adjustRange(distance, 0, max, smallest, largest);
			gradient[y][x] = static_cast<int>(value);
		}
	}
}

void RadialGradient::ovalRadialGradient(int width, int height, int smallest, int largest) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<int>(width, 0));

	double centerX = width / 2.0;
	double centerY = height / 2.0;

	double max;
	if (centerX < centerY) {
		max = centerY;
	} else {
		max = centerX;
	}

	double multiplier;
	if (width > height) {
		multiplier = width / height;
	} else {
		multiplier = height / width;
	}

	for (int y = 0; y < gradient.size(); y++) {
		for (int x = 0; x < gradient[0].size(); x++) {
			double distance;
			if (width < height) {
				double tempX = (x - centerX) * multiplier;
				tempX += centerX;
				distance = RadialGradient::radialDistance(tempX, static_cast<double>(y), centerX, centerY);
			} else {
				double tempY = (y - centerY) * multiplier;
				tempY += centerY;
				distance = RadialGradient::radialDistance(static_cast<double>(x), tempY, centerX, centerY);
			}
			if (distance > max) {
				distance = max;
			}
			double value = RadialGradient::adjustRange(distance, 0, max, smallest, largest);
			gradient[y][x] = static_cast<int>(value);
		}
	}
}

void RadialGradient::squareRadialGradient(int width, int height, int smallest, int largest) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<int>(width, 0));

	double centerX = width / 2.0;
	double centerY = height / 2.0;

	double max;
	if (centerX > centerY) {
		max = centerY;
	} else {
		max = centerX;
	}

	for (int y = 0; y < gradient.size(); y++) {
		for (int x = 0; x < gradient[0].size(); x++) {
			double angle = atan2(abs(y - centerY), abs(x - centerX));
			double distance;
			if (angle <= (-3 * PI / 4) || angle > (3 * PI / 4)) {
				distance = abs(centerX - x);
			} else if (angle <= (-1 * PI / 4)) {
				distance = abs(centerY - y);
			} else if (angle <= (PI / 4)) {
				distance = abs(centerX - x);
			} else {
				distance = abs(centerY - y);
			}
			if (distance > max) {
				distance = max;
			}
			double value = RadialGradient::adjustRange(distance, 0, max, smallest, largest);
			gradient[y][x] = static_cast<int>(value);
		}
	}
}

void RadialGradient::rectangularRadialGradient(int width, int height, int smallest, int largest) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<int>(width, 0));

	double centerX = width / 2.0;
	double centerY = height / 2.0;

	double max;
	if (centerX < centerY) {
		max = centerY;
	} else {
		max = centerX;
	}

	double multiplier;
	if (width > height) {
		multiplier = width / height;
	} else {
		multiplier = height / width;
	}

	double bottomLeftAngle = atan2((0 - centerY), (0 - centerX));
	double bottomRightAngle = atan2((0 - centerY), (width - centerX));
	double topLeftAngle = atan2((height - centerY), (0 - centerX));
	double topRightAngle = atan2((height - centerY), (width - centerX));

	for (int y = 0; y < gradient.size(); y++) {
		for (int x = 0; x < gradient[0].size(); x++) {
			double angle = atan2((y - centerY), (x - centerX));
			double distance;
			if (angle <= bottomLeftAngle || angle > topLeftAngle) {
				if (width < height) {
					double tempX = (x - centerX) * multiplier;
					tempX += centerX;
					distance = abs(centerX - tempX);
				} else {
					distance = abs(centerX - x);
				}
			} else if (angle <= bottomRightAngle) {
				if (height < width) {
					double tempY = (y - centerY) * multiplier;
					tempY += centerY;
					distance = abs(centerY - tempY);
				} else {
					distance = abs(centerY - y);
				}
			} else if (angle <= topRightAngle) {
				if (width < height) {
					double tempX = (x - centerX) * multiplier;
					tempX += centerX;
					distance = abs(centerX - tempX);
				} else {
					distance = abs(centerX - x);
				}
			} else {
				if (height < width) {
					double tempY = (y - centerY) * multiplier;
					tempY += centerY;
					distance = abs(centerY - tempY);
				} else {
					distance = abs(centerY - y);
				}
			}
			if (distance > max) {
				distance = max;
			}
			double value = RadialGradient::adjustRange(distance, 0, max, smallest, largest);
			gradient[y][x] = static_cast<int>(value);
		}
	}
}

void RadialGradient::decreasingRadialGradient(int width, int height, int smallest, int largest, double n) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<int>(width, 0));

	double centerX = width / 2.0;
	double centerY = height / 2.0;

	double max;
	if (centerX > centerY) {
		max = centerY;
	} else {
		max = centerX;
	}

	for (int y = 0; y < gradient.size(); y++) {
		for (int x = 0; x < gradient[0].size(); x++) {
			double distance = RadialGradient::radialDistance(x, y, centerX, centerY);
			if (distance > max) {
				distance = max;
			}
			double value = RadialGradient::decreasingFunction(distance, 0, max, smallest, largest, n);
			gradient[y][x] = static_cast<int>(value);
		}
	}
}

void RadialGradient::replaceAbove(int threshold, int newValue) {
	for (int x = 0; x < gradient.size(); x++) {
		for (int y = 0; y < gradient[0].size(); y++) {
			if (gradient[x][y] > threshold) {
				gradient[x][y] = newValue;
			}
		}
	}
}

void RadialGradient::invert() {
	if (!initialized) {
		throw std::logic_error("No gradient has been created yet");
	}
	for (int x = 0; x < gradient.size(); x++) {
		for (int y = 0; y < gradient[0].size(); y++) {
			gradient[x][y] = largest - gradient[x][y] + smallest;
		}
	}
}

void RadialGradient::grayscaleGradientToPPM(string fileName) {
	std::ofstream myFile;
	myFile.open(fileName + ".ppm");
	myFile << "P3";
	myFile << " ";
	myFile << gradient[0].size();
	myFile << " ";
	myFile << gradient.size();
	myFile << " ";
	myFile << 255;
	myFile << "\n";

	for (int i = 0; i < gradient.size(); i++) {
		for (int j = 0; j < gradient[0].size(); j++) {
			myFile << gradient[i][j];
			myFile << " ";
			myFile << gradient[i][j];
			myFile << " ";
			myFile << gradient[i][j];
			myFile << " ";
		}
		myFile << "\n";
	}
	myFile.close();
}

double RadialGradient::adjustRange(double oldNum, double oldMin, double oldMax, double newMin, double newMax) {
	return ((((newMax - newMin) * (oldNum - oldMin)) / (oldMax - oldMin)) + newMin);
}

double RadialGradient::radialDistance(int x, int y, double centerX, double centerY) {
	double distanceX = pow(abs(centerX - x), 2);
	double distanceY = pow(abs(centerY - y), 2);
	return sqrt(distanceX + distanceY);
}

double RadialGradient::radialDistance(double x, double y, double centerX, double centerY) {
	double distanceX = pow(abs(centerX - x), 2);
	double distanceY = pow(abs(centerY - y), 2);
	return sqrt(distanceX + distanceY);
}

double RadialGradient::decreasingFunction(double oldNum, double oldMin, double oldMax, double newMin, double newMax, double n) {
	double value = RadialGradient::adjustRange(oldNum, oldMin, oldMax, 0.000001, 0.999999);
	if (value != 1) {
		value = pow((1 - value), (1 / n));
	}
	return RadialGradient::adjustRange(value, 0.000001, 0.999999, newMin, newMax);
}
