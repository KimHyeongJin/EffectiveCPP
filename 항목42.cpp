//�׸�42_typename�ǵΰ����ǹ̸�������ľ�����.cpp
#include <iostream>
#include <vector>

/*
<class T>�� <typename T>�� �����ϴ�.

�ڵ� �ȿ� ��ø �̸��� ������ ��ġ ���� ���� ���� �� �ֽ��ϴ�. �ٷ� �����Ϸ��� �����м��� �� �� �ַλ����� Ȱ¦ ���ɴٴ� �̴ϴ�.

�����м���� ���ø� �ȿ��� ��ø ���� �̸��� ������ ���α׷��Ӱ� Ÿ���̶�� �˷����� �ʴ� �� �� �̸��� Ÿ���� �ƴ϶�� �����Ѵ�.

template< typename C >
void print2nd( const C& container )
{
	if( container.size() >=2 ){
		C::const_iterator iter( container.begin() );//�� �̸��� Ÿ���� �ƴѰ����� �����մϴ�.
		...


template< typename C >
void print2nd( const C& container )
{
	if( container.size() >=2 ){
		typename C::const_iterator iter( container.begin() );//��������� Ÿ������ �����м��⿡ �˷��ش�.
		...

typename Ű����� ��ø ���� �̸��� �ĺ��ϴ� �� ��� �մϴ�.

template< typename C >				//typename �� �� ����("class"�� ���� �ǹ�)
void f( const C& container,			//typename ���� �ȵ�(��, ���ø� �Ű������� �������� � �͵� C�� ǰ�� ���� �ʽ��ϴ�.)
		typename C::iteator iter );	//typename �� �����
		
template< typename T >
class Derived: public Base<T>::Nested{			//��ӵǴ� �⺻ Ŭ���� ����Ʈ:typename ���� �ȵ�
public:
	explicit Derived(int x):Base<T>::Nested(x)	//��� �ʱ�ȭ ����Ʈ�� �ִ� �⺻ Ŭ���� �ĺ���:typename ���� �ȵ�
	{
		typename Base<T>::Nested temp;			//��ø ���� Ÿ�� �̸��̸� �⺻ Ŭ���� ����Ʈ���� ���� ��� �ʱ�ȭ ����Ʈ�� �⺻ Ŭ���� �ĺ��ڵ� �ƴ�:typename �ʿ�
		...
	}
	...
}

�������� ���Ե� ��ǥ���� ���
template< typename IterT >
void workWithIterator( IterT iter )
{
	typename std::iterator_traits<IterT>::value_type temp(*iter);//IterT Ÿ���� ��ü�� ����Ű�� ����� Ÿ��, ����
	...
}

template< typename IterT >
void workWithIterator( IterT iter )
{
	typedef typename std::iterator_traits<IterT>::value_type value_type;//typedef �̸��� ���� ���� �� ��� �̸��� �Ȱ��� ���� ���� ����,����
	value_type temp(*iter);
	...
}


*/

template< typename T >
void Func( const T& container )
{
	T::const_iterator iter( container.begin() );//Ÿ���� �ƴ� ��� �����ȴ�. ���ø� �Ű����� T Ŭ������ ���� ������ ��� ���� const_iterator
	//typename T::const_iterator iter( container.begin() );
}

template< typename T >
class TestClass
{
public:
	void Draw( void ){ std::cout<<sizeof(p)<<" byte �뷮�� ���� Ŭ����"<<std::endl;}
private:
	T *p;
public:
	//T::iterator iter;//'T::iterator': ���� �̸��� ������ �ƴմϴ�.
	typename T::iterator iter;
};
//
// typename �� ���ø� ���ο��� ����ϸ鼭 �����Ϸ����� ���ø� ���ο��� "�̰� Ÿ���̾�" ��� �˸� �ʿ䰡 ������ ���ش�.
// T ó�� Ÿ���� ���ڷ� �޾� �װ��� Ÿ������ ���� ������ T�� ���� �̸�(dependent name) �̶� �Ѵ�.
// ���� �̸��ӿ��� �� �ٽ� �ٸ� �̸��� ���ǵ� ��� �׳༮�� ��ø ���� Ÿ�� �̸�(nested dependent type name)�̶� �Ҹ���.
// �ٷ� ���ø� ���ο��� ��ø ���� Ÿ�� �̸��� ���� ���, �׳༮�� Ÿ���ΰ��� ���� ���� ���ϴ� ���°� �߻� �� �� �ִ�.
// int���� �͵��� ������ �̸�(non - dependent name)�̶�� �Ҹ���.

//typename �� ����, template ���ο��� ������ ��찡 �ΰ��� �ִ�
//���� ���� Ÿ���̸��� �⺻ Ŭ������ ����Ʈ�� �ְų�, ��� �ʱ�ȭ ����Ʈ ���� �⺻ Ŭ���� �ĺ��ڷ� �������
// typename�� �ٿ� �ָ� �ȵȴٴ� ���̴�.
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
class Derived : public Base<T>//��ӵǴ� �⺻ Ŭ������ ����Ʈ:typename ���� �ȵ�
{
public:
	Derived():Base<T>()//��� �ʱ�ȭ ����Ʈ�� �ִ� Ŭ���� �ĺ���:typename ���� �ȵ�
	{
	}
	void Draw( void ){ std::cout<<sizeof(p)<<" byte �뷮�� ���� Ŭ����"<<std::endl;}
private:
	T *p;
public:
	//T::iterator iter;//'T::iterator': ���� �̸��� ������ �ƴմϴ�.
	typename T::iterator iter;
};

int main(void)
{
	//typename int a;//����

	//std::vector<int> vec;
	//vec.push_back(999);
	//Func(vec);

	Derived< std::vector<int> > test;

	test.Draw();

	Derived< std::vector<int> > test2;

	test2.Draw();

	return 0;
}