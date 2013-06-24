/*
 * NAME:        Chelsea Rath
 * INSTRUCTOR:  Dr. Cen LI
 * PROJECT:     Homework 3 - Question 2
 * DUE:         Thursday, 2/21/2013
 * DESSCRIPTON: A program to calculate the magnitude of drive
 *              and direction of turn for a robot's movements.
 *              The robot is equiped with 6 sensors located at
 *              30, 45, -30, -45, -130, and 130 degrees.
 */
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <iomanip>
using namespace std;

#define NUM_SENSORS 6
#define MAX_DISTANCE 10
#define PI 3.14159265
 
typedef struct {
	double magnitude;
	double direction;
} vector;

void readData(int sens[]);
void d2r(double& var);
void r2d(double& var);
void computeVectors(int const sens[], vector v[], double pos[]);
vector repulsive(double d, double D, double deg);
vector summation(vector v[], double pos[]);

int main( int argc, char* argv[] )
{
	// variables
	int sensors[NUM_SENSORS];
	double positions[NUM_SENSORS] = {45,30,-30,-45,-130,130};
	vector vectors[NUM_SENSORS];
	vector sum;

    cout << setprecision(2) << fixed;
	sum.magnitude = 0.0;
	sum.direction = 0.0;
	
	readData(sensors);	// reads the data from user input
	computeVectors(sensors,vectors,positions);	// computes all vectors for turn
	sum = summation(vectors,positions);	// compute the sum vector
	
	printf("The robot should turn %3.2f degrees with a magnitude of %1.2f.\n",
			sum.direction, sum.magnitude);
			
	return 1;
}

/*
 * FUNCTION:    readData
 * PARAMETERS:  int array to hold sensor readings
 * RETURN:      null
 * PURPOSE:     to read in the values from user input and store
 */
 void readData(int sens[])
 {
	for (int i = 0; i < NUM_SENSORS; ++i)
		cin >> sens[i];
	return;
 }
 
 /*
 * FUNCTION:    d2r
 * PARAMETERS:  float value to convert
 * RETURN:      null
 * PURPOSE:     to convert a degree to radian value
 */
 void d2r(double& val)
 {
	val = val * (PI/180);
 }
 
 /*
 * FUNCTION:    r2d
 * PARAMETERS:  float value to convert
 * RETURN:      null
 * PURPOSE:     to convert a radian to degree value
 */
 void r2d(double& val)
 {
	val = val * (180/PI);
 }
  
 /*
 * FUNCTION:    computeVectors
 * PARAMETERS:  sens -> array containing sensor readings
 *              v -> array to store computed vectors
 * RETURN:      null
 * PURPOSE:     to compute the vectors for each sensor
 */
void computeVectors(int const sens[], vector v[], double pos[])
{
    for (int i = 0; i < NUM_SENSORS; ++i)
    {
        v[i] = repulsive(sens[i], MAX_DISTANCE, pos[i]);
    }
    return;
}
 
 /*
 * FUNCTION:    repulsive
 * PARAMETERS:  double d -> the distance from sensor reading
 *              double D -> the max distance for sensor reading
 *              float degree -> the degree to change by
 * RETURN:      vector computed
 * PURPOSE:     to compute the vector with magnitude and distance
 *              the robot should move along according to readings
 */
vector repulsive(double d, double D, double degree)
{
    vector outputVector;

    if (d <= D)
    {
        outputVector.direction = -180 - degree;
        outputVector.magnitude = (D - d)/D;
    }
    else
    {
        outputVector.direction = 0.0;
        outputVector.magnitude = 0.0;
    }

    return outputVector;
}
 
 /*
 * FUNCTION:    summation
 * PARAMETERS:  v -> array to store computed vectors
 * RETURN:      newly summated vector for turn
 * PURPOSE:     to compute the summation of vectors
 */
vector summation(vector v[], double pos[])
{
    // initialize sum to the first vector in array
    vector sum = v[0];
    d2r(pos[0]);
    double sum_pos = pos[0];

    // loop through all values and calculate the sum
    for (int i = 1; i < NUM_SENSORS; ++i)
    {
        if (v[i].magnitude != 0.0)
        {
            d2r(pos[i]);

            // compute the magnitude
            double val1 = (sum.magnitude*cos(sum_pos)) + (v[i].magnitude*cos(pos[i]));
            double val2 = (sum.magnitude*sin(sum_pos)) + (v[i].magnitude*sin(pos[i]));
            sum.magnitude = sqrt(pow(val1,2) + pow(val2,2));

            // compute the direction
            sum.direction = atan2(val2, val1);
            sum_pos = sum.direction;
        }
    }

    // convert the direction to degrees
    r2d(sum.direction);

    return sum;
}
