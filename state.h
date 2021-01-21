#pragma once
#include <iostream>

struct movedata//move state
{
	double theta; //angle 1
	double pi;	//angle 2

	double p1;	//generalized momentum 1
	double p2;	//generalized momentum 2

	movedata operator+(const movedata& ref)const
	{
		movedata temp = { theta + ref.theta , pi + ref.pi, p1 + ref.p1, p2 + ref.p2 };
		return temp;
	}
};

movedata operator*(double frac, movedata t)
{
	movedata temp = { frac * t.theta, frac * t.pi, frac * t.p1, frac * t.p2 };
	return temp;
}

movedata operator/(movedata t, double frac)
{
	movedata temp = { t.theta / frac, t.pi / frac, t.p1 / frac, t.p2 / frac };
	return temp;
}

class System : private movedata
{
public:
	movedata operator()(movedata st)//hamiltonian
	{
		movedata temp;

		double u = m2 / m1;

		double A1 = (st.p1 * st.p2 * std::sin(st.theta - st.pi)) / (m1 * length * length * (1 + u * std::sin(st.theta - st.pi) * std::sin(st.theta - st.pi)));
		double A2 = (st.p1 * st.p1 * u - 2.0 * st.p1 * st.p2 * u * std::cos(st.theta - st.pi) + st.p2 * st.p2 * (1 + u)) * (std::sin(2 * (st.theta - st.pi))) / (2.0 * m1 * length * length * (1 + u * pow(std::sin(st.theta - st.pi), 2.0)));

		temp.theta = (st.p1 - (st.p2 * std::cos(st.theta - st.pi))) / (m1 * pow(length, 2.0) * (1 + u * pow(std::sin(st.theta - st.pi), 2.0)));
		temp.pi = st.p2 * (1 + u) - (st.p1 * u * std::cos(st.theta - st.pi)) / (m1 * pow(length, 2) * (1 + u * pow(std::sin(st.theta - st.pi), 2.0)));
		temp.p1 = -m1 * (1 + u) * 9.806 * length * std::sin(st.theta) - A1 - A2;
		temp.p2 = -m1 * u * 9.806 * length * std::sin(st.pi) + A1 - A2;

		return temp;
	}

private:
	double length = 1.0;

	double m1 = 1.0;
	double m2 = 1.0;
};