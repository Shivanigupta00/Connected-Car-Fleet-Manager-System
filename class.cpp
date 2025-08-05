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
//deleted vehicle acc to VIN
void deleteVehicle(const string& VIN){
    vehicles.erase(VIN);
}
//generate Alerts
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
// extract previous data
void extractTelemetry_data(const string&VIN,const Telemetry_data&data){
    Vehicle_data*veh = queryVehicle(VIN);
    if(veh){
        veh->previous_data.push_back(data);
        generateAlerts(VIN,data);
    }else{
        throw runtime_error("vehicle is not found");
    }
}

vector<Telemetry_data>getpreviousdata(const string& VIN){
    Vehicle_data*veh = queryVehicle(VIN);
    if(veh){
        return veh->previous_data;
    }
    return {};
}
//updating telementary data
Telemetry_data*getUpdateTele_data(const string&VIN){
    Vehicle_data* veh = queryVehicle(VIN);
    if(!veh->previous_data.empty()){
        return &(veh->previous_data.back());
    }
    return {};
}
//alerting all queries 
vector<Alert>all_query_alerts(){
    vector<Alert>all_alerts;
    for(auto it : alerts){
        all_alerts.push_back(it.second);
    }
    return all_alerts;
}

Alert*alertbyId(int id){
    auto it = alerts.find(id);
    if(it!= alerts.end()){
        return &(it->second);
    }
    return {};
}

int main(){
    cout<<"---Dummy Data making..."<<endl;
    generate_vehicle("VIN01","Tesla","Model 1","Fleet 01","Sneha", ACTIVE);
    generate_vehicle("VIN02","BMW","Model 2","Fleet 02","Shalini",ACTIVE);
    generate_vehicle("VIN03","Ford","Model 3","Fleet 03","xyz",MAINTENANCE);
    
    

    cout<<".........total vehicles and VIN and model name....."<<endl;
    vector<Vehicle_data>veh = list_All_vehicle();
    int total_vehicles = veh.size();
    cout<<"Total vehicles="<<total_vehicles<<endl;
    for(auto v: veh){
        cout<<"VIN="<<v.VIN<<endl;
        cout<<"Model="<<v.model<<endl;

    }
    //query is found or not
    cout<<"........query is found or not....."<<endl;
    Vehicle_data*vehicle_query = queryVehicle("VIN01");
    if(vehicle_query){
        cout<<"Found query"<<vehicle_query->manufacture<<endl;
        cout<<vehicle_query->model<<endl;
    }else{
        cout<<"NOt found"<<endl;
    }

    //Deleting query
    cout<<".........Deleting query....."<<endl;
    cout<<"Deleting VIN03"<<endl;
    deleteVehicle("VIN03");

    //after deletion
    cout<<".........after deletion...."<<endl;
    cout<<"Total vehicle="<<list_All_vehicle().size()<<endl;
    for(auto v: list_All_vehicle()){
        cout<<"VIN="<<v.VIN<<endl;
        cout<<"Model="<<v.model<<endl;

    }
    return 0;


}
















































































