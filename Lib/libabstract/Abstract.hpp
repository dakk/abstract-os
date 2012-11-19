#ifndef ABSTRACT_HPP
#define ABSTRACT_HPP

#include <Kernel/Managers.hpp>
#include <kernel.h>

DriverManager *getDriverManager();
NetworkManager *getNetworkManager();
DeviceManager *getDeviceManager();
TaskManager *getTaskManager();
VFSManager *getVFSManager();

#endif





