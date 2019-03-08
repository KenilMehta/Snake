#include "GeneratedFiles/sbeschema/MessageHeader.h"
#include "GeneratedFiles/sbeschema/NewPlayer.h"
#include <iostream>
using namespace sbeschema;
#define ACTINGVERSION 0
class SbeEncoderDecoder {
public:
    uint64_t createNewPlayerMessage(char * buffer,uint64_t size){
        MessageHeader hdr;
        NewPlayer newPlayer;

        hdr.wrap(buffer,0,ACTINGVERSION,size).blockLength(NewPlayer::sbeBlockLength()).templateId(NewPlayer::sbeTemplateId())
        .schemaId(NewPlayer::sbeSchemaId())
        .version(NewPlayer::sbeSchemaVersion());

        int encodedLength = hdr.encodedLength();

        size = size - encodedLength;
        newPlayer.wrapForEncode(buffer,encodedLength,size);
        return newPlayer.encodedLength() + hdr.encodedLength();
    }

    void decodeMessage(char * buffer,uint64_t size){
            MessageHeader hdr;
            hdr.wrap(buffer,0,ACTINGVERSION,size);
            std::cout<<"Received the following the template id "<<hdr.templateId()<<"\n";
    }

};

