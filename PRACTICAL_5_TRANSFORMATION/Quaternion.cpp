#include "Quaternion.h"

Quaternion::Quaternion(double w, double x, double y, double z) :
	m_w(w),
	m_x(x),
	m_y(y),
	m_z(z)
{
	pi = acos(-1);
}

Quaternion::Quaternion(double w, Vector v) :
	m_w(w),
	m_y(v.x()),
	m_z(v.y()),
	m_x(v.z())
{
	pi = acos(-1);
}


double Quaternion::w()
{
	return m_w;
}

double Quaternion::x()
{
	return m_x;
}

double Quaternion::y()
{
	return m_y;
}

double Quaternion::z()
{
	return m_z;
}

double Quaternion::modulus()
{
	return sqrt(m_w*m_w + m_x*m_x + m_y*m_y + m_z*m_z);
}

Quaternion Quaternion::normalise()
{
	double m = m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z;
	if (m > 0.001)
	{
		m = sqrt(m);
		return Quaternion(m_w / m, m_x / m, m_y / m, m_z / m);
	}
	else
	{
		return Quaternion(1, 0, 0, 0);
	}
}

Quaternion Quaternion::conjugate()
{
	return Quaternion(m_w, -m_x, -m_y, -m_z);
}

void Quaternion::fromAxisAngle(Vector v, double angleRadian)
{
	double m = v.length();
	if (m > 0.0001)
	{
		double ca = acos(angleRadian / 2);
		double sa = asin(angleRadian / 2);
		m_x = v.x() / m * sa;
		m_y = v.y() / m * sa;
		m_z = v.z() / m * sa;
		m_w = ca;
	}
	else
	{
		m_w = 1; m_x = 0; m_y = 0; m_z = 0;
	}
}

Quaternion Quaternion::multiply(Quaternion q)
{
	double nw = q.w() *  m_w - q.x() *  m_x - q.y() *  m_y - q.z() * m_z;
	double nx = q.w() *  m_x + q.x() *  m_w + q.y() *  m_z - q.z() * m_y;
	double ny = q.w() *  m_y + q.y() *  m_w + q.z() *  m_x - q.x() * m_z;
	double nz = q.w() *  m_z + q.z() *  m_w + q.x() *  m_y - q.y() * m_x;
	return Quaternion(nw, nx, ny, nz);
}

Quaternion Quaternion::copy()
{
	return Quaternion(m_w, m_x, m_y, m_z);
}

Vector Quaternion::rotate(Quaternion q1, Vector pt, int angle)
{
	//method to rotate a vector by using the matrix3 class's rotation and the quaternion, returns a rotated vector
	double length = sqrt(q1.x() * q1.x() + q1.y() * q1.y() + q1.z() * q1.z());//find the length of x y z only not w
	// THIS FUNCTION DOESNT WORK D:
	if (length != 0)//never divide by zero!
	{
		double as = (angle / 2.0) * (pi / 180);
		float a = cos(as);
		Vector vecIdentity = Vector(q1.x() / (float)length, q1.y() / (float)length, q1.z() / (float)length);//finding the identity of the vector using q's x y z as new values for vector 
		double newAngle = cos((angle / 2.0) * (pi / 180.0));//convert to radians
		double sinAngle = sin((angle / 2.0) * (pi / 180.0));//convert to radians
		vecIdentity = vecIdentity.scale(sinAngle);

		Quaternion q = Quaternion((float)newAngle, vecIdentity);//make a new quaternion using an angle and n a vector(identity of it)
		Quaternion r = Quaternion(0, pt);//make a new quaternion using the vector values
		Quaternion qCon = q.conjugate();//getting conjugate by calling the conjugate methid
		Quaternion qInverse = (float)(1 / (q.modulus() * q.modulus())) * qCon;//finding inverse by qCon * 1 / q^2
		Quaternion vectorRotate = (q * r * qInverse);// formula q * r * qInverse to get a rotated vector

		return Vector(vectorRotate.x(), vectorRotate.y(), vectorRotate.z());//returns the rotated vectors
	}
	else
	{
		return Vector(0, 0, 0);
	}
}


Quaternion operator+(Quaternion q1, Quaternion q2)
{
	return Quaternion(q1.w() + q2.w(), q1.x() + q2.x(), q1.y() + q2.y(), q1.z() + q2.z());
}

Quaternion operator-(Quaternion q1)
{
	return Quaternion(-q1.w(), -q1.x(), -q1.y(), -q1.z());
}
Quaternion operator-(Quaternion q1, Quaternion q2)
{
	return Quaternion(q1.w() - q2.w(), q1.x() - q2.x(), q1.y() - q2.y(), q1.z() - q2.z());
}
Quaternion operator*(Quaternion q1, Quaternion q2)
{
	double nw = q1.w() * q2.w() - q1.x() * q2.x() - q1.y() * q2.y() - q1.z() * q2.z();
	double nx = q1.w() * q2.x() + q1.x() * q2.w() + q1.y() * q2.z() - q1.z() * q2.y();
	double ny = q1.w() * q2.y() + q1.y() * q2.w() + q1.z() * q2.x() - q1.x() * q2.z();
	double nz = q1.w() * q2.z() + q1.z() * q2.w() + q1.x() * q2.y() - q1.y() * q2.x();
	return Quaternion(nw, nx, ny, nz);
}
std::string Quaternion::toString()
{	
	return "(" + std::to_string(m_w) + "," + std::to_string(m_x) + "i," + std::to_string(m_y) + "j," + std::to_string(m_z) + "k)";
}