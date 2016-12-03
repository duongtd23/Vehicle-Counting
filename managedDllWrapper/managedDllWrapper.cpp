// This is the main DLL file.
/**
 * wrapper function from c++ to c#
 */

#include "stdafx.h"

#include "managedDllWrapper.h"
#include "../Vehicle_Counting/VehicleCounting.h"
#include "../Vehicle_Counting/VehicleCounting.cpp"

//constructor
CppWrapper::MyVehicleCountingWrapper::MyVehicleCountingWrapper(System::String^ input, int count_type)
{
	msclr::interop::marshal_context context;
	std::string standardString = context.marshal_as<std::string>(input);
	myVehicleCounting = new MyVehicleCounting(standardString, count_type); //initiate C++ class's instance
}

//implement
int CppWrapper::MyVehicleCountingWrapper::functionMain(System::String^ output, bool writeVideoOuput)
{
	msclr::interop::marshal_context context;
	std::string standardString = context.marshal_as<std::string>(output);
	return myVehicleCounting->functionMain(standardString, writeVideoOuput);
}

int CppWrapper::MyVehicleCountingWrapper::functionMain()
{
	return myVehicleCounting->functionMain("", false);
}

//implement
int CppWrapper::MyVehicleCountingWrapper::getMotorCountTTD(){
	return myVehicleCounting->getMotorCountTTD();
}
int CppWrapper::MyVehicleCountingWrapper::getCarCountTTD(){
	return myVehicleCounting->getCarCountTTD();
}

int CppWrapper::MyVehicleCountingWrapper::getMotorCountDTT(){
	return myVehicleCounting->getMotorCountDTT();
}
int CppWrapper::MyVehicleCountingWrapper::getCarCountDTT(){
	return myVehicleCounting->getCarCountDTT();
}
void CppWrapper::MyVehicleCountingWrapper::stopCounting(){
	myVehicleCounting->destroy();
}
