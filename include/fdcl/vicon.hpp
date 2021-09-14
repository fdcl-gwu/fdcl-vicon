#ifndef FDCL_VICON_H
#define FDCL_VICON_H

#include <stdio.h>
#include <iostream>
#include <vrpn_Tracker.h>

#include "fdcl_observer.hpp"
#include "misc_matrix_func.hpp"


/** \brief Get data from the VICON system (not documented)
 *
 * Start a connection between the computer and the VICON server to get the
 * measurements from the server.
 */
class fdcl_vicon
{
public:
    fdcl_vicon();
    ~fdcl_vicon();

    std::string object = "body@192.168.10.1";
    static void callback(void* userdata, const vrpn_TRACKERCB tdata);

    bool on = 0;

    void open();
    void open(std::string object);
    void close();
    void loop();

private:
    vrpn_Tracker_Remote *tracker;

};

#endif
