#include "capacitor.h"
#include <iostream>
#include <cstdlib>
#include <cstddef>   


void constantcurrent(Capacitor *cap, int timesteps, double DT, double I)
{

	std::cout<<"Program for constant current capacitor"<<std::endl;
	
       	cap -> voltage[0] = 0;
	cap -> current[0] = I;
	cap->time[0] = 0;
	
        std::cout<<"Constant current: "<< cap -> current[0] <<std::endl;
	std::cout<<"initial  voltage: "<< cap -> voltage[0] <<std::endl;




	for (int i = 1; i < timesteps; i++)
	{	
		cap->current[i] = I;
		cap->voltage[i] = cap->voltage[i - 1] + (cap->current[i - 1] * DT) / cap->C;			    cap->time[i] = i;	
		if (i % 200 == 0)
		{
			std::cout << "Time: " << i << std::endl;
			std::cout << "Voltage: " << cap->voltage[i] << std::endl;
			std::cout << "Current:  " << cap->current[i] << std::endl;
			std::cout << std::endl;
		}
	}

}


void constantvoltage(Capacitor* cap, int timesteps, double DT, double V0, double R)
{
	std::cout << "Program for constant voltage capacitor" << std::endl;
	
	cap -> voltage[0] = 0;
	cap -> current[0] = V0 / R;
	cap->time[0] = 0;

	std::cout << "Initial current: " << cap->current[0] << std::endl;
	std::cout << "Initial voltage: " << cap->voltage[0] << std::endl;

	for (int i = 1; i < timesteps; i++)
	{
		cap->current[i] = cap->current[i - 1] - (cap->current[i - 1] * DT) / (R * cap->C); 
		cap->time[i] = i;
		cap->voltage[i] = V0 - cap->current[i] * R;
		
                if (i % 200 == 0)
                {
                        std::cout << "Time: " << i << std::endl;
			std::cout << "Voltage: " << cap->voltage[i] << std::endl;
                        std::cout << "Current:  " << cap->current[i] << std::endl;
			std::cout << std::endl;
                }

	
	}




}

int main()
{
        double DT = 1e-10;
        double FT= 5e-6;
        int timesteps = 50000;
        double R = 1e3;
        double c = 100e-12;
        double I = 1e-2;
        double V0 = 10.0;





        Capacitor *cap = (Capacitor *)malloc(sizeof(Capacitor));
        
        if (cap == NULL)
	{
        std::cout<<"Allocation of memory failed"<<std::endl;
        return 1;
        }


        cap -> time = (double *)malloc(timesteps * sizeof(double));
        cap -> voltage = (double *)malloc(timesteps * sizeof(double));
        cap -> current = (double *)malloc(timesteps * sizeof(double));
        cap -> C = c;


	constantcurrent(cap, timesteps, DT, I);
	constantvoltage(cap, timesteps, DT, V0, R);
   	


	free(cap->time);
    	free(cap->voltage);
   	free(cap->current);
	free(cap);

	return 0;
	
}

	




