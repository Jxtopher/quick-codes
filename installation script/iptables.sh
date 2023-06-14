#!/bin/bash
### BEGIN INIT INFO
# Provides:          iptables.sh
# Required-Start:    $syslog $time $remote_fs
# Required-Stop:     $syslog $time $remote_fs
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
### END INIT INFO

. /lib/lsb/init-functions

do_start() {
	/etc/init.d/fail2ban stop

	iptables -P INPUT DROP
	iptables -P FORWARD DROP
	iptables -P OUTPUT DROP


	#SSH
	iptables -A INPUT -p tcp --dport 22 -j ACCEPT
	iptables -A INPUT -p tcp --dport 1723 -j ACCEPT
	iptables -A INPUT -p tcp --dport 443 -j ACCEPT

	#SAMBA
#	iptables -A INPUT -p udp -s 192.168.1.0/24 -d 192.168.1.198/32 -m udp --dport 137 -j ACCEPT
#	iptables -A INPUT -p udp -s 192.168.1.0/24 -d 192.168.1.198/32 -m udp --dport 138 -j ACCEPT
#	iptables -A INPUT -m state -s 192.168.1.0/24 -d 192.168.1.198/32 --state NEW -m tcp -p tcp --dport 139 -j ACCEPT
#	iptables -A INPUT -m state -s 192.168.1.0/24 -d 192.168.1.198/32 --state NEW -m tcp -p tcp --dport 445 -j ACCEPT

	#HTTPS
#	iptables -A INPUT -p tcp -s 192.168.1.198/32 -d 192.168.1.198/32	--dport 80 -j ACCEPT
#	iptables -A INPUT -p tcp -s 192.168.1.198/32 -d 192.168.1.198/32	--dport 443 -j ACCEPT

	#Proxy
#	iptables -A INPUT -p tcp -s 192.168.1.198/32 -d 192.168.1.198/32  --dport 3128 -j ACCEPT

	#loop
	iptables -A INPUT -d 127.0.0.0/8 -j ACCEPT

	iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT
	iptables -A OUTPUT -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT


	/etc/init.d/fail2ban start
}

do_stop() {
	/etc/init.d/fail2ban stop

	iptables -t filter -F
	iptables -t filter -X

	iptables -t filter -P INPUT ACCEPT
	iptables -t filter -P FORWARD ACCEPT
	iptables -t filter -P OUTPUT ACCEPT

	iptables -t nat -F
	iptables -t nat -X

	iptables -t mangle -F
	iptables -t mangle -X

	/etc/init.d/fail2ban start
}

case $1 in 
 start)
	log_daemon_msg "Starting configuration" iptables
	if [[ $EUID = 0 ]]
	then
		do_start
		log_end_msg 0
	else
		log_end_msg 1
		echo "You are no root !"
		
	fi
	;;
 stop)
	log_daemon_msg  "Stopping configuration" iptables
	if [[ $EUID = 0 ]]
	then
		do_stop
		log_end_msg 0
	else
		log_end_msg 1
		echo "You are no root !"
	fi 
	;;
 restart)
	log_daemon_msg  "Restarting configuration" iptables
	if [[ $EUID = 0 ]]
	then
		do_stop
		do_start
		log_end_msg 0
	else
		log_end_msg 1
		echo "You are no root !"
	fi 
	;;
 status)
	if [[ $EUID = 0 ]]
	then
		iptables -L -n -v
	else
		echo "You are no root !"
	fi
	;;
     *)
	log_daemon_msg  "./iptables [start|stop|restart|status]"
	;;
esac


