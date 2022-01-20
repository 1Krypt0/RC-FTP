#! /bin/bash

# configure eth0 (port 1)
ifconfig eth0 down
ifconfig eth0 up
ifconfig eth0 172.16.40.1/24
# mac addr 00:21:5a:61:2c:54 (banc 5)

# configure route in tux3 to tux2
route add -net 172.16.41.0/24 gw 172.16.40.254

# clean arp table