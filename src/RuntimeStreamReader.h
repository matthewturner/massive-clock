#ifndef RuntimeStreamReader_h
#define RuntimeStreamReader_h

#include <Arduino.h>
#include "IStreamReader.h"

class RuntimeStreamReader : public IStreamReader
{
public:
    RuntimeStreamReader(Stream *stream);
    bool available() override;
    int read() override;

private:
    Stream *_stream;
};

#endif