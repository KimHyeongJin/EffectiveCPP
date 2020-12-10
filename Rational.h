#pragma once
template<typename T>
class Rational
{
public:
	Rational(const T& numerator = 0,	// �Ű������� �����ڷ� ���޵Ǵ� ������
		const T& denominator = 1) {};	// �׸� 20�� ���� ���ɴϴ�.
	const T numerator() const;		// ��ȯ�� ������ ������ ���� ���� ������
	const T denominator() const;	// ������ �׸� 28�� ���� �������.
	//...							// �̵� �Լ��� const�� ������ �׸� 3����...
};
/*
*	���ø� ���� �߷�(template argument deduction) ���������� �Ͻ��� Ÿ��
	��ȯ�� ������� �ʴ´�. ����� �ȵ˴ϴ�.
*	���ø� ���� �߷��� �Լ� ���ø����� ����Ǵ� �����Դϴ�.
*/


// �������� ������ ��ũ������ �߻��ϴ� ����
template<typename T>
class Rational2
{
public:
	Rational2(const T& numerator = 0,	// �Ű������� �����ڷ� ���޵Ǵ� ������
		const T& denominator = 1) {};	// �׸� 20�� ���� ���ɴϴ�.
	const T numerator() const;		// ��ȯ�� ������ ������ ���� ���� ������
	const T denominator() const;	// ������ �׸� 28�� ���� �������.
		// operator* �Լ��� �����մϴ�(�ڼ��� ������ �Ʒ��� ���Ϳ�)
	friend const Rational2 operator*(const Rational2& lhs,
		const Rational2& rhs);
};

// operator* �Լ��� �����մϴ�.
template<typename T>
const Rational2<T> operator*(const Rational2<T>& lhs,
	const Rational2<T>& rhs) {};