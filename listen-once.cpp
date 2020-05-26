#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(){
    int status;
    addrinfo hints;
    addrinfo *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, "3000", &hints, &result)) != 0){
        cerr << "Error occurred : " << gai_strerror(status) << endl;
        exit(1);
    }

    //You can do anything here basically.
    //Result is filled up.

    addrinfo *tmp = result;
    int i = 0;
    char ip[INET6_ADDRSTRLEN];

    while (tmp != NULL){
        cout << "Node id " << i << endl;
        i++;

        cout << "AI_FAMILY " << tmp->ai_family << endl;
        cout << "AI_FLAGS " << tmp->ai_flags << endl;
        cout << "AI_SOCKTYPE " << tmp->ai_socktype << endl;
        cout << "AI_ADDR " << tmp->ai_addr->sa_data << endl;

        if (tmp->ai_family == AF_INET){
            inet_ntop(tmp->ai_family, &(((sockaddr_in *)(tmp->ai_addr)) -> sin_addr), ip, INET_ADDRSTRLEN);
            cout << ip << endl;
        }else{
            inet_ntop(tmp->ai_family, &(((sockaddr_in6 *)(tmp->ai_addr)) -> sin6_addr), ip, INET6_ADDRSTRLEN);
            cout << ip << endl;
        }

        tmp = tmp->ai_next;
    }

    freeaddrinfo(result);

    return 0;
}
