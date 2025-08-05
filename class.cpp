#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
using namespace std;


enum RegistrationStatus {
    ACTIVE,
    MAINTENANCE,
    DECOMMISSIONED
};

struct Telemetry_data {
    double latitude;
    double longitude;
    double speed;
    string engine_status;
    double battery_level;
    double odometer;
    string diagnostics_code;
    long long timestamp;
};

struct Vehicle_data {
    string VIN;
    string manufacture;
    string model;
    string fleetId;
    string owner;
    RegistrationStatus status;
    vector<Telemetry_data> previous_data;
};

struct Alert {
    int id;
    string VIN;
    string type;
    string details;
    long long timestamp;
};

map<string ,Vehicle_data>vehicles;
map<int,Alert>alerts;

int id = 1;
// Create vehicle management all vehicle data
void generate_vehicle(const string& VIN,const string& manu,const string&mod,const string&fl,const string& own, RegistrationStatus status){
    if(vehicles.find(VIN) == vehicles.end()){
        Vehicle_data newV = {VIN,manu,mod,fl,own,status,{}};
        vehicles[VIN] = newV;
    }
}
// list of all vehicle 
vector<Vehicle_data>list_All_vehicle(){
    vector<Vehicle_data>allvehicle;
    for(auto it: vehicles){
        allvehicle.push_back(it.second);
    }
    return allvehicle;
}
//query of data
Vehicle_data*queryVehicle(const string& VIN){
    auto it = vehicles.find(VIN);
    if(it != vehicles.end()){
        return &(it->second);
    }
    return {};
}

void deleteVehicle(const string& VIN){
    vehicles.erase(VIN);
}

void generateAlerts(const string& VIN, const Telemetry_data&data){
    const double speed_limit = 100.0;
    const double low_fuel = 15.0;

    if(data.speed >speed_limit){
        alerts[id++] = {id-1,VIN,"Speed ALerts ","speed exceeded 100 km/h",data.timestamp};
    }
    if(data.battery_level <low_fuel){
        alerts[id++]={id-1,VIN,"Fuel is low","it is below 15%",data.timestamp};
    }
}






































