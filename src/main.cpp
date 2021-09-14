#include <pthread.h>
#include <iostream>
#include <vector> 
#include <time.h>

#include "fdcl/common_types.hpp"
#include "fdcl/matrix_utils.hpp"
#include "fdcl/vicon.hpp"

#define NUM_THREADS 4
pthread_mutex_t obs_mutex;

fdcl_vicon VICON;

bool SYS_ON = true;
struct timespec tspec_init, tspec_curr;


void *vicon_thread(void *thread_id)
{
    std::cout << "VICON: starting thread .." << std::endl;

    VICON.open();
    while (SYS_ON) VICON.loop();
    VICON.close();

    std::cout << "VICON: thread closed!" << std::endl;
    pthread_exit(NULL);
}

double get_time()
{
    double t;
    clock_gettime(CLOCK_REALTIME, &tspec_curr);
    t=(double) tspec_curr.tv_sec+ ((double)tspec_curr.tv_nsec)/1.e9;
    t-=(double) tspec_init.tv_sec+ ((double)tspec_init.tv_nsec)/1.e9;
    return t;
}


int main(int argc, char **argv)
{
    std::cout << "Starting program .." << std::endl;

    VICON.open();
    while (SYS_ON)
    {
        VICON.loop();
    }
    VICON.close();

    std::cout << "Program closed!" << std::endl;

    return 0;
}
