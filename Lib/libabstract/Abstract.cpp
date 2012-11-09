#include "Abstract.hpp"

Managers *_Managers = (Managers *) SINGLETON_ADDRESS;

DriverManager *getDriverManager()
{
	return _Managers->driverManager;
}


NetworkManager *getNetworkManager()
{
	return _Managers->netManager;
}

DeviceManager *getDeviceManager()
{
	return _Managers->deviceManager;
}

TaskManager *getTaskManager()
{
	return _Managers->taskManager;
}

VFSManager *getVFSManager()
{
	return _Managers->vfsManager;
}


