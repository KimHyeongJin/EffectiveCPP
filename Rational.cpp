#include "Rational.h"


template<typename T, typename U> T* make(const U& u)
{
	return new T{ u };//중괄호???, Uniform Initialization(https://modoocode.com/286)
}

int main()
{
	int* pNum = make<int>(2);
	Rational<int> oneHalf(1, 2);		// Rational이 이제 템플릿이란 것만 빼면
									// 이 예제는 항목 24의 것과 똑같습니다.

	//Rational<int> result = oneHalf * 2;// 그런데 에러입니다. 컴파일이 안되요.

	Rational2<int> oneHalf2(1, 2);
	//Rational2<int> result2 = oneHalf2 * 2;// 컴파일은 되지만 링크가 안됨...=_=;
	return 0;
}
/*
컴파일러가 확실히 하는 것은 Rational<T> 타입의
매개변수를 두 개 받아들이는 operator*라는 이름의 함수를 자신이 어떻게든 인스턴스
로 만들긴 해야 한다는 점입니다. 그러나 이 인스턴스화를 제대로 하려면 '대관절 T가
무었인고?'에 대한 수수께끼를 풀어야 합니다. 문제는 바로, 컴파일러 스스로는 이 수
수께끼를 풀 능력이 없다는 거죠.

T의 정체를 파악하기 위해, 컴파일러는 우선 operator* 호출 시에 넘겨진 인자의 모든
타입을 살핍니다. 지금의 경우에는 Rational<int>(oneHalf의 타입) 및 int(2의 타
입)입니다. 컴파일러는 이들을 하나씩 확인해 갑니다.

oneHalf 쪽은 의외로 확인이 쉽습니다. operator*의 첫 번째 매개변수는 Rational
<T> 타입으로 선언되어 있고, 지금 operator*에 넘겨진 첫 번째 매개변수가 마침 또
Rational<int> 타입이기 때문에, T는 int일 수밖에 없습니다.

하지만 애석하게도 두 번째 매개변수 쪽은 타입을 유추해내기가 쉽지 않습니다. 
operator*의 선언을 보면 두 번째 매개변수가 Rational<T> 타입으로 선언되어 있는데, 
지금 operator*에 넘겨진 두 번째 매개변수(2)는 int 타입입니다. 이때 컴파일러는 
어떻게 해야 T의 정체를 알아낼 수 있을까요? Rational<int>에는 explicit로 
선언되지 않은 생성자가 들어 있다는 것을 확인한 독자라면, 혹시 컴파일러가 이 생성자를 
써서 2를 Rational <int>로 변환하고 이를 통해 T가 int라고 유추할 수 있지 않을까 
하고 예상할 것 같습니다만, 컴파일러는 그렇게 동작하지 못합니다. 

그 이유는, (잘 알아두세요) 템플릿 인자 추론(template argument deduction) 
과정에서는 암시적 타입 변환이 고려 되지 않기 때문입니다. 절대로 안됩니다.

이런 타입 변환은 함수 호출이 진행될 때 쓰이는 것은 맞습니다. 그렇죠. 그러나 
여러분이 함수를 호출할 수 있으려면 어떤 함수가 있는지를 여러분이 미리 알고 있어야 
합니다. 게다가 호출되는 상황에 맞는 함수 템플릿에 넣어 줄 매개변수 타입을 추론하는 
일도(함수를 인스턴스화해야 하니 말이죠) 여러분이 해야 합니다.

다시 말씀드리지만 템플릿 인자 추론이 진행되는 동안에는
생성자 호출을 통한 암시적 타입 변환 자체가 고려되지 않습니다.
*/