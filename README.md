# P2P_Navy
P2P Navy for fun
Rebuild C to C++ project
Change PID terminals communication with sync TCP ip with boost asio
Next -> add simultaneous open Tcp to be in P2P and bypass NAT box


[COMPILE for DEV usage]
go in build/bin folder
cd ../.. && ./build_project.sh && cd -

[HOW TO USE PROGRAM]
argv[1] = pos file
argv[2] = Opened Port of The Opponent 
argv[3] = Opponent IP for P2P

go to pos folder, it contain required boats locations

[EXEMPLE]
./P2P_Navy ../../pos/pos1 25008 127.0.0.1
