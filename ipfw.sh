#!/bin/bash
# dmz server port list
aServerPorts="25 80 110 143 443"
aIcmpTypes="0 3 3/4 4 11 12 14 16 18"


iptables -t filter -F
iptables -t nat -F
iptables -t filter -X
iptables -t nat -X
iptables -t filter -Z
iptables -t nat -Z

iptables -t filter -P  INPUT DROP
iptables -t filter -P  OUTPUT DROP
iptables -t filter -P  FORWARD DROP

# allow localhost 
iptables -t filter -A INPUT -s localhost -d localhost -j ACCEPT
iptables -t filter -I OUTPUT -s localhost -d localhost -j ACCEPT

# allow icmp sniffer
for aIcmpType in $aIcmpTypes
do
	iptables -A INPUT -i ens33 -p icmp --icmp-type $aIcmpType -j ACCEPT
	iptables -A INPUT -i ens35 -p icmp --icmp-type $aIcmpType -j ACCEPT
done
iptables -A OUTPUT -o ens33 -p icmp --icmp-type 0 -j ACCEPT
iptables -A OUTPUT -o ens34 -p icmp --icmp-type 0 -j ACCEPT
iptables -A OUTPUT -o ens35 -p icmp --icmp-type 0 -j ACCEPT

iptables -A INPUT -i ens33 -p icmp --icmp-type echo-request -m limit --limit 1/m --limit-burst 3 -j ACCEPT #0 
iptables -A INPUT -i ens34 -p icmp --icmp-type echo-request -m limit --limit 1/m --limit-burst 3 -j ACCEPT #0 
iptables -A INPUT -i ens35 -p icmp --icmp-type echo-request -m limit --limit 1/m --limit-burst 3 -j ACCEPT #0 
iptables -A INPUT -p icmp -j DROP #0


# allow remote control
iptables -t filter -A INPUT -i ens33 -p tcp -s 192.168.2.2 --dport 22 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -t filter -A OUTPUT -o ens33 -p tcp -d 192.168.2.2 --sport 22 -m state --state ESTABLISHED -j ACCEPT
iptables -t filter -A FORWARD -i ens33 -o ens35 -p tcp -s 192.168.2.2 --sport 1024:65535 -d 172.16.2.2 --dport 3389 -m state --state NEW,ESTABLISHED -j ACCEPT 
iptables -t filter -A FORWARD -o ens33 -i ens35 -p tcp -d 192.168.2.2 --dport 1024:65535 -s 172.16.2.2 --sport 3389 -m state --state ESTABLISHED -j ACCEPT 
iptables -t filter -A FORWARD -i ens33 -o ens34 -p tcp -s 192.168.2.2 --sport 1024:65535 -d 10.10.2.2 --dport 3389 -m state --state NEW,ESTABLISHED -j ACCEPT 
iptables -t filter -A FORWARD -o ens33 -i ens34 -p tcp -d 192.168.2.2 --dport 1024:65535 -s 10.10.2.2 --sport 3389 -m state --state ESTABLISHED -j ACCEPT 

# allow inner to dmz
#iptables -A FORWARD -i ens33 -o ens35 -j ACCEPT
#iptables -A FORWARD -i ens35 -o ens33 -j ACCEPT



# allow outer to dmz and firewall dns  (25)
iptables -A INPUT -i ens34 -s 10.10.2.2 -p udp --dport 53 -j ACCEPT
iptables -A OUTPUT -o ens34 -d 10.10.2.2 -p udp --sport 53 -j ACCEPT
iptables -A FORWARD -i ens34 -o ens35 -p udp --dport 53 -j ACCEPT
iptables -A FORWARD -i ens35 -o ens34 -p udp --sport 53 -j ACCEPT
#iptables -A FORWARD -i ens34 -o ens35 -p tcp --dport 53 -j ACCEPT
#iptables -A FORWARD -i ens35 -o ens34 -p tcp --sport 53 -j ACCEPT

# allow dmz to innner (25,53,80,110,143,443)
iptables -A FORWARD -i ens35 -o ens33 -p udp --sport 53 -j ACCEPT
iptables -A FORWARD -i ens33 -o ens35 -p udp --dport 53 -j ACCEPT
#iptables -A FORWARD -i ens33 -o ens35 -p tcp --dport 53 -j ACCEPT
#iptables -A FORWARD -i ens35 -o ens33 -p tcp --sport 53 -j ACCEPT


for aServerPort in $aServerPorts
do
	iptables -A FORWARD -i ens33 -o ens35 -p tcp --dport $aServerPort -j ACCEPT
	iptables -A FORWARD -i ens35 -o ens33 -p tcp --sport $aServerPort -j ACCEPT
done

# allow inner to outer(25,80,110,143,443)
for aServerPort in $aServerPorts
do
	iptables -A FORWARD -i ens33 -o ens34 -p tcp --dport $aServerPort -j ACCEPT
	iptables -A FORWARD -i ens34 -o ens33 -p tcp --sport $aServerPort -j ACCEPT
done


# allow dmz to outer DNS  root
#iptables -A FORWARD -i ens35 -o ens34  -j ACCEPT
#iptables -A FORWARD -i ens34 -o ens35 -j ACCEPT
iptables -A FORWARD -i ens35 -o ens34 -p udp -s 172.16.2.2 -d 10.10.2.2 --dport 53 -j ACCEPT
iptables -A FORWARD -i ens34 -o ens35 -p udp -s 10.10.2.2 -d 172.16.2.2 --sport 53 -j ACCEPT

# allow dmz to outer mail transfer
iptables -A FORWARD -i ens35 -o ens34 -p tcp -s 172.16.2.2 -d 10.10.2.2 --dport 25 -j ACCEPT
iptables -A FORWARD -i ens34 -o ens35 -p tcp -s 10.10.2.2 -d 172.16.2.2 --sport 25 -j ACCEPT
# allow outer to dmz mail transfer
iptables -A FORWARD -i ens34 -o ens35 -p tcp -d 172.16.2.2 -s 10.10.2.2 --dport 25 -j ACCEPT
iptables -A FORWARD -i ens35 -o ens34 -p tcp -d 10.10.2.2 -s 172.16.2.2 --sport 25 -j ACCEPT


# allow dns transfer with  firewall to dmz 
# TSIG authorize
# AXFR/IXFR transfer
#iptables -t filter -A INPUT -i ens35 -p udp --dport 53 -j ACCEPT
#iptables -t filter -A OUTPUT -o ens35 -p udp --sport 53 -j ACCEPT
iptables -t filter -A INPUT -i ens35 -s 172.16.2.2  -d 172.16.2.1 -p udp --dport 53 -j ACCEPT
iptables -t filter -A OUTPUT -o ens35 -d 172.16.2.2 -s 172.16.2.1 -p udp --sport 53 -j ACCEPT
iptables -t filter -A INPUT -p tcp  -s 172.16.2.2 --dport 53 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -t filter -A OUTPUT -p tcp  --sport 53 -d 172.16.2.2 -m state --state ESTABLISHED -j ACCEPT


# allow dmz and outer to inner certServer   (temp)
iptables -A FORWARD -p tcp -d 192.168.2.2 --dport 80 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -A FORWARD -p tcp -s 192.168.2.2 --sport 80 -m state --state ESTABLISHED -j ACCEPT
