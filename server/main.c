#include <sys/select.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>

#define PORT 60000

int main()
{
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind (sfd, (struct sockaddr *) &addr, sizeof (addr)) == -1)
	{
		close(sfd);
		return -1;
	}

	listen(sfd, 0);

	fd_set rset;
	FD_ZERO(&rset);
	FD_SET(sfd, &rset);
	int ret = select(sfd+1, &rset, 0, 0, 0);
	if(ret <= 0)
		return -1;

	FD_ISSET(sfd, &rset);

	struct sockaddr_in  clientaddr;
	socklen_t clilen  = sizeof (clientaddr);
	int cfd = accept (sfd, (struct sockaddr *) &clientaddr, (socklen_t*)&clilen);

	if(cfd == -1) printf("accept failed\n");
	else{
		printf("accepted client(%s:%u), fd(%d)\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), cfd);
	}

	close(sfd);

	return 0;
}
