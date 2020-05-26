#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

addrinfo getHint(){
    addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM; //Only TCP

    return hint;
}

int main(int argc, char *argv[]){
    addrinfo hints = getHint(), *res;
    char ipstr[INET6_ADDRSTRLEN];

    if (argc != 2){
        cerr << "Usage: showip hostname" << endl;
        exit(1);
    }

    int status;
    if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0){
        cerr << "Some error occurred : " << gai_strerror(status) << endl;
        exit(1);
    }

    cout << "IP addresses belonging to: " << argv[1] << endl;

    addrinfo *tmp = res;
    while (tmp != NULL){
        if (tmp->ai_family == AF_INET){
            cout << "IPv4 ";

            sockaddr_in *ipv4 = (sockaddr_in *)(tmp->ai_addr);
            inet_ntop(tmp->ai_family, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
        }else if (tmp->ai_family == AF_INET6){
            cout << "IPv6 ";

            sockaddr_in6 *ipv6 = (sockaddr_in6 *)(tmp->ai_addr);
            inet_ntop(tmp->ai_family, &(ipv6->sin6_addr), ipstr, sizeof(ipstr));
        }

        cout << ipstr << endl;
        tmp = tmp->ai_next;
    }

    return 0;


}
