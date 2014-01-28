// Observer.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
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
	const std::string name = "女子高生";
	std::string state;

public:
	CJK() {}

	void Hittakuri()
	{
		state = "ひったくり";
		Notify();
	}

	std::string GetName() { return name; }
	std::string GetState() { return state; }
};


class CPolice : public IObserver
{
	const std::string name = "警察";
public:
	~CPolice() { std::cout << "任務終了" << std::endl; }
	void Update(CSubject* obj)
	{
		auto o = dynamic_cast<CJK*>(obj);
		std::cout << o->GetName() + "から" + name + "への依頼";
		std::cout << o->GetState() + "発生";
		std::cout << "-----------> 逮捕";
		std::cout << std::endl;
	}
};

class CFriend : public IObserver
{
	const std::string name = "友人";
public:
	~CFriend() { std::cout << "帰宅します" << std::endl; }
	void Update(CSubject* obj)
	{
		CJK* o = (CJK*)(obj);
		std::cout << o->GetName() + "から" + name + "への依頼";
		std::cout << o->GetState() + "発生";
		std::cout << "-----------> 取り逃がす";
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