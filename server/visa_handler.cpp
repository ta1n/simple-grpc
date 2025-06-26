#include "visa_handler.h"
#include <iostream>
#include <sstream>
#include <cstring> 

VISAHandler::VISAHandler() : resource_manager(0), device_session(0), 
                            use_simulation(true), current_freq(0), current_gain(0) {
    if (viOpenDefaultRM(&resource_manager) != VI_SUCCESS) {
        std::cerr << "Using simulation mode\n";
        use_simulation = true;
    }
}

VISAHandler::~VISAHandler() {
    if (device_session) viClose(device_session);
    if (resource_manager) viClose(resource_manager);
}

bool VISAHandler::connect(const std::string& device_id) {
    if (use_simulation) {
        current_device_id = device_id;
        return true;
    }
    
    char* device_id_copy = strdup(device_id.c_str());
    if (!device_id_copy) return false;
    
    bool success = (viOpen(resource_manager, device_id_copy, VI_NULL, VI_NULL, &device_session) == VI_SUCCESS);
    
    free(device_id_copy); 
    if (success) {
        current_device_id = device_id;
    }
    return success;
}

bool VISAHandler::configure(const std::string& device_id, double freq, double gain) {
    if (!connect(device_id)) return false;
    
    if (use_simulation) {
        current_freq = freq;
        current_gain = gain;
        return true;
    }

    char cmd[100];
    sprintf(cmd, "FREQ %.6f Hz", freq);
    if (viPrintf(device_session, "%s\n", cmd) != VI_SUCCESS) return false;
    
    sprintf(cmd, "GAIN %.2f dB", gain);
    if (viPrintf(device_session, "%s\n", cmd) != VI_SUCCESS) return false;
    
    current_freq = freq;
    current_gain = gain;
    return true;
}

std::string VISAHandler::get_status(const std::string& device_id) {
    if (use_simulation) {
        return "Simulated: Freq=" + std::to_string(current_freq) + 
               " Hz, Gain=" + std::to_string(current_gain) + " dB";
    }
    return "Connected to real device " + device_id;
}

DeviceSettings VISAHandler::get_current_settings(const std::string& device_id) {
    DeviceSettings settings;
    settings.frequency = current_freq;
    settings.gain = current_gain;
    settings.status = get_status(device_id);
    return settings;
}


