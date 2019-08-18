#include "Image.h"

void createImage()
{
	std::vector<char> *buffer = NULL;
	CCImage* img = new CCImage;
	img->initWithImageData((unsigned char*)buffer->data(), buffer->size());

	CCTexture2D* texture = new CCTexture2D();

	bool isImg = texture->initWithImage(img);

	img->release();
}