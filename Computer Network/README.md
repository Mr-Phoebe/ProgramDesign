Protocol for Computer Network
===
Requirement
---
Use the knowledge of datalink layer, I need to design a sliding window protocol for Error-free duplex communication between two sites in the noise environment.  
The channel model is a 8000bps full-duplex satellite channel; channel propagation delays of 270 milliseconds; the channel error rate is $10^{-5}$; the channel provides byte stream transmission service, the network layer packet length is fixed to 256 bytes.  

Programming Environment
---
VS2013 + WIN32  

How to use
---
Just add "event.c, Impl.c, Impl.h, Init.c, log.c, network.c, physical.c, protocol.h, timer.c" to your current project, and everything will work in the same way as using dll/lib.  
After compiling, we will get a datalink.exe.   
We need to open two consoles to run the program, and one station must be **a** and the other one must be **b**
```
Usage:  
    datalink <options> [-port <tcp-port#>] [-ber <ber>] [-log <filename>]
Options :
    A/B : Station name
        u : Utopia channel (an error-free channel) (default 1.0e-5)
        f : Flood traffic
        i : Set station B layer 3 sender mode as IDLE-BUSY-IDLE-BUSY-...
        n : Do Not create log file
        0~3 : Debug mask (default: 0)
    -port : TCP port number (default: 59144)
    -ber : Bit Error Rate (default: 1.0E-005)
    -log : Using assigned file as log file
```
Here is an example  
```
datalink af3 –port 10002 –log c:\temp\a.log –ber 2.0E-4
datalink bf3 –port 10002 –log c:\temp\b.log –ber 2.0E-4

datalink au
datalink bu
```

Code Layout
---
###Impl.h/Impl.c
Store the shared global constaints and variables.
###Init.c
Impl function <code>protocol_init ()</code>
###event.c
Impl function <code>wait_for_event ()</code>
###network.c
Impl function <code>enable_network_layer ()</code>, <code>disable_network_layer ()</code>, 
<code>get_packe ()t</code>, <code>put_packet ()</code>
###physical.c
Impl function <code>recv_frame ()</code>, <code>send_frame ()</code>, <code>phl_sq_len ()</code>, <code>crc32 ()</code>
###timer.c
Impl function <code>get_ms ()</code>, <code>start_timer ()</code>, <code>stop_timer ()</code>, 
<code>start_ack_timer ()</code>, <code>stop_ack_timer ()</code>
###log.c
Impl function <code>log_printf ()</code>, <code>lprintf ()</code>, <code>station_name ()</code>, <code>dbg_* ()</code>
###datalink.c
Sliding Window Protocol