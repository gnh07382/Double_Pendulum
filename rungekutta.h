#pragma once

template <typename func, typename state>
class movement								//Includes Runge-Kutta and position prediction
{
private:
	std::list<state> move;	//in this case (LIFO, But not queue) list is fastest

	void RungeKutta(func& sys, int timestep, double stepsize)//4th order Runge-kutta for any type
	{
		state k1 = { 0.0, }, k2 = { 0.0, }, k3 = { 0.0, }, k4 = { 0.0, };

		for (size_t i = 0; i < timestep; i++)
		{
			state temp = move.back();

			k1 = stepsize * sys(temp);

			k2 = stepsize * sys(temp + (0.5 * k1));

			k3 = stepsize * sys(temp + (0.5 * k2));

			k4 = stepsize * sys(temp + k3);

			temp = temp + ((k1 + (2.0 * k2) + (2.0 * k3) + k4) / 6.0);

			move.push_back(temp);
		}
	}

public:
	movement(double theta, double pi, int timestep, double stepsize)// creates first prediction
	{
		state m = { theta, pi, 0.0, 0.0 };
		move.push_back(m);

		func sys;
		RungeKutta(sys, timestep, stepsize);
	};

	void calcsteps(int timestep, double stepsize)//calculates prediction steps
	{
		func sys;
		RungeKutta(sys, timestep, stepsize);
	}

	state getcurrentstep()//return state
	{
		state temp = move.front();
		return temp;
	}

	int stepnum()//return step number
	{
		return move.size();
	}

	void deletesteps(int number)//delete steps
	{
		for (size_t i = 0; i < number; i++)
			move.pop_front();
	}
};
