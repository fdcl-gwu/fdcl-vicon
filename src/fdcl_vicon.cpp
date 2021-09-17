#include "fdcl/vicon.hpp"


fdcl::vicon::vicon()
{
    ;
}


fdcl::vicon::~vicon()
{
    if (on)
    {
        fdcl::vicon::close();
    }
}


void fdcl::vicon::close()
{
    delete tracker;
    on = false;

    std::cout << "VICON: object closed" << std::endl;
}


void fdcl::vicon::open(std::string object)
{
    tracker = new vrpn_Tracker_Remote(object.c_str());
    tracker -> register_change_handler(NULL, fdcl::vicon::callback);

    std::cout << "VICON: object opened" << std::endl;
}


void fdcl::vicon::open()
{
    open(object);
}


void fdcl::vicon::loop()
{
    tracker->mainloop();
}


void fdcl::vicon::callback(void* userdata, const vrpn_TRACKERCB tdata)
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
    // State.callback_zed(R_vm, x_v);
    std::cout << "\nx_v: " << x_v.transpose() << std::endl;
    std::cout << "R_vm: " << R_vm << std::endl;
}