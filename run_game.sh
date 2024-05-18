#!/bin/bash

# Démarrer le serveur
./build/P2P_Navy pos/pos1 25012 127.0.0.1 &
SERVER_PID=$!

# Attendre un moment pour que le serveur soit prêt
sleep 2

# Démarrer le client
./build/P2P_Navy pos/pos2 25012 127.0.0.1

# Attendre que le serveur se termine
wait $SERVER_PID
