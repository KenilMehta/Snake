#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include "EpollUserBase.h"
#pragma once
namespace epoll {

class EpollWrapper {
public:
  EpollWrapper(EpollUserBase & parent) : parent_{parent}{
      isRunning_ = false;
    epfd_ = epoll_create(5);
    if (epfd_ == -1) {
      throw std::runtime_error("Cannot create EpollWrapper");
    }
  }

  bool registerFd(int fd) {

    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = fd;

    if (epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &ev) == -1) {
      perror("epoll_ctl");
      return false;
    }
    std::cout << "Registered the following fd with Epoll " << fd << "\n";
    return true;
  }

  void poll(int timeInMillis){
    int noOfReadyFds = epoll_wait(epfd_, events, sizeof(events), timeInMillis);

    if (noOfReadyFds == -1) {
      if(isRunning_)
        throw std::runtime_error("Error waiting EpollWrapper Reactor");
    }

    for(int i=0;i<noOfReadyFds;++i){
      int fd = events[i].data.fd;
      parent_.onInputOnFd(fd);
    }
  }

  void startReactor() {
    isRunning_ = true;

    while (isRunning_) {
      poll(60000);
    }
  }



  void stopReactor(){
      isRunning_ = false;
  }

  ~EpollWrapper() {
    std::cout << "Closing EpollWrapper FD" << std::endl;
    if (epfd_ != -1) {
      close(epfd_);
    }
  }

private:
  int epfd_;
  bool isRunning_;
  EpollUserBase & parent_;
    epoll_event events[1024];
};
} // namespace epoll
