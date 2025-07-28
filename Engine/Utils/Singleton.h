#pragma once
template <typename T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}

	Singleton(const Singleton&) = delete;
	void operator=(const Singleton&) = delete;

protected:
	Singleton() = default;
	virtual ~Singleton() = default;
};

/// 싱글톤 상속 받을 때 작성 해야 할 것
/// 생성자와 소멸자는 private으로 지정 ( 암묵적으로 public되는걸 막기 위함 )
/// public에서 friend class Sington<T> 작성 -> ???