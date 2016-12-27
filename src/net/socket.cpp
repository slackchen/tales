#include "tales.h"

namespace Tales
{
	namespace Net
	{
		Socket::Socket()
		{
#ifdef TALES_WIN32
			WORD wVersionRquest = MAKEWORD(1, 1);
			WSADATA wsaData;
			WSAStartup(wVersionRquest, &wsaData);
#endif
		}

		Socket::Socket(Socket && rhs)
		{
			sock = rhs.sock;
			sockAddr = rhs.sockAddr;
			rhs.sock = INVALID_SOCKET;
		}


		Socket::~Socket()
		{
			close();

#ifdef TALES_WIN32
			WSACleanup();
#endif
		}

		bool Socket::invalid()
		{
			return sock == INVALID_SOCKET;
		}

		bool Socket::create(Protocol protocol)
		{
			close();

			if (protocol == Protocol::Tcp)
				sock = socket(AF_INET, SOCK_STREAM, 0);
			else if (protocol == Protocol::Udp)
				sock = socket(AF_INET, SOCK_DGRAM, 0);
			else
				return false;

			if (sock == INVALID_SOCKET)
				return false;

			return true;
		}

		void Socket::close()
		{
			if (sock != 0)
			{
			#ifdef TALES_WIN32
				::closesocket(sock);
            #else
                ::close(sock);
            #endif

				sock = INVALID_SOCKET;
			}
		}

		bool Socket::connect(const String & host)
		{
			Array<String> strs = host.split(":");
			if (strs.num() < 2)
				return false;

			String addr = strs[0];
			int port = strs[1].toInt();

			sockaddr_in addrSrv;
			memset(&addrSrv, 0, sizeof(addrSrv));
			addrSrv.sin_addr.s_addr = inet_addr(addr.str());
			addrSrv.sin_family = AF_INET;
			addrSrv.sin_port = htons(port);

			if (addrSrv.sin_addr.s_addr == INADDR_NONE) // enable DNS resolve
			{
				struct hostent* hostent = gethostbyname(addr.str());
				addrSrv.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)hostent->h_addr_list[0]));
			}

			int ret = ::connect(sock, (sockaddr*)&addrSrv, sizeof(sockaddr));
			if (ret == SOCKET_ERROR)
				return false;

			sockAddr = addrSrv;

			return true;
		}

		bool Socket::bind(const String & host)
		{
			Array<String> strs = host.split(":");
			if (strs.num() < 2)
				return false;

			String addr = strs[0];
			int port = strs[1].toInt();

			struct sockaddr_in sin;
			int on = 1;
			sin.sin_family = AF_INET;
			sin.sin_port = htons(port);
			sin.sin_addr.s_addr = addr == "0.0.0.0" ? INADDR_ANY : inet_addr(addr.str());
			if (
				!setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on)) &&
				!::bind(sock, (struct sockaddr *)&sin, sizeof(sin)) &&
				(listen(sock, SOMAXCONN) == 0)
				)
			{
				sockAddr = sin;
				return true;
			}

			return false;
		}

		Socket Socket::accept()
		{
			struct sockaddr_in sin;
			socklen_t addlen = sizeof(sin);
			SOCKET s = ::accept(sock, (struct sockaddr*)&sin, &addlen);
			if (s != INVALID_SOCKET)
			{
				Socket newSock;
				newSock.sock = s;
				newSock.sockAddr = sin;
				return std::move(newSock);
			}

			return std::move(Socket());
		}

		void Socket::send(const String & str)
		{
			int offset = 0;
			int count = str.length() * sizeof(char) + 1;

			while (offset < count)
				offset += send((char*)str.str(), offset, count - offset);
		}

		String Socket::recvString()
		{
			char buf[1024];
			int offset = 0;

			while (offset < 1024)
			{
				offset += recv(buf, offset, 1);
				if (buf[offset - 1] == 0)
				{
					break;
				}
			}

			return std::move(String(buf));
		}

		int Socket::send(char * buf, int offset, int count)
		{
			return ::send(sock, buf + offset, count, 0);
		}

		int Socket::recv(char * buf, int offset, int count)
		{
			return ::recv(sock, buf + offset, count, 0);
		}

		void Socket::setBlocking(bool block)
		{
			unsigned long ul = block ? 0 : 1;
			int ret = ::ioctlsocket(sock, FIONBIO, (unsigned long*)&ul);
			if (ret == SOCKET_ERROR)
			{
				close();
			}
		}

		String Socket::gethostinfo()
		{
			struct sockaddr_in serv, guest;
			char serv_ip[20];
			char guest_ip[20];
			socklen_t serv_len = sizeof(serv);
			socklen_t guest_len = sizeof(guest);
			getsockname(sock, (struct sockaddr *)&serv, &serv_len);
			getpeername(sock, (struct sockaddr *)&guest, &guest_len);
			inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));
			inet_ntop(AF_INET, &guest.sin_addr, guest_ip, sizeof(guest_ip));
			return String::format("host %s:%d", serv_ip, ntohs(serv.sin_port));
		}

		String Socket::getpeerinfo()
		{
			struct sockaddr_in serv, guest;
			char serv_ip[20];
			char guest_ip[20];
			socklen_t serv_len = sizeof(serv);
			socklen_t guest_len = sizeof(guest);
			getsockname(sock, (struct sockaddr *)&serv, &serv_len);
			getpeername(sock, (struct sockaddr *)&guest, &guest_len);
			inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));
			inet_ntop(AF_INET, &guest.sin_addr, guest_ip, sizeof(guest_ip));
			return String::format("peer %s:%d", guest_ip, ntohs(guest.sin_port));
		}
	}
}
