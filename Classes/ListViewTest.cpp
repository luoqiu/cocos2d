//
//  ListViewTest.cpp
//  UITest
//
//  Created by apple on 14-9-5.
//
//
//#include "ContentLayer.h"
#include "ListViewTest.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Scalejpeg.h"
#include "platform/CCFileUtils.h"
#include "deprecated/CCstring.h"
#include "HttpDown.h"
#include "GetUrl.h"
#include "configData.h"


using namespace CocosDenshion;
using namespace ui;
static const std::string path = "https://m.baidu.com/sf/vsearch?pd=image_content&atn=page&fr=tab&tn=vsearch&ss=100&sa=tb&rsv_sug4=2235&inputT=2234&word=";
using namespace cocos2d;

typedef struct _MENU
{
	std::string name;
	//Scene* scene;
	Widget::ccWidgetTouchCallback callBack;
}MENU;

MENU menu[] =
{
	{"英语", [](Ref* p,Widget::TouchEventType type) {}},
	{"数学", [](Ref* p,Widget::TouchEventType type) {}},
	{"关于", [](Ref* p,Widget::TouchEventType type) {}},
	{"退出", [](Ref* p,Widget::TouchEventType type) {}},
};

static int items = sizeof(menu) / sizeof(menu[0]);



Scene* ListViewTest::createScene()
{
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = ListViewTest::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}

void ListViewTest::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // 创建一个ListView
    auto listView = ListView::create();
    // 设置ListView的方向，本例为VERTICAL（垂直）
    listView->setDirection(ScrollView::Direction::VERTICAL);
    // 设置ListView的背景图片
    listView->setBackGroundImage("green_edit.png");
    // 设置背景图片作为九宫格填充
    listView->setBackGroundImageScale9Enabled(true);
    // 设置ListView的ContentSize
    //listView->setContentSize(Size(480, 260));
	listView->setContentSize(visibleSize);
    // 设置ListView的位置
    //listView->setPosition(Vec2((visibleSize.width - listView->getContentSize().width) / 2.0f,
    //                           (visibleSize.height - listView->getContentSize().height) / 2.0f));
	listView->setPosition(Vec2::ZERO);
    // 添加事件监听器
    listView->addEventListener([=](Ref *pSender, ListView::EventType type){
        switch (type)
        {
            case ListView::EventType::ON_SELECTED_ITEM_START:
            {
                ListView* listView = static_cast<ListView*>(pSender);
                log("select child start index = %ld", listView->getCurSelectedIndex());
                break;
            }
            case ListView::EventType::ON_SELECTED_ITEM_END:
            {
                ListView* listView = static_cast<ListView*>(pSender);
                log("select child end index = %ld", listView->getCurSelectedIndex());
				switch (listView->getCurSelectedIndex())
				{
				case 0:
				{
					auto scence = EnglishClass::createScene();
					Director::getInstance()->pushScene(scence);
					//Director::getInstance()->replaceScene(scence);
					break;
				}					
				default:
					break;
				}

// 				auto effect = SimpleAudioEngine::getInstance();
// 				effect->preloadEffect("a.wav");
// 				effect->setEffectsVolume(1);
// 				effect->playEffect("a.wav");
// 				//ShowImage();
// 				sFileName = "bed.jpg";
// 				onMenuGetTestClicked(NULL);


                break;
            }
            default:
                break;
        }

    });
    // 添加事件监听器
    listView->addEventListener([=](Ref* pSender, ScrollView::EventType type){
        switch (type) {
            case ScrollView::EventType::SCROLL_TO_BOTTOM:
                log("SCROLL_TO_BOTTOM");
                break;
            case ScrollView::EventType::SCROLL_TO_TOP:
                log("SCROLL_TO_TOP");
                break;
            default:
                break;
        }
    });
    // 将ListView添加为当前层的子节点
    this->addChild(listView);
    
    // 添加自定义item（10个Button）
    for (int i = 0; i < items; ++i)
    {
        // 创建一个Button
        Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
        // 设置Button的Name
        custom_button->setName("Title Button");
        // 设置Button是否九宫格填充
        custom_button->setScale9Enabled(true);
        // 设置Button的ContentSize
        custom_button->setContentSize(Size(40, 20));
        // 设置Button的TitleText为对应_array的文本内容
        //custom_button->setTitleText(StringUtils::format("listview_item_%d", i));
		custom_button->setTitleText(menu[i].name);
        // 设置Button的文本字体大小
        custom_button->setTitleFontSize(12);
		custom_button->addTouchEventListener(menu[i].callBack);
        // 创建一个Layout，用来添加Button
        Layout *custom_item = Layout::create();
        // 设置Layout的ContentSize和Button的ContentSize一致
        custom_item->setContentSize(custom_button->getContentSize());
        // 设置Layout的坐标位置
        custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
        // 将Button添加为Layout的字节
        custom_item->addChild(custom_button);
        // 将Layout添加为ListView的子节点
        listView->addChild(custom_item);
    }    
}

