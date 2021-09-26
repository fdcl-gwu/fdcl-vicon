#ifndef FDCL_VICON_H
#define FDCL_VICON_H

#include <stdio.h>
#include <iostream>
#include <vrpn_Tracker.h>

#include "fdcl/matrix_utils.hpp"


/** \brief Get data from the VICON system (not documented)
 *
 * Start a connection between the computer and the VICON server to get the
 * measurements from the server.
 */
namespace fdcl
{
    
class vicon
{
public:
    vicon();
    ~vicon();

    std::string object = "body@192.168.10.1";
    static void callback(void* userdata, const vrpn_TRACKERCB tdata);

    bool on = false;

    void open();
    void open(std::string object);
    void close();
    void loop();

private:
    vrpn_Tracker_Remote *tracker;

};

}  // end of namespace fdcl

#endif
