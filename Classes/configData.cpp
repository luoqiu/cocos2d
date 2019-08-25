//
//  TextTest.cpp
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#include "configData.h"
#include "searchSqlite.h"
#include "ui/CocosGUI.h"
using namespace ui;
static const std::string defaultStr = "1";
static const int g_gradeTag = 1;
static const int g_contentTag = 2;

cocos2d::Scene * EnglishClass::createScene()
{
	// 创建一个场景对象，该对象将会由自动释放池管理内存的释放
	auto scene = Scene::create();

	// 创建层对象，该对象将会由自动释放池管理内存的释放
	auto layer = EnglishClass::create();

	// 将HelloWorld层作为子节点添加到场景
	scene->addChild(layer);

	// 返回场景对象
	return scene;
}

void EnglishClass::GetValueForKey(const std::string& key, std::string& value, const std::string& defaultValue)
{
	value = UserDefault::getInstance()->getStringForKey(key.c_str());
	if (value.empty())
	{
		value = defaultValue;
		UserDefault::getInstance()->setStringForKey("stage", defaultValue);
		UserDefault::getInstance()->flush();
	}
}

void EnglishClass::GetVec(std::string& index, std::vector<int>& vec)
{
	vec.clear();
	for (int i = atoi(index.c_str()); i < atoi(_wordsOnce.c_str()); ++i)
	{
		vec.push_back(i);
	}
}

bool EnglishClass::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_bGradeFlag = true;

	_stage = UserDefault::getInstance()->getStringForKey("stage");
	if (_stage.empty())
	{
		_stage = "小学英语";
		UserDefault::getInstance()->setStringForKey("stage", _stage);
		UserDefault::getInstance()->flush();
	}

	_sGrade = UserDefault::getInstance()->getStringForKey("grade");
	if (_sGrade.empty())
	{
		_sGrade = "人教第一册";
		UserDefault::getInstance()->setStringForKey("sGrade", _sGrade);
		UserDefault::getInstance()->flush();
	}

	 _index = UserDefault::getInstance()->getStringForKey(_sGrade.c_str());
	if (_index.empty())
	{
		_index = "1";
		UserDefault::getInstance()->setStringForKey(_sGrade.c_str(), _index);
		UserDefault::getInstance()->flush();
	}

	_wordsOnce = UserDefault::getInstance()->getStringForKey("_wordsOnce");
	if (_wordsOnce.empty())
	{
		_wordsOnce = "5";
		UserDefault::getInstance()->setStringForKey("_wordsOnce", _wordsOnce);
		UserDefault::getInstance()->flush();
	}

	_vecSerialumber.clear();
	for (int i =  1; i < 10; ++i)
	{
		_vecSerialumber.push_back(i);
	}
	SearchSqlite::GetInstance().SearchValue(_vecSerialumber, _stage, _vecGrade);

	_vecSerialumber.clear();
	for (int i = atoi(_index.c_str()) + 1; i < atoi(_wordsOnce.c_str()); ++i)
	{
		_vecSerialumber.push_back(i);
	}

	SearchSqlite::GetInstance().SearchValue(_vecSerialumber, _sGrade, _vecWords);

	return true;
}


void EnglishClass::onEnterGrade()
{
	auto chl = getChildByTag(g_contentTag);
	if (chl)
	{
		removeChildByTag(g_contentTag, true);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto listView = ListView::create();
	listView->setDirection(ScrollView::Direction::VERTICAL);
	// 设置ListView的背景图片
	listView->setBackGroundImage("green_edit.png");
	// 设置背景图片作为九宫格填充
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(visibleSize);
	listView->addEventListener([=](Ref *pSender, ListView::EventType type) {
		switch (type)
		{
		case ListView::EventType::ON_SELECTED_ITEM_END:
		{
			ListView* listView = static_cast<ListView*>(pSender);
			int index = listView->getCurSelectedIndex();
			if (index < _vecGrade.size())
			{
				std::string grade = _vecGrade[index];
				std::string gradeIndex;
				GetValueForKey(grade, gradeIndex, defaultStr);
				std::vector<int> vecIndex;
				GetVec(gradeIndex, vecIndex);
				_vecWords.clear();
				SearchSqlite::GetInstance().SearchValue(vecIndex, grade, _vecWords);
				//切换展示内容;
				_bGradeFlag = false;
			}

			break;
		}
		default:
			break;
		}
	});

	for (int i = 0; i < _vecGrade.size(); ++i)
	{
		// 创建一个Button
		Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
		// 设置Button的Name
		custom_button->setName(_vecGrade[i]);
		// 设置Button是否九宫格填充
		custom_button->setScale9Enabled(true);
		// 设置Button的ContentSize
		custom_button->setContentSize(Size(40, 20));
		// 设置Button的TitleText为对应_array的文本内容
		//custom_button->setTitleText(StringUtils::format("listview_item_%d", i));
		custom_button->setTitleText(_vecGrade[i]);
		// 设置Button的文本字体大小
		custom_button->setTitleFontSize(12);
		
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
	listView->setTag(g_gradeTag);
	addChild(listView);
}


void EnglishClass::onEnterContent()
{
	auto chl = getChildByTag(g_gradeTag);
	if (chl)
	{
		removeChildByTag(g_gradeTag, true);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto listView = ListView::create();
	listView->setDirection(ScrollView::Direction::HORIZONTAL);
	// 设置ListView的背景图片
	listView->setBackGroundImage("green_edit.png");
	// 设置背景图片作为九宫格填充
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(visibleSize);
	listView->addEventListener([=](Ref *pSender, ListView::EventType type) {
		switch (type)
		{
		case ListView::EventType::ON_SELECTED_ITEM_END:
		{
			ListView* listView = static_cast<ListView*>(pSender);
			int index = listView->getCurSelectedIndex();
			if (index < _vecGrade.size())
			{
				std::string grade = _vecGrade[index];
				std::string gradeIndex;
				GetValueForKey(grade, gradeIndex, defaultStr);
				std::vector<int> vecIndex;
				GetVec(gradeIndex, vecIndex);
				_vecWords.clear();
				SearchSqlite::GetInstance().SearchValue(vecIndex, grade, _vecWords);
				//切换展示内容;
				_bGradeFlag = true;
			}

			break;
		}
		default:
			break;
		}
	});

}

void EnglishClass::onEnter()
{
	Layer::onEnter();

	if (_bGradeFlag)
	{
		onEnterGrade();
	}
	else
	{
		onEnterContent();
	}
}
