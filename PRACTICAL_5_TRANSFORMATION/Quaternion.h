#pragma once
#include "Vector.h"
#include <cmath>

class Quaternion
{
protected:
	double  m_w, m_x, m_y, m_z;
	double pi;

public:
	Quaternion(double m_w = 0, double m_x = 0, double m_y = 0, double m_z = 0);
	Quaternion(double m_w, Vector v);
	std::string toString();
	double w();
	double x();
	double y();
	double z();

	double modulus();
	Quaternion normalise();
	Quaternion conjugate();
	void fromAxisAngle(Vector v, double angleRadian);
	Quaternion multiply(Quaternion q);
	Quaternion copy();
	Vector rotate(Quaternion q1, Vector pt, int angle);
};

Quaternion operator+(Quaternion q1, Quaternion q2);
Quaternion operator-(Quaternion q1);
Quaternion operator-(Quaternion q1, Quaternion q2);
Quaternion operator*(Quaternion q1, Quaternion q2);