std::string ListViewTest::getTitle() const
{

    return "ListView Test ";
}

void ListViewTest::ShowError(const std::string& error)
{
	CCTexture2D* texture = new CCTexture2D();
	static int i = 1;

	texture->initWithString(error.c_str(), "", 15);
	auto sprit = Sprite::createWithTexture(texture);
	sprit->setPosition(Vec2(200, i++ * 20));
	addChild(sprit);
}

bool ListViewTest::ShowLocalImage(std::string& p)
{
	CCImage* img = new CCImage;

	img->initWithImageFile(p);

	if (img->getWidth() == 0 || img->getHeight() == 0)
	{
		ShowError("error local img");

		return false;
	}

	float scale = img->getWidth() > img->getHeight() ? img->getWidth() / 200 : img->getHeight() / 200;

	CCTexture2D* texture = new CCTexture2D();
	texture->initWithImage(img);
	auto sprit = Sprite::createWithTexture(texture);
	sprit->setPosition(Vec2(200, 200));
	sprit->setScale(1 / scale);
	addChild(sprit);

	return true;
}

bool ListViewTest::ShowImage(std::string& p)
{
	CCImage* img = new CCImage;
	
	img->initWithImageFile(p);
	//img->initWithImageData((unsigned char*)buffer->data(), buffer->size());
	if (img->getWidth() == 0 || img->getHeight() == 0)
	{
		ShowError("error img" + StringUtils::format("%d", vUrls.size()));
		index++;
		if (index < vUrls.size())
		{
			GetImgRes();
		}
		return false;
	}

	float scale = img->getWidth() > img->getHeight() ? img->getWidth() / 200 : img->getHeight() / 200;

	CCTexture2D* texture = new CCTexture2D();
	texture->initWithImage(img);
	auto sprit = Sprite::createWithTexture(texture);
	sprit->setPosition(Vec2(200,200));
	sprit->setScale(1 / scale);
	addChild(sprit);

	return true;
}

void ListViewTest::ShowResImg(std::vector<char>* buffer)
{
	if (buffer == NULL)
	{
		index++;
		if (index < vUrls.size())
		{			
			GetImgRes();
		}
		return ;
	}
	std::string buf(buffer->begin(), buffer->end());
	std::string filePath = FileUtils::getInstance()->getWritablePath();
	filePath += sFileName;

	FILE* file = fopen(filePath.c_str(), "wb");
	if (file)
	{
		int len = fwrite(buf.c_str(), 1, buf.size(), file);
		if (len != buf.size())
		{
			auto slen = CCString::createWithFormat("len %d,errno:%d", len, errno);
			ShowError(slen->getCString());

			ShowError("error");
			return;
		}

		fclose(file);

		//ShowImage(filePath);
	}
	else
	{
		ShowError(filePath);
	}
}

void ListViewTest::GetImgRes()
{
	//HttpDown::GetInstance().SetBackCall(CC_CALLBACK_1(ListViewTest::ShowResImg, this));
	//HttpDown::GetInstance().HttpGetTest(vUrls[index]);
}

void ListViewTest::GetRes(std::vector<char>* p)
{
	vUrls.clear();

	if (p == NULL)
	{
		return;
	}

	std::string response(p->begin(), p->end());
	GetUrl::GetInstance().getUrl(response, vUrls);

	if (vUrls.size() == 0)
	{
		return;
	}

	index = 0;
	GetImgRes();
}

