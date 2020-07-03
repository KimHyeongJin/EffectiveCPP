#pragma once
#define FORTEST

#include <iostream>
//항목 9: 객체 생성 및 소멸 과정 중에는 절대로 가상 함수를 호출하지 말자.
/*
객체 생성 및 소멸 과정 중에는 가상 함수를 호출하면 절대로 안됩니다.
우선 호출 결과가 여러분이 원하는 대로 돌아가지 않을 것이고, 원하는 대로 돌아 간다고 해도 여러분은 여전히 심각한 얼굴을 하고 있을 것이 분명하기 때문입니다.
자바(Java) 혹은 C#을 하다가 이쪽 세계에 발을 들여놓은 분들은 이번 항 목을 종잇장이 닳을 때까지 읽으셔야 할 것입니다.
여러분이 쓰시던 언어가 '비뚤'이라면， C++는 심하게 '빼뚤'인 부분이 바로 이번 항목의 내용이니까요.

주식 거래를 본떠 만든 클래스 계통 구조가 있다고 가정합시다.
이를테면 매도 주문, 매수 주문 등등이 있겠죠. 
이러한 거래를 모델링히는 데 있어서 중요한 포인트라면 감사(audit) 기 능이 있어야 한다는 점입니다.
그렇기 때문에 주식 거래 객체가 생성될 때마다 감사 로그 (audit log)에 적절한 거래 내역이 만들어지도록 해야 합니다.
결국, 다음과 같은 클래스 정도가 나와 주는 게 맞을 것 같습니다.
*/

//모든 거래에 대한 기본 클래스
class Transaction
{
public:
	Transaction();
	virtual void logTransaction() const = 0;//타입에 따라 달라지는 로그 기록을 만듭니다.
	//...
};

//기본 클래스 생성자의 구현
Transaction::Transaction()
{
	//...
	logTransaction();//마지막 동작으로, 이 거래를 로깅(하기 시작)합니다.
}

#ifdef FORTEST
void Transaction::logTransaction() const
{
	std::cout << "Transaction::logTransaction" << std::endl;
}
#endif

//Transaction의 파생 클래스
class BuyTransaction : public Transaction
{
public:
	BuyTransaction() {};
	virtual void logTransaction() const;//타입에 따라 달라지는 로그 기록을 만듭니다.
	//...
};

#ifdef FORTEST
void BuyTransaction::logTransaction() const
{
	std::cout << "BuyTransaction::logTransaction" << std::endl;
}
#endif

//Transaction의 파생 클래스
class SellTransaction : public Transaction
{
public:
	SellTransaction() {};
	virtual void logTransaction() const;//타입에 따라 달라지는 로그 기록을 만듭니다.
	//...
};

#ifdef FORTEST
void SellTransaction::logTransaction() const
{
	std::cout << "SellTransaction::logTransaction" << std::endl;
}
#endif

