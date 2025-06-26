# Overview
This project is a gRPC based server-client implementation which simulates controlling RF equipment using VISA.

- **gRPC Server (C++)**: Handles device configuration and status queries
	+  **VISA Integration**: Supports real hardware or simulation mode
- **Python Client**: Provides  interface for RF control
    

## Features

- Configure RF parameters (frequency, gain) via gRPC
    
- Query current device status


# Quick Start

Run the server: 
```bash

git clone https://github.com/ta1n/simple-grpc
docker compose up

```

Run the client:
```bash

python client/client.py

```

### Using the Client Interface

**When attached to the client container, you'll see an interactive menu:**

```
RF Controller Client
1. Configure Device
2. View Current Settings
3. Exit
Select an option (1-3): 

```

```
Select an option (1-3): 1
Enter Device ID: USRP1
Enter Frequency (Hz): 2.4e9  
Enter Gain (dB): 30

Configuration Result:
Success: Yes
Message: OK
Status: Configured - Freq=2.4 GHz, Gain=30 dB
```

**Sample Query:**

```
Select an option (1-3): 2
Enter Device ID to query: USRP1

Current Device Settings:
Device ID: USRP1
Frequency: 2400000000.0 Hz
Gain: 30.0 dB
Status: Device active

```


## Hardware Integration

Supports two operation modes:

1. **Real Hardware Mode**
        
2. **Simulation Mode**:
    
    - Automatically activated if VISA libraries not found
        
    - Maintains device state in memory
        
    - Logs all commands that would be sent to hardware


