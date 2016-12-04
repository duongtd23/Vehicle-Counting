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
		const int COUNT_DOWN_TO_TOP = 1;
		const int COUNT_TOP_TO_DOWN = 0;
		const int COUNT_COMBINE = 2;
		// constructor
		MyVehicleCountingWrapper(System::String^ input, int count_type);

		// wrapper methods
		int functionMain(System::String^ ouput, bool writeVideoOuput);
		int functionMain();

		int CppWrapper::MyVehicleCountingWrapper::getMotorCountTTD();
		int CppWrapper::MyVehicleCountingWrapper::getCarCountTTD();

		int CppWrapper::MyVehicleCountingWrapper::getMotorCountDTT();
		int CppWrapper::MyVehicleCountingWrapper::getCarCountDTT();

		void CppWrapper::MyVehicleCountingWrapper::stopCounting();

	private:
		MyVehicleCounting *myVehicleCounting; // an instance of class in C++
	};
}
