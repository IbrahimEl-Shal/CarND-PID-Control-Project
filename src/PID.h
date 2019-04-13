#ifndef PID_H
#define PID_H

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  /**
   * With twiddle the PID controller converges faster.
   * We Try tuning twiddle and see if you can reduce the overshoot.
   * @output The Average PID error
   */
  void Twiddle(double tol);
 
  //private:
  
  int Counter = 0; 
  double p[3] = {0, 0, 0};    // initial p vector 
  double dp[3] = {0.1, 0.1, 0.1};   // dp vector: Vector of potential changes 
  
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;
  
  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;
};

#endif  // PID_H