#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <msgpack.hpp>
#include <sstream>
using namespace std;

#define SERVER_PORT htons(50007)

int main() {

        char buffer[1000];
        int n;

        int serverSock=socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = SERVER_PORT;
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        /* bind (this socket, local address, address length)
           bind server socket (serverSock) to server address (serverAddr).  
           Necessary so that server can use a specific port */ 
        bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));

        // wait for a client
        /* listen (this socket, request queue length) */
        listen(serverSock,1);
        bzero(buffer, 1000);

        sockaddr_in clientAddr;
        socklen_t sin_size=sizeof(struct sockaddr_in);
        int clientSock=accept(serverSock,(struct sockaddr*)&clientAddr, &sin_size);

        while (1) {

                //receive a message from a client
                n = read(clientSock, buffer, 500);
                cout << "Server received:  " << buffer << endl;

			    stringstream sbuf;
			    msgpack::packer<stringstream> pk(&sbuf);
			    pk.pack_map(4);
			    pk.pack(string("1st"));
			    pk.pack(1);
			    pk.pack(string("2nd"));
			    pk.pack(2);
			    pk.pack(string("3rd"));
			    pk.pack(3);
			    pk.pack(string("4th"));
			    pk.pack(4);

                cout << sbuf << endl;
                write(clientSock, sbuf.str().c_str(), sbuf.str().size());
                string str = "\r\n";
    			write(clientSock, str.c_str(), sizeof(str.c_str()));
                /* deserialize the buffer into msgpack_object instance. */
                /* deserialized object is valid during the msgpack_zone instance alive. */
                cout << sbuf.str().c_str() << endl;
                cout << sbuf.str() << endl;
                cout << "data length: " << sbuf.str().size() << endl;
                msgpack::unpacked msg;
			    msgpack::unpack(&msg, sbuf.str().c_str(), sbuf.str().size());

			    msgpack::object obj = msg.get();
			    cout << obj << endl;
      

                //strcpy(buffer, "test");

                cout << "Confirmation code  " << n << endl;
        }
        return 0;
}