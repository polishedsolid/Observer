// Observer.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>



class CSubject;

// Observer Interface
class IObserver
{
public:
	virtual ~IObserver() {}
	virtual void Update(CSubject* obj) = 0;
};

// Subject
class CSubject
{
protected:
	std::vector<IObserver*> observers;

public:

	virtual ~CSubject() { DeleteAllObserver(); }

	void AddObserver(IObserver* obs)
	{
		observers.push_back(obs);
	}

	void DeleteObserver(IObserver* obs)
	{
		auto it = std::find(observers.begin(), observers.end(), obs);
		if (it == observers.end()) return;
		observers.erase(it);
	}

	void DeleteAllObserver()
	{
		observers.clear();
	}

	void Notify()
	{
		for each(auto o in observers)
		{
			o->Update(this);
		}
	}

};

class CJK : public CSubject
{
	const std::string name = "���q����";
	std::string state;

public:
	CJK() {}

	void Hittakuri()
	{
		state = "�Ђ�������";
		Notify();
	}

	std::string GetName() { return name; }
	std::string GetState() { return state; }
};


class CPolice : public IObserver
{
	const std::string name = "�x�@";
public:
	~CPolice() { std::cout << "�C���I��" << std::endl; }
	void Update(CSubject* obj)
	{
		auto o = dynamic_cast<CJK*>(obj);
		std::cout << o->GetName() + "����" + name + "�ւ̈˗�";
		std::cout << o->GetState() + "����";
		std::cout << "-----------> �ߕ�";
		std::cout << std::endl;
	}
};

class CFriend : public IObserver
{
	const std::string name = "�F�l";
public:
	~CFriend() { std::cout << "�A��܂�" << std::endl; }
	void Update(CSubject* obj)
	{
		CJK* o = (CJK*)(obj);
		std::cout << o->GetName() + "����" + name + "�ւ̈˗�";
		std::cout << o->GetState() + "����";
		std::cout << "-----------> ��蓦����";
		std::cout << std::endl;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	auto jk = std::make_unique<CJK>();
	auto police = std::make_unique<CPolice>();
	auto frend = std::make_unique<CFriend>();

	jk->AddObserver(police.get());
	jk->AddObserver(frend.get());

	jk->Hittakuri();

	getchar();

	return 0;
}