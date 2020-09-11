#include<iostream>
#include<vector>
# include<tuple>
#include<numeric>
#include<cmath>
#include<limits>

using namespace std;


class LinearRegressionCPP
{


private:
	vector<double> m_x_vals;
	vector<double> m_y_vals;
	double m_a;
	double m_b;
	double m_num_elems;
	double m_old_error;

	bool isconverged(double a,double b) 
	{
		double error = 0;
		double thresold = 0.01;
		for (int i = 0; i < m_num_elems; i++) 
		{
			error += ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]) * ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);
		}
		error /= m_num_elems;
		cout << "error:\t" << error << "\r\n";
		bool r = (abs(error) > m_old_error - thresold && abs(error) < m_old_error + thresold) ? true : false;
		m_old_error = abs(error);
		return r;
	}

public:
	LinearRegressionCPP(){}
	~LinearRegressionCPP(){}
	LinearRegressionCPP(vector<double> &m_x_vals, vector<double> &m_y_vals) :m_x_vals(m_x_vals), m_y_vals(m_y_vals), m_num_elems(m_y_vals.size()) {}


	void trainalgorithm(int num_iters,double a,double b)
	{
		int iter = 0;
		m_a = a;
		m_b = b;

		while (!isconverged(m_a,m_b) && (iter < num_iters))
		{
			//update the gradient
			double step = 0.02;
			double grad_a = 0;
			double grad_b = 0;

			//compute gradient of error wrt to a
			for (int i = 0; i < m_num_elems; i++) 
			{
				grad_a += m_x_vals[i] * ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);

			}
			grad_a = (2 * grad_a) / m_num_elems;

			//compute gradient of error wrt to b
			for (int i = 0; i < m_num_elems; i++)
			{
				grad_b += m_x_vals[i] * ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);

			}
			grad_b = (2 * grad_b) / m_num_elems;

			m_a = m_a - (step * grad_a);
			m_b = m_b - (step * grad_b);
			cout << "a:\t" << m_a << "b:\t" << m_b << "\r\n";
			cout << "grad_a:\t" << grad_a << "grad_b:\t" << grad_b << "\r\n";
			iter++;


		}

	}


	double regress(double x)
	{
		double r = m_a * x + m_b;
		return r;
	}




}



; int main(int argc, char** argv)
{
	vector<double> y({ 2.8,2.9,7.6,9,8.6 });
	vector<double> x({ 1,2,3,4,5 });

	LinearRegressionCPP lr(x, y);

	lr.trainalgorithm(1000, 3, -10);

	cout << lr.regress(3) << endl;

	return 0;

}