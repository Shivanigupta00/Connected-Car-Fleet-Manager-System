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

class Telemetry_data{
protected:
    double latitude;
    double longitude;
    double speed;
    string engine_status;
    double battery_level;
    double odometer;
    string diagnostics_code;  // if any error
    long long timestamp;


public:
    Telemetry_data(double la, double lo, double s, string eng, double battery,double odometer,string diagn, long long ts ):
    latitude(la),longitude(lo),speed(s),engine_status(eng),battery_level(battery),odometer(odometer),diagnostics_code(diagn),timestamp(ts){}

    double getspeed() const{
        return speed;
    }
    double getfuel() const{
        return battery_level;
    }
    double getTimestamp() const{
        return timestamp;
    }


};

class connect{
private:
    string VIN;
    string manufacture;
    string fleetId;
    string owner;
    RegistrationStatus status;

public:
    connect(string V, string manu, string fl,string own, RegistrationStatus status):
    VIN(V), manufacture(manu),fleetId(fl),owner(own),status(status){}

    string getVIN() const{
        return VIN;
    }

    string Manufacture()  const{
        return manufacture;
    } 

    string fleetId() const{
        return fleetId;
    }
    string getOwner() const{
        return owner;
    }
    RegistrationStatus getstatus() const{
        return  status;

    }

};

class Alert {
private:
    static int nextId;
    int id;
    string VIN;
    string type;
    string details;
    long long timestamp;

public:
    Alert(const string& V, const string& type, const string& details, long long ts)
        : id(nextId++), VIN(V), type(type), details(details), timestamp(ts) {}

    int getId() const {
        return id;
    }

    string getType() const {
        return type;
    }
    
    string getVin() const {
        return VIN;
    }
};

class FleetVehicle{
private:
    map<string,connect>vehicles;
    map<string,Alert>fuels;

    double speed_limit = 100.0;
    double fuel_limit = 15.0;

    void generateAlert(const string& vin, const Telemetry_data&data){
        if(data.s>speed_limit){
            Alert.insert({{Alert::nextId,id}})
        }
    }

};






















