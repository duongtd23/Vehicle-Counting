// managedDllWrapper.h
/**
 * wrapper function from c++ to c#
 */

#pragma once
#include "../Vehicle_Counting/VehicleCounting.h"
#include "../Vehicle_Counting/VehicleCounting.cpp"
#include "msclr\marshal_cppstd.h"
using namespace System;

namespace CppWrapper {

	public ref class MyVehicleCountingWrapper
	{
	public:
		// constructor
		MyVehicleCountingWrapper(System::String^ input);

		// wrapper methods
		int functionMain(System::String^ ouput);
		int CppWrapper::MyVehicleCountingWrapper::getMotorCount();

	private:
		MyVehicleCounting *myVehicleCounting; // an instance of class in C++
	};
}
