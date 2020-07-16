#pragma once
#include <string>

class CompanyA
{
public:
	//...
	void sendCleartext(const std::string& msg);
	void sendEncrypted(const std::string& msg);
	//...
};

class CompanyB
{
public:
	//...
	void sendCleartext(const std::string& msg);
	void sendEncrypted(const std::string& msg);
	//...
};

class CompanyZ		// 이 클래스는 sendCleartext 함수를 제공하지 않습니다.
{
public:
	//...
	void sendEncrypted(const std::string& msg);
	//...
};


class MsgInfo // 메시지 생성에 사용되는 정보를 담기 위한 클래스
{
	//... 
};





template<typename Company>
class MsgSender
{
public:
	//...									// 생성자, 소멸자, 등등
		void sendClear(const MsgInfo& info)
	{
		std::string msg;
		//	info로부터 msg를 만듭니다;

		Company c;
		c.sendCleartext(msg);
	}
	void sendSecret(const MsgInfo& info) // sendClear 함수와 비슷합니다. 단, 
	{
		//...
	}								// c.sendEnCrypted 힘수를 호출하는 점이 차이
};

template<>								// MsgSender 템플릿의 완전 특수화 버전입니다. sendClear 함수가 빠진것만 제외
class MsgSender<CompanyZ>				// 하면 일반형 템플릿과 똑같습니다.
{
public:
	//...
	void sendSecret(const MsgInfo& info)
	{
		//...
	}
};
//위의 2개의 클래스는 서로 다르다.


//다음 코드는 컴파일이 되지 않는다.
//'sendClear 함수가 존재하지 않는다'라는 것이 컴파일이 안되는 이유.
//우리 눈에는 기본 클래스에 들어있는 sendClear 함수가 버젓이 보이는데도, 컴파일러는 기본 클래스를 들여다보려고 하지도 않는 것
//입니다.어째서일까요 ?
//
//문제는 간단합니다.컴파일러가 LoggingMsgSender 클래스 템플릿의 정의와 마주칠 때, 컴파일러는 대체 이 클래스가 어디서 파생된
//것인지를 모른다는 것입니다.MsgSender<Company>인 것은 분명 맞죠. 하지만 Company는 템플릿 매개변수이고, 이 템플릿 매개 변수
//는 나중(LoggingMsgSender가 인스턴스로 만들어질 때)까지 무엇이 될지 알 수 없습니다.Company가 정확히 무엇인지 모르는 상황
//에서는 MsgSender<Company> 클래스가 어떤 형태인지 알 방법이 있을리가 없겠죠 ? 이러니, sendClear 함수가 들어 있는지 없는지
//알아낼 방법이 없는 것도 당연합니다.
template<typename Company>
class LoggingMsgSender : public MsgSender<Company>
{
public:
	//...
	void sendClearMsg(const MsgInfo& info)
	{
		// "메시지 전송 전" 정보를 로그에 기록합니다; 
		sendClear(info);						// 만약 Company == CompanyZ 라면 이 함수는 있을 수 조차 없습니다!
		// "메시지 전송 후" 정보를 로그에 기록합니다;
	}
	//...
};