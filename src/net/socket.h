#pragma once

namespace Tales
{
	namespace Net
	{
		using namespace Core;

		class TALES_API Socket : public Object
		{
		public:
			enum class Protocol
			{
				Tcp,
				Udp
			};

			Socket();
			Socket(Socket&& rhs);
			~Socket();

			bool invalid();

			bool create(Protocol protocol = Protocol::Tcp);
			void close();

			bool connect(const String& host);
			bool bind(const String& host);

			Socket accept();

			void send(const String& str);
			String recvString();

			int send(char* buf, int offset, int count);
			int recv(char* buf, int offset, int count);

			void setBlocking(bool block);
			String gethostinfo();
			String getpeerinfo();

		private:
			SOCKET sock = -1;
			struct sockaddr_in sockAddr;
		};
	}
}


