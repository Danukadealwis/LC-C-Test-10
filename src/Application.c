//========= please implement==================
//    The Application module should instantiate the SerialInterface (kind of an inheritance) and "realize" the callback.
//    Print out the received data from callback to output device through standard printf().
//    The Application module should also instantiate a thread (using Thread.c) to run once per second (use Sleep(1000)) to print out the number of bytes received in the last second.
//    This bytes per second information needs to send out back through the SerialInterface.