/*
이제 아래의 코드가 실행될 때 어떻게 되는지 생각해 볼까요?
BuyTransaction b;

BuyTransaction 생성자가 호출되는 것은 어쨌든 맞습니다.
그러나 우선은 Transaction 생성자가 호출되어야 합니다.
파생 클래스 객체가 생성될 때 그 객체의 기본 클래스 부분이 파생 클래스 부분보다 먼저 호출되는 것이 정석이니까요.
Transaction 생성자의 마지막 줄을 힐끗 보면 가상 함수인 logTransaction을 호출히는 문장이 보이는데, 무척이나 당혹스러운 사건이 벌어지는 부분이 바로 이 문장입니다.
여기서 호출되는 logTransaction 함수는 BuyTransaction의 것이 아니라 Transaction의 것이란 사실! 지금 생성되는 객체의 타입이 BuyTransaction인데도 말이죠 잘 새겨두세요.
기본 클래스의 생성자가 호출될 동안에는, 가상 함수는 절대로 파생 클래스 쪽으로 내려가지 않습니다.
그 대신, 객 체 자신이 기본 클래스 타입인 것처럼 동작합니다. 이해가 안 되세요P 기본 클래스 생성 과 정에서는 가상 함수가 먹히지 않는다고요.

그다지 직관적이지 않아 보이긴 합니다만 이 같은 동작에는 다 이유가 있습니다.
****** 아시다시피 기본 클래스 생성자는 파생 클래스 생성자보다 앞서서 실행되기 때문에 기본 클래스 생성자가 돌아가고 있을 시점에 파생 클래스 데이터 멤버는 아직 초기화된 상태가 아니라는 것이 핵심입니다. ******

지금 해드린 이야기보다 사실 다섯 배는 더 핵심적인 이야기를 꺼낼 때가 왔습니다.
파생 클래스 객체의 기본 클래스 부분이 생성되는 동안은 그 객체의 타입은 바로 기본 클래스입니다.
호출되는 가상 함수는 모두 기본 클래스의 것으로 결정(resolve)될 뿐만 아니라, 런타임 타입 정보를 사용하는 언어 요소[이를 테면 dynamic_cast(항목 27 참조)라든지 typeid 같은 것]를 사용한다고 해도 이 순간엔
모두 기본 클래스 타입의 객체로 취급합니다.
위의 예제를 가지고 설명해 볼까요? BuyTransaction 객체의 기본 클래스 부분을 초기화하기 위해 Transaction 생성자가 실행되고 있는 동안에는, 그 객체의 타입이 Transaction이라는 이야기 입니다.
이런 식의 처리는 C++ 언어의 다른 모든 기능에서 이루어지고 있고, 타당성도 아주 충분합니다. BuyTransaction 클래스만의 데이터는 아직 초기화된 상태가 아니기 때문에, 아예 없었던 것처럼 취급하는 편이 최고로 안전하다는 거죠.
그러니까 파생 클래스의 생성자의 실행이 시작되어야만 그 객체가 비로소 파생 클래스 객체의 면모를 갖게 됩니다.

객체가 소멸될(소멸자가 호출될) 때는 어떻게 될까요? 똑같이 생각하면 됩니다. 파생 클래스의 소멸자가 일단 호출되고 나면 파생 클래스만의 데이터 멤버는 정의되지 않은 값으로 가정하기 때문에, 이제부터 C++는 이들을 없는 것처럼 취급하고 진행합니다.
기본 클래스 소멸자에 진입할 당시의 객체는 더도 덜도 아닌 기본 클래스 객체가 되며, 모든 C++ 기능들(가상함수, dynamic_cast, 기타 등등) 역시 기본 클래스 객체의 자격으로 처리합니다.

위의 예제 코드를 다시 봐주세요. Transaction 생성자에서 가상 함수를 직접 호출하는 코드가 바로 보이죠? 이번 항목의 지침을 위반한 것인데, 반론의 여지가 없을 뿐 아니라 눈에도 잘 띄는 위반이 되겠습니다.
이런 위반은 누가 보더라도 발견이 쉽기 때문에, 이런 경우에 대해 경고 메시지를 내어 주는 컴파일러도 꽤 있습니다(물론 아닌 컴파일러도 꽤 되지요. 컴파일러 경고에 대해 더 알고 싶은 분은 항목 53을 참고 하시면 됩니다).
뭐 컴파일러 경고가 나오지 않더라도 프로그램 실행 전에 문제가 드러날 수도 있습니다. logTransaction 함수가 Transaction 클래스에서 순수 가상 함수로 선언되어 있기 때문입니다.
이 함수의 정의가 존재하지 않으면(이런 일이 없을거 같죠? 그런데 가능합니다. 항목 34 참조) 링크 단계에서 에러가 생깁니다. 링크가 제대로 되려면 Transaction::logTransaction 의 구현 코드를 찾아야 하는데,
찾아질 리가 없으니까요.

생성자 혹은 소멸자 안에서 가상 함수가 호출되는지를 잡아내는 일이 항상 쉬운 것은 아닙니다. Transaction 의 생성자가 여러 개 된다고 가정해 보세요. 각 생성자에서 하는 일이 조금씩은 다르겠지만 몇 가지 작업은 똑같을 텐데요.
똑같은 작업을 모아 공동의 초기화 코드로 만들어 두면 코드 판박이 현상을 막을 수 있겠지요? 대개 이런 설계의 열매로 private 멤버인 비가상 초기화 함수가 만들어지는데, 이 함수 안에서 logTransaction을 호출한다고
가정해 봅시다.
*/

