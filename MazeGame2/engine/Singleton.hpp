#pragma once

template<typename T>
class Singleton {

protected:

	static T* instance;

	Singleton() {};

public: 

	Singleton& operator=(Singleton&) = delete;
	Singleton(const Singleton&) = delete;

	static T* GetInstance() {
		if (!instance) {
			instance = new T;
		}
		return instance;
	}

	virtual ~Singleton() { delete instance; }
};

template<typename T>
T* Singleton<T>::instance = nullptr;