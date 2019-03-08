#include "EpollWrapper.h"
#include "UdpSocket.h"
#include "SbeEncoderDecoder.h"

#define BUFFERSIZE 2048
class Client : public EpollUserBase{
private:
    epoll::EpollWrapper epoll_;
    UdpSocket soc_;
    SbeEncoderDecoder sbeEncoder;
    char buffer[BUFFERSIZE];
public:
    Client(std::string ip,std::string port):epoll_(*this),soc_(ip,port){
        epoll_.registerFd(soc_.get());

        auto size = sbeEncoder.createNewPlayerMessage(buffer, sizeof(buffer));
        if(!soc_.send(buffer,size,"10.233.61.21","3456")){
            throw std::runtime_error("Error sending new player message");
        }
        /*char a[3] = "hi";
        soc_.send(a,3,"10.233.61.21","3456");*/
    }

    void onInputOnFd(int fd){
        std::cout<<fd;
    }

};

int main(){
    Client client("","1234");

    return 0;
}
