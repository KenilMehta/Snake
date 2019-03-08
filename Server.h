#include "UdpSocket.h"
#include "EpollWrapper.h"
#include "SbeEncoderDecoder.h"

#define BUFFERSIZE 2048
class Server : public EpollUserBase{
private:
    UdpSocket soc_;
    epoll::EpollWrapper epoll_;
    char buffer_[BUFFERSIZE];
    SbeEncoderDecoder encoderDecoder;
public:
    Server(std::string ip,std::string port):soc_(ip,port),epoll_(*this){
        epoll_.registerFd(soc_.get());
    }

    void onInputOnFd(int fd) override {
        UdpSocket s(fd);
        s.recv(buffer_, sizeof(buffer_));
        encoderDecoder.decodeMessage(buffer_, sizeof(buffer_));
    }

    void start(){
        epoll_.startReactor();
    }

    ~Server(){
        epoll_.stopReactor();
    }
};

