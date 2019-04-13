#include "PID.h"
#include <cmath>
using namespace std;
/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  
  p_error = 0;
  i_error = 0;
  d_error = 0;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  d_error = cte - p_error;
  p_error = cte; 
  i_error = i_error + cte;
  Counter = Counter + 1;
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  double Total_Error = - (Kp * p_error) - (Kd * d_error) - (Ki * i_error); 
  return Total_Error;  // TODO: Add your total error calc here!
}

void PID::Twiddle(double tol)
{
  Kp = p[0];
  Ki = p[1];
  Kd = p[2];
  
  double error = 0;
  double best_error = TotalError();
  double Sum = abs(dp[0]) + abs(dp[1]) + abs(dp[2]); 
  
  while(Sum > tol)
  {
  		for(int i= 2; i< 3; i++) //i=2
    	{
     		p[i] = p[i] + dp[i]; 
    		Kp = p[0];
    		Ki = p[1];
    		Kd = p[2];
    		error = TotalError();
    		if (abs(error) < abs(best_error))
			{
				best_error = error;
       			//Modify our dp to slighty large value
				dp[i] *= 1.1;
			}
    		else
       		{
          		p[i] = p[i] - 2*dp[i];
          		Kp = p[0];
				Ki = p[1];
				Kd = p[2];
				error = TotalError();
          
          		if (abs(error) < abs(best_error))
				{
					best_error = error;
					dp[i] *= 1.1;
				}
				else
				{
					p[i] = p[i] + dp[i];
					dp[i] *= 0.9;
            	}
        	}
  		}
  }
  Kp = p[0];
  Ki = p[1];
  Kd = p[2];
}