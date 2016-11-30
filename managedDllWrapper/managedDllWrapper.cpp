// This is the main DLL file.
/**
 * wrapper function from c++ to c#
 */

#include "stdafx.h"

#include "managedDllWrapper.h"
#include "../Vehicle_Counting/VehicleCounting.h"
#include "../Vehicle_Counting/VehicleCounting.cpp"

//constructor
CppWrapper::MyVehicleCountingWrapper::MyVehicleCountingWrapper(System::String^ input)
{
	msclr::interop::marshal_context context;
	std::string standardString = context.marshal_as<std::string>(input);
	myVehicleCounting = new MyVehicleCounting(standardString); //initiate C++ class's instance
}

//implement
int CppWrapper::MyVehicleCountingWrapper::functionMain(System::String^ output)
{
	msclr::interop::marshal_context context;
	std::string standardString = context.marshal_as<std::string>(output);
	return myVehicleCounting->functionMain(standardString, false);
}

//implement
int CppWrapper::MyVehicleCountingWrapper::getMotorCount(){
	return myVehicleCounting->getMotorCount();
}
