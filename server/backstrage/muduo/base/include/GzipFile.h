#pragma once


#include "StringPiece.h"
#include "noncopyable.h"
#include <zlib.h>

namespace muduo
{

class GzipFile : noncopyable
{
private:
    explicit GzipFile(gzFile file)
        : file_(file)
    {
    }

    gzFile file_;
public:
    GzipFile(/* args */);
    ~GzipFile();
};
   
} // namespace muduo
