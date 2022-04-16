#include "RuntimeStreamReader.h"

RuntimeStreamReader::RuntimeStreamReader(Stream *stream)
{
    _stream = stream;
}

bool RuntimeStreamReader::available()
{
    return _stream->available();
}

int RuntimeStreamReader::read()
{
    delay(20);
    return _stream->read();
}