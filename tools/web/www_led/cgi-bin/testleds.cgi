#!/bin/sh


LED1_ON=0
LED2_ON=0
LED3_ON=0
LED4_ON=0
SPEED=1


case $QUERY_STRING in
    *cb_led=led1*)
        LED1_ON=1
        ;;
esac
 
case $QUERY_STRING in
    *cb_led=led2*)
        LED2_ON=1
        ;;
esac
 
case $QUERY_STRING in
    *cb_led=led3*)
        LED3_ON=1
        ;;
esac
 
case $QUERY_STRING in
    *cb_led=led4*)
        LED4_ON=1
        ;;
esac
       
 
#/bin/echo $LED1_ON $LED2_ON  $LED3_ON $LED4_ON > /tmp/led-control
/bin/echo $LED1_ON > /sys/class/gpio/gpio18/value
 
/bin/echo "Content-type: text/html; charset=gb2312"
/bin/echo
#/bin/echo $QUERY_STRING "STRING"


/bin/cat led-result.template
exit 0