/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "TollgateScene.h"

Scene * TollgateScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}

bool TollgateScene::init()
{
	bool bRet = false;
	do {
		auto visibleSize = Director::sharedDirector()->getVisibleSize();
		auto titleSprite = Sprite::create("title1.png");
		titleSprite->setPosition(Vec2(visibleSize.width / 3, visibleSize.height * 3 / 4));
		
		addChild(titleSprite, 2);

		m_player = Player::create();
		m_player->BindSprite(Sprite::create("sprite1.png"));
		m_player->setPosition(Vec2(200, visibleSize.height / 4));
		
		addChild(m_player, 3);
		initBG();

		scheduleUpdate();

		bRet = true;
	} while (0);
	return true;
}

void TollgateScene::update(float delta)
{
	int pos1_x = m_bgSprite1->getPositionX();
	int pos2_x = m_bgSprite2->getPositionX();

	int speed = 1;
	pos1_x -= speed;
	pos2_x -= speed;

	auto size = m_bgSprite1->getContentSize();
	if (pos1_x < -size.width / 2)
	{
		pos2_x = size.width / 2;
		pos1_x = size.width + size.width / 2;
	}

	if (pos2_x < -size.width / 2)
	{
		pos1_x = size.width / 2;
		pos2_x = size.width + size.width / 2;
	}
	m_bgSprite1->setPositionX(pos1_x);
	m_bgSprite2->setPositionX(pos2_x);
}

void TollgateScene::createJumpBt()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto jumpTile = LabelTTF::create("jump", "", 35);
	//auto jumpBt = ControlButton::create();

}

void TollgateScene::jumpEvent(Ref * pSender)
{
}

void TollgateScene::initBG()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_bgSprite1 = Sprite::create("tollgateBG.png");
	m_bgSprite1->setContentSize(Size(900,450));
	m_bgSprite1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(m_bgSprite1, 0);

	m_bgSprite2 = Sprite::create("tollgateBG.png");
	m_bgSprite2->setContentSize(Size(900, 450));
	m_bgSprite2->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));
	m_bgSprite2->setFlipX(true);
	addChild(m_bgSprite2, 0);
}
