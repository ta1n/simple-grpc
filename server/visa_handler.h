#ifndef VISA_HANDLER_H
#define VISA_HANDLER_H

#include <string>
#include <visa.h>

struct DeviceSettings {
    double frequency;
    double gain;
    std::string status;
};

class VISAHandler {
public:
    VISAHandler();
    ~VISAHandler();
    
    bool connect(const std::string& device_id);
    bool configure(const std::string& device_id, double freq, double gain);
    std::string get_status(const std::string& device_id);
    DeviceSettings get_current_settings(const std::string& device_id);

private:
    ViSession resource_manager;
    ViSession device_session;
    bool use_simulation;
    double current_freq;
    double current_gain;
    std::string current_device_id;
};
#endif
