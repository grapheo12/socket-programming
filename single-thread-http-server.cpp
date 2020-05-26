/* Server that returns current UNIX timestamp
 */

#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <chrono>

#define PORT "3000"
#define BACKLOG 10
#define BUFFER_SIZE 1000000

using namespace std;
int main(){
    addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_UNSPEC;
    hint.ai_flags = AI_PASSIVE;
    hint.ai_socktype = SOCK_STREAM;

    addrinfo *myip;
    getaddrinfo(NULL, PORT, &hint, &myip);

    int main_socket = socket(myip->ai_family, myip->ai_socktype, myip->ai_protocol);
    if (main_socket == -1){
        cerr << "Cannot get socket" << endl;
        exit(1);
    }

    int status = bind(main_socket, myip->ai_addr, myip->ai_addrlen);
    if (status == -1){
        cerr << "Cannot bind to port" << endl;
        exit(1);
    }

    listen(main_socket, BACKLOG);

    //Now accept incoming connections.

    sockaddr_storage client_addr;
    socklen_t addr_size = sizeof(client_addr);

    while (true){
        int client_fd = accept(main_socket, (sockaddr *)&(client_addr), &addr_size);

        //Get the current unix timestamp as a character array
        string reqTime;
        {
            using namespace std::chrono;

            milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
            stringstream ss;
            ss << "Current time is: " << ms.count() << endl;

            reqTime = ss.str();
        }

        stringstream httpResponseStream;
        httpResponseStream << "HTTP/1.0 200 OK" << endl;
        httpResponseStream << "Content-Type: text/html" << endl;
        httpResponseStream << endl;
        httpResponseStream << reqTime << endl;
        httpResponseStream << endl;
        reqTime = httpResponseStream.str();
        char *msg = new char[reqTime.length()];
        strcpy(msg, reqTime.c_str());

        char *data = new char[BUFFER_SIZE];
        int recv_status = recv(client_fd, data, BUFFER_SIZE, 0);
        if (recv_status){
            cout << "Received data: " << endl;
            cout << data << endl;
            send(client_fd, msg, sizeof(char) * reqTime.length(), 0);
        }
        free(data);
        close(client_fd);

    }

    return 0;

}
