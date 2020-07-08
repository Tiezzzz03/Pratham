#include "main.h" // The To function and subsequently all of the functions that call it has been experimentally changed, may need to be fix, reworked, or reverted if it does not work

HOLO::HOLO(){};
PID HOLO::pidLFRR = PID(28, 0.0, .009); // Random numbers right now, need to be tuned 20 P is good
PID HOLO::pidLRRF = PID(28, 0.0, .009); // Random numbers right now, need to be tuned

void HOLO::spinX(double x, voltageUnits units)
{
  ld.spin(fwd, x, units);
  rd.spin(fwd, -x, units);
}

void HOLO::spinY(double y, voltageUnits units)
{
  d.spin(fwd, y, units);
}

double HOLO::toLFRR(double x, double y) // Calculates the cartesian position of wheels that are rotated 45 degrees from the Y-axis (Left Front wheel and Right Rear wheels are parallel and are positioned in a 45 degree again from the usual vertical orientation)
{
  return sin(atan2(y, x) + M_PI_4)*magn(x, y);
}

double HOLO::toLRRF(double x, double y) // Calculates the cartesian position of wheels that are rotated -45 degrees from the Y-axis (Left Rear wheel and Right Front wheels are parallel and are positioned in a -45 degree again from the usual vertical orientation)
{
  return sin(atan2(y, x) - M_PI_4)*magn(x, y);
}

void HOLO::setTarget(double x, double y) // Calculates the (x, y) coordinate parameters into individual wheel positions and sets it equal to its corresponding wheel pid position.
{
  pidLFRR.target = toLFRR(x, y);
  pidLRRF.target = toLRRF(x, y);
}

void HOLO::To() // Possibly can add another parameter that asks for turning degree more implementation details below
{
  double dX = 0;
  double dY = 0;
  double voltsLFRR = 0;
  double voltsLRRF = 0;
  int time = 0;
  int timeout = 80;
  // fps.reset();
  double center[] = {robot.fps.coordinates[0], robot.fps.coordinates[1]};
  while (1) 
  {
    dX = robot.fps.coordinates[0] - center[0];
    dY = robot.fps.coordinates[1] - center[1];
    pidLFRR.position = toLFRR(dX, dY);
    pidLRRF.position = toLRRF(dX, dY);
    voltsLFRR = pidLFRR.calc(pidLFRR.target, pidLFRR.position);
    voltsLRRF = pidLRRF.calc(pidLRRF.target, pidLRRF.position);
    // double tolerance = .01;
    // if(std::abs(pidLFRR.error) < 7 * abs(pidLFRR.derivative) * tolerance)
    //   pidLFRR.integral = 0;
    // if(std::abs(pidLRRF.error) < 7 * abs(pidLRRF.derivative) * tolerance)
    //   pidLRRF.integral = 0;
    // if((target != 0 && position/target < 0) || (position != 0 && target/position < 0))
    // {
    //   integral = 1.5;
    // }
    // if(std::abs(pidLFRR.error) < tolerance && abs(pidLFRR.derivative) < 1 && std::abs(pidLRRF.error) < tolerance && abs(pidLRRF.derivative) < 1)
    // {
    //   goto kill;
    // }
    if(abs(pidLFRR.derivative) < 0.001 && abs(pidLRRF.derivative) < 0.001)
    {
      if(time >= timeout)
        goto kill;
      else
        time += 20;
    }
    if(false)
    {
      kill:
      // cout << "completed" << endl;
      d.stop();
      this_thread::yield();
      break;
    }
    LeftFrontMotor.spin(fwd, voltsLFRR, voltageUnits::volt); // After turning calculations, the motor turning volts calculated can be added/subtracted in the parameter of these spin functions.
    LeftRearMotor.spin(fwd, voltsLRRF, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
  pidLFRR.resetPID();
  pidLRRF.resetPID();
}

void HOLO::For() 
{
  double x = robot.fps.coordinates[0];
  double y = robot.fps.coordinates[1];
  pidLFRR.target += toLFRR(x, y);
  pidLRRF.target += toLRRF(x, y);
  To();
}

void HOLO::To(double x, double y) 
{
  setTarget(x, y);
  To();
}

void HOLO::For(double x, double y) 
{
  setTarget(x, y);
  For();
}

void HOLO::aTo() 
{
  thread async_pid = vex::thread(To);
}

void HOLO::aFor() 
{
  thread async_pid = vex::thread(For);
}

void HOLO::aTo(double x, double y) 
{
  setTarget(x, y);
  aTo();
}

void HOLO::aFor(double x, double y) 
{
  setTarget(x, y);
  aFor();
}

void HOLO::To(double target[])
{
  To(target[0], target[1]);
}

void HOLO::For(double target[])
{
  For(target[0], target[1]);
}

void HOLO::aTo(double target[])
{
  aTo(target[0], target[1]);
}

void HOLO::aFor(double target[])
{
  aFor(target[0], target[1]);
}

void HOLO::driveFor(double x, double y, int speed)
{
  
}

void HOLO::driveFor(double target[], int speed)
{
  
}
