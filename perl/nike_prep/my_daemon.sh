#!/bin/bash
#
# my_daemon.pl This starts and stops my_daemon.pl
#
# chkconfig: 2345 12 88
# description: my_daemon.pl is receiving data from rabbitmq and pushing it to dabase
# processname: my_daemon.pl
# pidfile: /var/run/my_daemon.pl.pid
### BEGIN INIT INFO
# Provides: $my_daemon.pl
### END INIT INFO

# Source function library.
. /etc/init.d/functions

binary="./my_daemon.pl"

[ -x $binary ] || exit 1 # chmod +x

RETVAL=0

start() {
    echo -n "Starting my_daemon.pl: "
    daemon $binary
    RETVAL=$?
    PID=$!
    echo
    [ $RETVAL -eq 0 ] && touch /var/lock/subsys/my_daemon.pl

    echo $PID > /var/run/my_daemon.pl.pid
}

stop() {
    echo -n "Shutting down my_daemon.pl: "
    killproc my_daemon.pl
    RETVAL=$?
    echo
    if [ $RETVAL -eq 0 ]; then
        rm -f /var/lock/subsys/my_daemon.pl
        rm -f /var/run/my_daemon.pl.pid
    fi
}

restart() {
    echo -n "Restarting my_daemon.pl: "
    stop
    sleep 2
    start
}

case "$1" in
    start)
        start
    ;;
    stop)
        stop
    ;;
    status)
        status my_daemon.pl
    ;;
    restart)
        restart
    ;;
    *)
        echo "Usage: $0 {start|stop|status|restart}"
    ;;
esac

exit 0