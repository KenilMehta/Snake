#include <string>
#include <zconf.h>
#include <cstring>
#include <iostream>
#include <string>

#include <netdb.h>
#include <arpa/inet.h>
#pragma once
class UdpSocket {
public:

    UdpSocket(std::string ip,std::string port){
        struct addrinfo * info;
        getAddressInfo(&info,port,ip);

        fd_ = socket(info->ai_family,info->ai_socktype,info->ai_protocol);
        if(fd_ == -1){
            throw std::runtime_error("error creating fd");
        }
        destroy_ = true;
        if(bind(fd_,info->ai_addr,info->ai_addrlen) == -1){
            throw std::runtime_error("error binding fd");
        }

        freeaddrinfo(info);
        std::cout<<"Socket created with ip "<<ip<<" port "<<port<<"\n";
    }

    UdpSocket(int fd) : fd_{fd},destroy_{false}{
    }

    bool send(char * message,int size,std::string destination_ip,std::string destination_port){
        struct addrinfo * info;
        getAddressInfo(&info,destination_port,destination_ip);

        if(sendto(fd_,message,size,0,info->ai_addr,info->ai_addrlen) == -1){
            throw std::runtime_error("Error sending");
        }
        return true;
    }

    long int recv(char * buffer,int size){
        struct sockaddr_storage their_addr;

        socklen_t addr_len = sizeof(their_addr);

        auto  bytesReceived = recvfrom(fd_,buffer, size,0, (struct sockaddr *)&their_addr,&addr_len);
        buffer[bytesReceived] ='\0';
        if(bytesReceived == -1){
            throw std::runtime_error("Error recving");
        }
        return bytesReceived;
    }

    ~UdpSocket(){
        if(fd_ != -1 && destroy_){
            std::cout<<"destroying UDPSocket\n";
            close(fd_);
        }
    }

    int get() const {
        return fd_;
    }

private:
    int fd_;
    bool destroy_;

    void *get_in_addr(struct sockaddr *sa)
    {
        if (sa->sa_family == AF_INET) {
            return &(((struct sockaddr_in*)sa)->sin_addr);
        }
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }

    void getAddressInfo(struct addrinfo ** info,const std::string & port,const std::string & ip){
        struct addrinfo hints;

        memset(&hints,0,sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;

        const char * name = nullptr;
        if(ip==""){
            hints.ai_flags = AI_PASSIVE;
        }else{
            name = ip.c_str();
        }


        if(getaddrinfo(name,port.c_str(),&hints,info) != 0){
            throw std::runtime_error("Error fiinding get addr info");
        }
    }
};
