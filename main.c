/*
 * Felix Schulze
 * 07/12/2014
 * getIP
 *
 */



#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#define NETWORK_DEV_FILE "/proc/net/dev"

int get_ip(char *dev, char *ip)
{
	int fd;
	struct ifreq ifr;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	/* I want to get an IPv4 IP address */
	ifr.ifr_addr.sa_family = AF_INET;

	/* I want IP address attached to "eth0" */
	strncpy(ifr.ifr_name, dev, IFNAMSIZ-1);

	ioctl(fd, SIOCGIFADDR, &ifr);

	close(fd);

	/* save result */
	strcpy(ip, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

	return 0;
}

int get_dev(int number, char *dev)
{
	number += 2;
	FILE *fp;

        fp = fopen(NETWORK_DEV_FILE, "r");

        if(fp == NULL)
        {
                printf("File could not be opened\nIp address could not be determined\n");
        }

	for(unsigned i = 0; i < number; i++)
        	while(fgetc(fp) != '\n');

        for(int i = 0; i < 10; i++)
        {
                dev[i] = fgetc(fp);
                if(dev[i] == ':')
                {
                        dev[i] = 0;
                        break;
                }
        }

        fclose(fp);

	return 0;
}


int main(int argc, char **argv)
{
	char ip[16];
	char dev[16];

	if(argc < 1)
	{
		printf("Error; Enter the number of the network device\nExample getIp 1\n");
	}

	get_dev(atoi(argv[1]), dev);
	printf("Dev :%s\n", dev);
	get_ip(dev, ip);
	printf("IP  :%s\n",  ip);

}