//Transaction의 생성자 함수에서 logTransaction을 호출하는 것보다 더 사악한 코드
class Transaction
{
public:
	Transaction() { Init(); };
	virtual void logTransaction() const = 0;//타입에 따라 달라지는 로그 기록을 만듭니다.
	//...

private:
	void Init()
	{
		//....
		logTransaction();
	}
};
/*
이 코드는 앞의 코드와 비교해서 볼 때 개념적으로는 똑같은 코드이지만, 사악한 걸로 따지면 한 술도 모자라 몇 술 더 뜨는 코드입니다. 왜냐하면 앞의 코드와 달리 컴파일도 잘 되고
링크도 말끔하게 되기때문입니다. 이 코드가 실행된다고 생각해 보세요. logTransaction은 Transaction 클래스 안에서 순수 가상 함수이기 때문에, 대부분의 시스템은 순수 가상함수가 
호출될 때 프로그램을 바로 끝내(abort) 버립니다(이때 갑작스런 종료라는 메시지도 출력하고요). 이 정도면 고마운 경우죠. logTransaction 함수가 '보통' 가상(즉, 순수 가상이 아닌) 함수이며
Transaction의 멤버 버전이 구현되어 있을 경우엔 머리가 터지기 시작합니다. 반면에 파생 클래스 객체가 생성되는데 호출되는 logTransaction 함수는 어째서 Transaction 의 것인가에 대해
사태파악을 못하고 돌아버리는 쪽은 여러분 일테고요. 이런 문제를 피하는 방법은 생성 중이거나 소멸 중인 객체에 대해 생성자나 소멸자에서 가상 함수를 호출하는 코드를 
철저히 솎아내고, 생성자와 소멸자가 호출하는 모든 함수들이 똑같은 제약을 따르도록 만드는 일 외엔 없습니다.
Transaction 생성자에서 가상 함수를 호출하는 것은 이런 바람직한 일과 확실히 거리가 멉니다. 잊지 마세요.

이제는 이 문제의 대처방법에 대해 말씀드릴 때이군요. 방법은 여러 가지이지만 한 가지만 소개하지요. logTransaction을 Transaction 클래스의 비가상 멤버 함수로 바꾸는 것입니다.
그러고 나서 파생 클래스의 생정자들로 하여금 필요한 로그 정보를 Transaction의 생성자로 넘겨야 한다는 규칙을 만듭니다. logTransaction이 비가상 함수이기 때문에
Transaction 의 생성자는 이 함수를 안전하게 호출할 수 있습니다. 다음과 같이 말이죠.
*/
class Transaction
{
public:
	Transaction(const std::string log);
	void logTransaction(const std::string log) const;//이제는 비가상 함수 입니다.
	//...

};

//기본 클래스 생성자의 구현
Transaction::Transaction(const std::string log)
{
	//...
	logTransaction(const std::string log);//이제는 비가상 함수를 호출합니다.
}

//Transaction의 파생 클래스
class BuyTransaction : public Transaction
{
public:
	BuyTransaction(parameters) :Transaction(createLogString(parameters)){};//로그 정보를 기본 클래스 생성자로 넘깁니다.
	//...
private:
	static std::string createLogString(parameters);
};

/*
무슨 뜻인지 아시겠어요? 기본 클래스 부분이 생성될 때는 가상 함수를 호출한다 해도 기본 클래스의 울타리를 넘어 내려갈 수 없기 때문에(파생 클래스는 아직 존재 하지 않잖아...), 필요한 초기화 정보를 파생 클래스
쪽에서 기본 클래스 생성자로 '올려'주도록 만듦으로써 부족한 부분을 역으로 채울 수 있다는 점입니다(내려 올 수 없으니 올려 준다).

방금 보신 예제 코드를 한 번만 더 보십시오. BuyTransaction 클래스에서 선언된 createLogString 이라는 (private 멤버) 정적 함수가 사용되고 있는 부분에 대해 잠깐 이야기 하려고요.
이 함수는 기본 클래스에 생성자 쪽으로 넘길 값을 생성하는 용도로 쓰이는 도우미 함수인데, 기본 클래스에 멤버 초기화 리스트가 만수산 드렁칡처럼 달려 있는 경우에 특히 훨씬 편리합니다(그리고 읽기에도 더 편해요).
정적 멤버로 되어 있기 때문에, 생성이 채 끝나지 않은 BuyTransaction 객체의 미초기화된 데이터 멤버를 자칫 실수로 건드릴 위험도 없습니다. 이 대목엔 몇 번 줄을 치셔되 됩니다.
왜냐하면 '미초기화된 데이터 멤버는 정의되지 않은 상태에 있다'라는 사실 때문입니다. 바로 이것 때문에 기본 클래스 부분의 생성과 소멸이 진행되는 동안에 호출되는 가상 함수가 무턱대고 파상 클래스 쪽으로 내려가지
않는 것이랍니다.

이것만은 잊지 말자!
생성자 혹은 소멸자 안에서 가상 함수를 호출하지 마세요. 가상 함수라고 해도, 지금 실행 중인 생성자나 소멸자에 해당되는 클래스의 파상 클래스 쪽으로는 내려가지 않으니까요.
*/