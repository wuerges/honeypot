
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>


static char mesg[10000];
static int buffer[1000];

void (*pointer_to_function)();
void one_function() {
    int i, c = 0;
    c = sprintf(mesg, "printing the values in the buffer:\n");
    for(i = 0; i < 10; ++i)
        c += sprintf(mesg+c, "buffer[%d] = %d\n", i, buffer[i]);
}

void other_function() {
    sprintf(mesg, "Congratulations! This function should not be ran!");
}

int main(int argc, char**argv)
{
    pointer_to_function = &one_function;
    int sockfd,n,p,d;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t len;

    sockfd=socket(AF_INET,SOCK_DGRAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(32000);
    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    for (;;)
    {
        len = sizeof(cliaddr);
        n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);

        mesg[n] = 0;
        sscanf(mesg, "%d %d", &p, &d);
        //sprintf(mesg, "%d %d\n",p, d);
        
        pointer_to_function();
        n = strlen(mesg);
        printf(">>%s<<\n", mesg);

        sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
    }
}


