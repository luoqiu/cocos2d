//
//  PageViewTest.cpp
//  UITest
//
//  Created by apple on 14-9-5.
//
//

#include "PageViewTest.h"
#include "ContentLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* PageViewTest::createScene()
{
    // ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
    auto scene = Scene::create();
    
    // ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
    auto layer = PageViewTest::create();
    
    // ��HelloWorld����Ϊ�ӽڵ���ӵ�����
    scene->addChild(layer);
    
    // ���س�������
    return scene;
}


void PageViewTest::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // ��ʾ��Ϣ
    _displayValueLabel = Text::create("��ˮƽ�����ƶ�page", "fonts/Marker Felt.ttf", 32);
    _displayValueLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.8));
    this->addChild(_displayValueLabel);

    // ����һ��PageView
    auto pageView = PageView::create();
    // ����PageView��ContentSize
    pageView->setContentSize(Size(480.0f, 320.0f));
    // ����PageView����Ļ����λ��
    pageView->setPosition(Vec2((visibleSize.width - pageView->getContentSize().width) / 2.0f,
                               (visibleSize.height - pageView->getContentSize().height) / 2.0f));
    // ����PageView������������ֻ��3��page
    int pageCount = 3;
    // ѭ�����3��Layout���ؿ�ͼƬ��
    for (int i = 0; i < pageCount; ++i)
    {
        // ����һ��Layout
        Layout* layout = Layout::create();
        // ����Layout��ContentSize
        layout->setContentSize(Size(480.0f, 320.0f));
        // ����һ��ImageView
        ImageView* imageView = ImageView::create(StringUtils::format("level%d.png",i+1));
        imageView->setContentSize(Size(480.0f, 320.0f));
        imageView->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
        // ��ImageView���ΪLayout���ӽڵ�
        layout->addChild(imageView);
        // ��i��ʾ��λ���ϲ���Layout
        pageView->insertPage(layout,i);
    }
    // ����¼�������
    pageView->addEventListener([=](Ref* pSender,PageView::EventType type){
        switch (type)
        {
            case PageView::EventType::TURNING:
            {
                PageView* pageView = dynamic_cast<PageView*>(pSender);
                // ��_displayValueLabel�ı�����ʾPageIndex
                _displayValueLabel->setString(StringUtils::format("page = %ld",pageView->getCurPageIndex() + 1));
            }
                break;
                
            default:
                break;
        }
    });
    // ��PageView���δ������ӽڵ�
    this->addChild(pageView);
}

std::string PageViewTest::getTitle() const
{
    return "PageView����ҳ�������� Test ";
}