#include "network\HttpClient.h"
//E:\cocos2d\codes\Hello\cocos2d\cocos\network\HttpClient.h
//get请求
void ListViewTest::onMenuGetTestClicked(cocos2d::CCObject *sender)
{
// 	std::string filepath = FileUtils::getInstance()->getWritablePath();
// 	filepath += sFileName;
// 	if (FileUtils::getInstance()->isFileExist(filepath))
// 	{
// 		ShowError(filepath + " is Exist");
// 		ShowLocalImage(filepath);
// 		return;
// 	}
// 
// 	HttpDown::GetInstance().SetBackCall(CC_CALLBACK_1(ListViewTest::GetRes,this));
// 
// 	std::string urlPath = path + sFileName;
// 
// 	HttpDown::GetInstance().HttpGetTest(urlPath);


// 	return;
// 	// test 1
// 	{
// 		auto request = new network::HttpRequest();//创建request对象,这里new出来的对象不能使用autorelease()，原因后述
// 		request->setUrl("https://m.baidu.com/sf/vsearch?pd=image_content&atn=page&fr=tab&tn=vsearch&ss=100&sa=tb&rsv_sug4=2235&inputT=2234&word=" );//设置url
// 		//request->setUrl( "https://ss1.bdstatic.com/70cFvXSh_Q1YnxGkpoWK1HF6hhy/it/u=255657492,1187028829&fm=26&gp=0.jpg");
// 		//request->setUrl("https://ss1.bdstatic.com/70cFvXSh_Q1YnxGkpoWK1HF6hhy/it/u=255657492,1187028829&fm=26&gp=0.jpg");
// 		request->setRequestType(network::HttpRequest::Type::GET);//设置请求方式
// 		request->setResponseCallback(this, callfuncND_selector(ListViewTest::onHttpRequestCompleted));//这是回调对象和回调函数
// 		request->setTag("GET test1");//设置用户标识，可以通过response获取
// 		cocos2d::network::HttpClient::getInstance()->send(request);//使用CCHttpClient共享实例来发送request
// 		request->release();//调用release()
// 	}
}
// //这里就是我们要处理接收到数据的回调函数了，sender为CCHttpClient实例指针，data为接收到的response指针
// void ListViewTest::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
// {
// 	auto response = (network::HttpResponse*)data;
// 
// 	if (!response)
// 	{
// 		return;
// 	}
// 
// 	// 获取对应request的字符串标识
// 	if (0 != strlen(response->getHttpRequest()->getTag()))
// 	{
// 		log("%s completed", response->getHttpRequest()->getTag());
// 	}
// 	//获取返回代码，比如200、404等
// 	int statusCode = response->getResponseCode();
// 	char statusString[64] = {};
// 	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
// 
// 	log("response code: %d", statusCode);
// 
// 	if (!response->isSucceed())
// 	{
// 		log("response failed");
// 		log("error buffer: %s", response->getErrorBuffer());//可以调用getErrorBuffer()来获取错误原因
// 		return;
// 	}
// 
// 	// dump data
// 	std::vector<char> *buffer = response->getResponseData();//用来获取接收到的数据
// 	std::string buf(buffer->begin(), buffer->end());
// 	char* p = "cow.jpg";
// 	std::string sFileName = "cow.jpg";
// 	std::string path = FileUtils::getInstance()->getWritablePath();
// #if CC_PLATFORM_ANDROID==CC_TARGET_PLATFORM
// 	//path = "/sdcard/DCIM/";
// #endif
// 	path += sFileName;
// 	FILE* file = fopen(path.c_str(), "wb");
// 	if (file)
// 	{
// 		
// 		int len = fwrite(buf.c_str(),  1, buf.size(), file);
// 		if (len != buf.size())
// 		{
// 				//StringUtils::toString(customTime)
// 			auto slen = CCString::createWithFormat("len %d,errno:%d", len,errno);
// 			ShowError(slen->getCString());
// 
// 			ShowError("error");
// 			return;
// 		}
// 		
// 		fclose(file);
// 
// 		ShowImage(path);
// 	}
// 	else
// 	{
// 		ShowError(path);
// 	}
// 	CCImage* img = new CCImage;
// 	img->initWithImageFile("cow.jpg");
// 	//img->initWithImageData((unsigned char*)buffer->data(), buffer->size());
// 	
// 	
// 	CCTexture2D* texture = new CCTexture2D();
// 
// 
// 	texture->initWithImage(img);
// 	auto sprit = Sprite::createWithTexture(texture);
// 	sprit->setPosition(Vec2::ANCHOR_MIDDLE);
// 	this->addChild(sprit);
	//img->release();
//}