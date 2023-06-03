
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define  BUFF_SIZE   1024

int
main(int argc, char *argv[])
{
	int   server_socket;
	int   client_socket;
	int   client_addr_size;

	struct sockaddr_in   server_addr;
	struct sockaddr_in   client_addr;

	char   buff_rcv[BUFF_SIZE+5];
	char   buff_snd[BUFF_SIZE+5];


	server_socket  = socket( PF_INET, SOCK_STREAM, 0);
	if( -1 == server_socket)
	{
		printf( "server socket 생성 실패\n");
		exit(1);
	}

	memset( &server_addr, 0, sizeof( server_addr));
	server_addr.sin_family     = AF_INET;
	server_addr.sin_port       = htons( 4000);
	server_addr.sin_addr.s_addr= htonl( INADDR_ANY);

	if( -1 == bind( server_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
	{
		printf( "bind() 실행 에러\n");
		exit( 1);
	}

	if( -1 == listen(server_socket, 5))
	{
		printf( "대기상태 모드 설정 실패\n");
		exit( 1);
	}

	client_addr_size  = sizeof( client_addr);

	struct stat sb;
	fstat(server_socket, &sb);

	struct pollfd pf2;
	pf2.fd = server_socket;
	pf2.events = POLLIN;
	
	if (poll(&pf2, 1, 1000))
		client_socket = accept( server_socket, (struct sockaddr*)&client_addr, &client_addr_size);

	printf("%d \n", client_socket);

	fstat(server_socket, &sb);

	char buf[4096 + 1];
	struct pollfd pfd;

	pfd.fd = client_socket;
	pfd.events = POLLIN;
	for (int i =0; i < 10; i++)
	{
		printf("fstat : %d\n", fstat(pfd.fd, &sb));
		printf("size : %d\n", sb.st_size);
		// if (sb.st_size > 0)
		{
			if (poll(&pfd, 1, -1) == -1)
			{
				if (pfd.revents & POLLERR)
					printf("poll error");
			}
		printf("%d", pfd.revents);
		
		printf("fstat : %d", fstat(pfd.fd, &sb));
		ssize_t len = recv(pfd.fd, &buf, 4096, 0);
		if (len < 0)
			printf("recv() failed");
		if (len == 0)
			printf("Connection closed");
		buf[len] = '\0';
		printf("%s",buf);
		}
	}
	printf("%d", pfd.revents);
	// std::string receive = "";
	// receive  += buf;
	// while (receive.find("\r\n") != std::string::npos)
	// {
	// 	std::string msg = receive.substr(0, receive.find("\r\n"));
	// 	receive.erase(0, receive.find("\r\n") + 2);
	// 	printf("%s",receive.c_str());
	// }
}
