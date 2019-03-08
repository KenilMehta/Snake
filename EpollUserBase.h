#pragma once

class EpollUserBase{
public:
    virtual void onInputOnFd(int fd) = 0;

};

