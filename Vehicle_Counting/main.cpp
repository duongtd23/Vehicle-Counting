#include "VehicleCounting.h"
using namespace std;
using namespace cv;

int main(){
	char arr[] = "../dataset/yt_be.mp4";
	string str(arr);
	MyVehicleCounting myVehicleCounting = MyVehicleCounting(str);
	myVehicleCounting.functionMain("output/output.avi", false);
}