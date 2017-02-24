#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "common.h"
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

	char request_message[sizeof(req)] ;
	 char search[sizeof(int)];
	
	
	//char first_par[sizeof(int)];
	//char second_par[sizeof(int)];
	printf("SIZEOF REQ %d",sizeof(req));
	
	//sprintf(first_par,"%d",4);
	//sprintf(second_par,"%d",6);
	//strcat(first_par,second_par);
	//memcpy((void *)request,(void *)first_par,2*sizeof(int));
	//memcpy((void *)&request[sizeof(int)],(void *)second_par,sizeof(int));

	/*request packet*/
	
	/*Creates the svcid and the request he wants to sent*/
	svcid=1;	
	
	 /****search******/
	sprintf(search, "%d", svcid);

	printf("svcid einai: %s \n",search);
	
	/*initialize reqid*/
	reqid=0;

	req request;
	request.par1=htonl(4);
	request.par2=htonl(6);
	
	printf("Params : %d,%d",ntohl(request.par1),ntohl(request.par2));
	
	  
	messagelen=sizeof(req) +2*sizeof(int);
    
	message=malloc(messagelen);
	

	memcpy((void *)request_message,(void *)&request,sizeof(req));
	
	//request_message[sizeof(req)]='\0';
	//printf("PARAMETERS ARE %s \n",request_message);
	
	
	int key;

	/* Create the UDP socket */
        if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
              printf("Failed to create socket");
              exit(1);
        }
        
        /*Set the multicast ip to ask for the service*/
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	addr.sin_addr.s_addr = inet_addr("224.1.2.3");

	/*TRANSMITTED MESSAGES ARE NOT DELIVERED TO THE SENDING HOST*/
	//unsigned char loop = 0;
	//setsockopt(sock, IPPROTO_IP,IP_MULTICAST_LOOP, &loop,sizeof(loop));

	//sendto(sock, buff, sizeof(buff), 0, (struct sockaddr*)&addr, sizeof(addr));



	key=sendRequest (svcid,request_message, sizeof(request_message));
	key=replyAvailable(0);

	printf("CLient's has send asychronous the request with id:%d \n",key);

	//key=sendRequest (svcid,request_message, sizeof(request_message));

	//printf("CLient's has send asychronous the request with id:%d \n",key);

	return 0;

}

