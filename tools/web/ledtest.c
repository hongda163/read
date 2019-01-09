/*************************************************************************
    > File Name: ledtest.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Mon 24 Dec 2018 07:44:48 PM PST
 ************************************************************************/

 %%%%%%%%%%%%%%%ledtest.c%%%%%%%%%%%%%%%%%%%%%%%
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include<string.h>
static int led_fd;
static int leds[4] = {0};
static void lightleds(void)
{
for(i=0;i<4;i++)
{
ioctl(led_fd, leds[i], i);
}
}
int main(void)
{
int led_control_pipe;
int null_writer_fd; // for read endpoint not blocking when control process exit led_fd = open("/dev/EmbedSky-leds", 0);
if (led_fd < 0) {
perror("open device leds");
exit(1);
}
unlink("/tmp/led-control");
mkfifo("/tmp/led-control", 0666);
led_control_pipe = open("/tmp/led-control", O_RDONLY | O_NONBLOCK); if (led_control_pipe < 0) {
perror("open control pipe for read");
exit(1);
}
null_writer_fd = open("/tmp/led-control", O_WRONL Y | O_NONBLOCK); if (null_writer_fd < 0) {
perror("open control pipe for write");
exit(1);
}
for (;;) {
fd_set rds;
int ret;
struct timeval step;
step.tv_sec = 0;
step.tv_usec =0.125*1000000L;
FD_ZERO(&rds);
FD_SET(led_control_pipe, &rds);
ret = select(led_control_pipe + 1, &rds, NULL, NULL, &step);
if (ret < 0) {
perror("select");
exit(1);
}
if (ret == 0) {
lightleds();
}
else if (FD_ISSET(led_control_pipe, &rds)) {
static char buffer[200];
for (;;) {
char c;
int len = strlen(buffer);
if (len >= sizeof buffer - 1) {
memset(buffer, 0, sizeof buffer);
break;
}
if (read(led_control_pipe, &c, 1) != 1) {
break;
}
if (c == 'r') {
continue;
}
if (c == 'n') {
int tmp_leds[4];
if (sscanf(buffer,"%d%d%d%d", &tmp_leds[0], &tmp_leds[1],&tmp_leds[2],&tmp_leds[3]) == 4) {
leds[0] = tmp_leds[0];
leds[1] = tmp_leds[1];
leds[2] = tmp_leds[2];
leds[3] = tmp_leds[3];
}
int j;
for(j=0;j<4;j++)
{
if(leds[j])
fprintf(stderr,"led%d is onn",j+1);
else
fprintf(stderr, "led%d is offn",j+1);
}
memset(buffer, 0, sizeof buffer);
break;
}
buffer[len] = c;
}
}
}
close(led_fd);
return 0;
}
%%%%%%%%%%%%%%%ledtest.c%%%%%%%%%%%%%%%%%%%%%%%
