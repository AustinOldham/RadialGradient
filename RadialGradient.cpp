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

#include "RadialGradient.h"

using std::vector;
using std::pow;
using std::abs;
using std::sqrt;
using std::atan2;
using std::cout;
using std::string;

template <class T>
RadialGradient<T>::RadialGradient() : smallest(-1), largest(-1), initialized(false) {}

template <class T>
vector<vector<T>> RadialGradient<T>::getGradient() {
	return gradient;
}

template <class T>
void RadialGradient<T>::altNormalRadialGradient(int width, int height, T smallest, T largest) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<T>(width, 0));

	double centerX = width / 2.0;
	double centerY = height / 2.0;

	double tempDistanceX = pow(centerX, 2);
	double tempDistanceY = pow(centerY, 2);
	double max = sqrt(tempDistanceX + tempDistanceY);

	for (int y = 0; y < gradient.size(); y++) {
		for (int x = 0; x < gradient[0].size(); x++) {
			double distance = RadialGradient::radialDistance(x, y, centerX, centerY);
			double value = RadialGradient::adjustRange(distance, 0, max, smallest, largest);
			gradient[y][x] = static_cast<T>(value);
		}
	}
}

template <class T>
void RadialGradient<T>::normalRadialGradient(int width, int height, T smallest, T largest) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<T>(width, 0));

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
			gradient[y][x] = static_cast<T>(value);
		}
	}
}

template <class T>
void RadialGradient<T>::ovalRadialGradient(int width, int height, T smallest, T largest) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<T>(width, 0));

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
			gradient[y][x] = static_cast<T>(value);
		}
	}
}

template <class T>
void RadialGradient<T>::squareRadialGradient(int width, int height, T smallest, T largest) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<T>(width, 0));

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
			gradient[y][x] = static_cast<T>(value);
		}
	}
}

template <class T>
void RadialGradient<T>::rectangularRadialGradient(int width, int height, T smallest, T largest) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<T>(width, 0));

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
			gradient[y][x] = static_cast<T>(value);
		}
	}
}

template <class T>
void RadialGradient<T>::decreasingRadialGradient(int width, int height, T smallest, T largest, double n) {
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<T>(width, 0));

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
			gradient[y][x] = static_cast<T>(value);
		}
	}
}

template <class T>
void RadialGradient<T>::sharpRadialGradient(int width, int height, T smallest, T largest, double sharpMult) {
	//sharpMult must range from 0 to 1
	this->smallest = smallest;
	this->largest = largest;
	this->initialized = true;
	gradient.clear();
	gradient.resize(height, vector<T>(width, 0));

	double centerX = width / 2.0;
	double centerY = height / 2.0;

	double max;
	if (centerX > centerY) {
		max = centerY;
	} else {
		max = centerX;
	}

	double sharpRadius = max * sharpMult;
	double sharpMax = max - sharpRadius;

	for (int y = 0; y < gradient.size(); y++) {
		for (int x = 0; x < gradient[0].size(); x++) {
			/*double multiplier = 0.5;
			double tempX = (x - centerX) * multiplier;
			tempX += centerX;
			double tempY = (y - centerY) * multiplier;
			tempY += centerY;
			double distance = RadialGradient::radialDistance(tempX, tempY, centerX, centerY);*/


			double distance = RadialGradient::radialDistance(x, y, centerX, centerY);
			if (distance > max) {
				distance = max;
			}
			distance = distance - sharpRadius;
			if (distance < 0) {
				distance = 0;
			}

			double value = RadialGradient::adjustRange(distance, 0, sharpMax, smallest, largest);
			gradient[y][x] = static_cast<T>(value);
		}
	}
}

template <class T>
void RadialGradient<T>::makeRinged() {
	for (int y = 0; y < gradient.size(); y++) {
		for (int x = 0; x < gradient[0].size(); x++) {
			if (gradient[y][x] < 0.1) {
				gradient[y][x] = 0.0;
			} else if (gradient[y][x] < 0.2) {
				gradient[y][x] = 0.1;
			} else if (gradient[y][x] < 0.5) {
				gradient[y][x] = 0.4;
			} else if (gradient[y][x] < 0.8) {
				gradient[y][x] = 0.7;
			} else {
				gradient[y][x] = 1.0;
			}
		}
	}
}

template <class T>
void RadialGradient<T>::replaceAbove(T threshold, T newValue) {
	for (int x = 0; x < gradient.size(); x++) {
		for (int y = 0; y < gradient[0].size(); y++) {
			if (gradient[x][y] > threshold) {
				gradient[x][y] = newValue;
			}
		}
	}
}

template <class T>
void RadialGradient<T>::invert() {
	if (!initialized) {
		throw std::logic_error("No gradient has been created yet");
	}
	for (int x = 0; x < gradient.size(); x++) {
		for (int y = 0; y < gradient[0].size(); y++) {
			gradient[x][y] = largest - gradient[x][y] + smallest;
		}
	}
}

template <class T>
void RadialGradient<T>::grayscaleGradientToPPM(string fileName) {
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
			myFile << static_cast<int>(RadialGradient::adjustRange(gradient[i][j], smallest, largest, 0, 255));
			myFile << " ";
			myFile << static_cast<int>(RadialGradient::adjustRange(gradient[i][j], smallest, largest, 0, 255));
			myFile << " ";
			myFile << static_cast<int>(RadialGradient::adjustRange(gradient[i][j], smallest, largest, 0, 255));
			myFile << " ";
		}
		myFile << "\n";
	}
	myFile.close();
}

template <class T>
double RadialGradient<T>::adjustRange(double oldNum, double oldMin, double oldMax, double newMin, double newMax) {
	return ((((newMax - newMin) * (oldNum - oldMin)) / (oldMax - oldMin)) + newMin);
}

template <class T>
double RadialGradient<T>::radialDistance(int x, int y, double centerX, double centerY) {
	double distanceX = pow(abs(centerX - x), 2);
	double distanceY = pow(abs(centerY - y), 2);
	return sqrt(distanceX + distanceY);
}

template <class T>
double RadialGradient<T>::radialDistance(double x, double y, double centerX, double centerY) {
	double distanceX = pow(abs(centerX - x), 2);
	double distanceY = pow(abs(centerY - y), 2);
	return sqrt(distanceX + distanceY);
}

template <class T>
double RadialGradient<T>::decreasingFunction(double oldNum, double oldMin, double oldMax, double newMin, double newMax, double n) {
	double value = RadialGradient::adjustRange(oldNum, oldMin, oldMax, 0.000001, 0.999999);
	if (value != 1) {
		value = pow((1 - value), (1 / n));
	}
	return RadialGradient::adjustRange(value, 0.000001, 0.999999, newMin, newMax);
}

template class RadialGradient<char>;
template class RadialGradient<short>;
template class RadialGradient<uint8_t>;
template class RadialGradient<int>;
template class RadialGradient<float>;
template class RadialGradient<double>;
