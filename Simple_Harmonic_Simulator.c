/**
* Name: Simple_Harmonic_Simulator.c
* Purpose: Simulate the SHM of a spring mass sytem and generate
* position, velocity, and time steps.
* Author: CplusX-Builder
**/

/*---Initial Conditions---*/
#define MASS 1.0
#define INITIAL_LENGTH_OF_SPRING 5.0
#define DRAG_COEFFICIENT 0.5
#define LENGTH_OF_TABLE 15.0
#define SPRING_CONSTANT 25.0
#define KINETIC_FRICTION_COEFFICIENT 0.5
#define ACCELERATION_DUE_TO_GRAVITY 9.80

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main (void)
{
    /*1. After leaving the mass with a force f(t)*/
    double v0 = 0.001;
    double x0 = 7.0;
    double time = 0.0; //this is the starting time.

    /*2. Time Steps*/
    double dt = 1.0;
    double totalSimulationTime = 60.0;

    printf("\n\t\t====== HORIZONTAL MASS SPRING SIMULATOR =======");
    printf("\nTime\t | Position\t | Velocity\n");

    /*3. Simulation Loop*/
    while (time < totalSimulationTime)
    {
        double F_res = - ((SPRING_CONSTANT) * (x0 - INITIAL_LENGTH_OF_SPRING));
        double F_drag = - ((DRAG_COEFFICIENT) * v0);

        double normalForce = ACCELERATION_DUE_TO_GRAVITY * MASS;
        double F_fric = 0.0;

        if (fabs(v0) > 1e-4)
        {
            //box is moving
            F_fric = - KINETIC_FRICTION_COEFFICIENT * normalForce * (v0 > 0 ? 1.0 : - 1.0);
        } else {
            //box is slowly going to rest
            double drivingForce = F_drag + F_res;
            if (fabs(drivingForce) <= KINETIC_FRICTION_COEFFICIENT * normalForce)
            {
                v0 = 0.0;
                if (fabs(INITIAL_LENGTH_OF_SPRING - x0) < 1e-3) break;
            }
        }

        double F_net = F_res + F_drag + F_fric;

        /*Applying Newton's Law, F = ma*/
        double accelarationOfMass = F_net / MASS;

        /*Updating the starting coordinates (Euler's Method)*/
        double V_new = v0 + accelarationOfMass * dt;
        double X_new = x0 + V_new * dt;
        time = time + dt;

        if (x0 < 0.0)
        { x0 = 0.0;
          v0 = 0.0;
        }
        if (x0 > LENGTH_OF_TABLE)
        {
            x0 = LENGTH_OF_TABLE;
            v0 = 0.0;
        }
        /*Display the variables every 1.0 seconds*/

        if ((int)(time * 1000) % 100 == 0)
        {
            printf("%ld\t | %ld\t | %ld\n", time, X_new, V_new);
        }
    }
return 0;
}
