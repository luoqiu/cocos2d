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

cocos2d::Scene * EnglishClass::createScene()
{
	// ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto scene = Scene::create();

	// ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto layer = EnglishClass::create();

	// ��HelloWorld����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);

	// ���س�������
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

	_stage = UserDefault::getInstance()->getStringForKey("stage");
	if (_stage.empty())
	{
		_stage = "СѧӢ��";
		UserDefault::getInstance()->setStringForKey("stage", _stage);
		UserDefault::getInstance()->flush();
	}

	_sGrade = UserDefault::getInstance()->getStringForKey("grade");
	if (_sGrade.empty())
	{
		_sGrade = "�˽̵�һ��";
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

void EnglishClass::onEnter()
{
	Layer::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto listView = ListView::create();
	listView->setDirection(ScrollView::Direction::VERTICAL);
	// ����ListView�ı���ͼƬ
	listView->setBackGroundImage("green_edit.png");
	// ���ñ���ͼƬ��Ϊ�Ź������
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
			}

			break;
		}
		default:
			break;
		}
	});

}
