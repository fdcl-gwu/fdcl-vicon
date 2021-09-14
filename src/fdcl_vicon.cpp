#include "fdcl/vicon.hpp"


fdcl_vicon::fdcl_vicon()
{
    ;
}


fdcl_vicon::~fdcl_vicon()
{
    if (on)
    {
        fdcl::vicon::close();
    }
}


void fdcl_vicon::close()
{
    delete tracker;
    on = false;
}


void fdcl_vicon::open(std::string object)
{
    tracker = new vrpn_Tracker_Remote(object.c_str());
    tracker -> register_change_handler(NULL, fdcl_vicon::callback);

    std::cout << "VICON: object opened" << std::endl;
}


void fdcl_vicon::open()
{
    open(object);
}


void fdcl_vicon::loop()
{
    tracker->mainloop();
}


void fdcl_vicon::callback(void* userdata, const vrpn_TRACKERCB tdata)
{
    Vector3 x_v;
    Matrix3 R_vm;

    x_v(0)=tdata.pos[0];
    x_v(1)=tdata.pos[1];
    x_v(2)=tdata.pos[2];

    R_vm(0,0) = 1-(2*(tdata.quat[1])*(tdata.quat[1]))
        -(2*(tdata.quat[2])*(tdata.quat[2]));
    R_vm(0,1) = (2*tdata.quat[0]*tdata.quat[1])-(2*tdata.quat[3]*tdata.quat[2]);
    R_vm(0,2) = (2*tdata.quat[0]*tdata.quat[2])+(2*tdata.quat[3]*tdata.quat[1]);
    R_vm(1,0) = (2*tdata.quat[0]*tdata.quat[1])+(2*tdata.quat[3]*tdata.quat[2]);
    R_vm(1,1) = 1-(2*(tdata.quat[0])*(tdata.quat[0]))
        -(2*(tdata.quat[2])*(tdata.quat[2]));
    R_vm(1,2) = (2*(tdata.quat[1])*(tdata.quat[2]))
        -(2*(tdata.quat[3])*(tdata.quat[0]));
    R_vm(2,0) = (2*tdata.quat[0]*tdata.quat[2])-(2*tdata.quat[3]*tdata.quat[1]);
    R_vm(2,1) = (2*tdata.quat[0]*tdata.quat[3])+(2*tdata.quat[2]*tdata.quat[1]);
    R_vm(2,2) = 1-(2*(tdata.quat[0])*(tdata.quat[0]))
        -(2*(tdata.quat[1])*(tdata.quat[1]));

    // You can either just print your data, or add your own callback here.
    // Make sure that the callback is static. 
    // OBS.callback_zed(R_vm, x_v);
}