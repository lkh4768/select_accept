#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 60000
#define IP	 "127.0.0.1"

int main()
{
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr=inet_addr(IP);
	addr.sin_port = htons(PORT);

	if(connect(sfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		printf("Server Connect Error(%d:%s)\n", errno, strerror(errno));
		close(sfd);
		return -1;
	}
	else
		printf("Server(%s:%d) Connected, fd(%d)\n", IP, PORT, sfd);

	close(sfd);
	return 0;
}
