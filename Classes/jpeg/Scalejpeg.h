#ifndef __SCALE_JPEG__
#define __SCALE_JPEG__
#include "cocos2d.h"
//生成图片的缩略图（图片的一个缩小版本）
typedef std::function<void(const std::string& error)> logCall;
bool generate_image_thumbnail(const char* inputFile, const char* outputFile, const logCall& call);
#endif