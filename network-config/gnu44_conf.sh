#! /bin/bash

# Configure eth0 (port 2)
ifconfig eth0 down
ifconfig eth0 up
ifconfig eth0 172.16.40.254/24

# Configure eth1 (port 14)
ifconfig eth0 down
ifconfig eth0 up
ifconfig eth0 172.16.41.253/24
# mac addr 00:22:64:19:09:5c (banc 5)

# enable ip forwarding
echo 1 > /proc/sys/net/ipv4/ip_forward
# disable ICMP echo ignore broadcast
echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts

# clean arp table