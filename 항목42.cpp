//항목42_typename의두가지의미를제대로파악하자.cpp
#include <iostream>
#include <vector>

/*
<class T>와 <typename T>는 동일하다.

코드 안에 중첩 이름이 있으면 골치 아픈 일이 생길 수 있습니다. 바로 컴파일러가 구문분석을 할 때 애로사항이 활짝 꽃핀다는 겁니다.

구문분석기는 템플릿 안에서 중첩 의존 이름을 만나면 프로그래머가 타입이라고 알려주지 않는 한 그 이름이 타입이 아니라고 가정한다.

template< typename C >
void print2nd( const C& container )
{
	if( container.size() >=2 ){
		C::const_iterator iter( container.begin() );//이 이름은 타입이 아닌것으로 가정합니다.
		...


template< typename C >
void print2nd( const C& container )
{
	if( container.size() >=2 ){
		typename C::const_iterator iter( container.begin() );//명시적으로 타입임을 구문분석기에 알려준다.
		...

typename 키워드는 중첩 의존 이름만 식별하는 데 써야 합니다.

template< typename C >				//typename 쓸 수 있음("class"와 같은 의미)
void f( const C& container,			//typename 쓰면 안됨(즉, 템플릿 매개변수에 의존적인 어떤 것도 C를 품고 있지 않습니다.)
		typename C::iteator iter );	//typename 꼭 써야함
		
template< typename T >
class Derived: public Base<T>::Nested{			//상속되는 기본 클래스 리스트:typename 쓰면 안됨
public:
	explicit Derived(int x):Base<T>::Nested(x)	//멤버 초기화 리스트에 있는 기본 클래스 식별자:typename 쓰면 안됨
	{
		typename Base<T>::Nested temp;			//중첩 의존 타입 이름이며 기본 클래스 리스트에도 없고 멤버 초기화 리스트의 기본 클래스 식별자도 아님:typename 필요
		...
	}
	...
}

현업에서 보게될 대표적인 사례
template< typename IterT >
void workWithIterator( IterT iter )
{
	typename std::iterator_traits<IterT>::value_type temp(*iter);//IterT 타입의 객체로 가리키는 대상의 타입, 정상
	...
}

template< typename IterT >
void workWithIterator( IterT iter )
{
	typedef typename std::iterator_traits<IterT>::value_type value_type;//typedef 이름을 만들 때는 그 멤버 이름과 똑같이 짓는 것이 관례,정상
	value_type temp(*iter);
	...
}


*/

template< typename T >
void Func( const T& container )
{
	T::const_iterator iter( container.begin() );//타입이 아닌 결로 가정된다. 템플릿 매개변수 T 클래스의 정적 데이터 멤버 변수 const_iterator
	//typename T::const_iterator iter( container.begin() );
}

template< typename T >
class TestClass
{
public:
	void Draw( void ){ std::cout<<sizeof(p)<<" byte 용량을 가진 클래스"<<std::endl;}
private:
	T *p;
public:
	//T::iterator iter;//'T::iterator': 종속 이름이 형식이 아닙니다.
	typename T::iterator iter;
};
//
// typename 은 템플릿 내부에서 사용하면서 컴파일러에게 템플릿 내부에서 "이건 타입이야" 라고 알릴 필요가 있을때 써준다.
// T 처럼 타입을 인자로 받아 그것을 타입으로 쓰기 때문에 T를 의존 이름(dependent name) 이라 한다.
// 의존 이름속에서 또 다시 다른 이름이 정의된 경우 그녀석은 중첩 의존 타입 이름(nested dependent type name)이라 불린다.
// 바로 템플릿 내부에서 중첩 의존 타입 이름이 있을 경우, 그녀석도 타입인것을 인지 하지 못하는 사태가 발생 할 수 있다.
// int같은 것들은 비의존 이름(non - dependent name)이라고 불린다.

//typename 을 쓸때, template 내부여도 못쓰는 경우가 두가지 있다
//중텁 의존 타입이름이 기본 클래스의 리스트에 있거나, 멤버 초기화 리스트 내의 기본 클래스 식별자로 있을경우
// typename을 붙여 주면 안된다는 것이다.
template< typename T >
class Base
{
public:
	Base(){}
	~Base(){}
private:
	T m_p;
};

template< typename T >
class Derived : public Base<T>//상속되는 기본 클래스의 리스트:typename 쓰면 안됨
{
public:
	Derived():Base<T>()//멤버 초기화 리스트에 있는 클래스 식별자:typename 쓰면 안됨
	{
	}
	void Draw( void ){ std::cout<<sizeof(p)<<" byte 용량을 가진 클래스"<<std::endl;}
private:
	T *p;
public:
	//T::iterator iter;//'T::iterator': 종속 이름이 형식이 아닙니다.
	typename T::iterator iter;
};

int main(void)
{
	//typename int a;//에러

	//std::vector<int> vec;
	//vec.push_back(999);
	//Func(vec);

	Derived< std::vector<int> > test;

	test.Draw();

	Derived< std::vector<int> > test2;

	test2.Draw();

	return 0;
}