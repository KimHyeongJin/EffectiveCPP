#pragma once
template<typename T>
class Rational
{
public:
	Rational(const T& numerator = 0,	// 매개변수가 참조자로 전달되는 이유는
		const T& denominator = 1) {};	// 항목 20을 보면 나옵니다.
	const T numerator() const;		// 반환값 전달이 여전히 값에 의한 전달인
	const T denominator() const;	// 이유는 항목 28을 보면 나오고요.
	//...							// 이들 함수가 const인 이유는 항목 3에서...
};
/*
*	템플릿 인자 추론(template argument deduction) 과정에서는 암시적 타입
	변환이 고려되지 않는다. 절대로 안됩니다.
*	템플릿 인자 추론은 함수 템플릿에만 적용되는 과정입니다.
*/


// 컴파일은 되지만 링크에러가 발생하는 예제
template<typename T>
class Rational2
{
public:
	Rational2(const T& numerator = 0,	// 매개변수가 참조자로 전달되는 이유는
		const T& denominator = 1) {};	// 항목 20을 보면 나옵니다.
	const T numerator() const;		// 반환값 전달이 여전히 값에 의한 전달인
	const T denominator() const;	// 이유는 항목 28을 보면 나오고요.
		// operator* 함수를 선언합니다(자세한 내용은 아래에 나와요)
	friend const Rational2 operator*(const Rational2& lhs,
		const Rational2& rhs);
};

// operator* 함수를 정의합니다.
template<typename T>
const Rational2<T> operator*(const Rational2<T>& lhs,
	const Rational2<T>& rhs) {};