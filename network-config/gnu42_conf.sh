#! /bin/bash

# Configure eth0 (port 13)
ifconfig eth0 down
ifconfig eth0 up
ifconfig eth0 172.16.41.1/24
# mac addr 00:21:5a:5a:7c:e7 (banc 5)

# configure route in tux2 to tux3
route add -net 172.16.40.0/24 gw 172.16.41.253 

# clean arp table