#include <iostream>
#include <grpcpp/grpcpp.h>
#include "rfcontrol.grpc.pb.h"
#include "visa_handler.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class RFService : public rfcontrol::RFController::Service {
    Status SetRFSettings(ServerContext* context, const rfcontrol::RFConfig* request,
                        rfcontrol::RFResponse* reply) override {
        
        std::cout << "Configuring: " << request->device_id() 
                  << " Freq=" << request->frequency()
                  << " Gain=" << request->gain() << "\n";
        
        bool ok = handler.configure(request->device_id(), 
                                  request->frequency(), 
                                  request->gain());
        
        reply->set_success(ok);
        reply->set_message(ok ? "OK" : "Failed");
        reply->set_device_status(handler.get_status(request->device_id()));
        
        return Status::OK;
    }
    
    Status GetCurrentSettings(ServerContext* context, const rfcontrol::DeviceQuery* request,
                             rfcontrol::CurrentSettings* reply) override {
        
        auto settings = handler.get_current_settings(request->device_id());
        
        reply->set_device_id(request->device_id());
        reply->set_current_frequency(settings.frequency);
        reply->set_current_gain(settings.gain);
        reply->set_status_message(settings.status);
        
        return Status::OK;
    }
    
private:
    VISAHandler handler;
};

int main() {
    std::string address = "0.0.0.0:50051";
    RFService service;
    
    ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    
    auto server = builder.BuildAndStart();
    std::cout << "Server running on " << address << "\n";
    server->Wait();
    
    return 0;
}

