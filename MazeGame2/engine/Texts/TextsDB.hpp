#pragma once
#include "../Singleton.hpp"
#include "TextDBBase.hpp"
#include "../Logger.hpp"
#include <unordered_map>
#include <string>

class TextsDB : public Singleton<TextsDB>{

	std::string lang;
	std::unordered_map<std::string, TextDBBase*> base;

public:
	
	TextsDB();
	void AddLanguage(std::string langName, TextDBBase* baseptr);
	void ChangeLanguage(std::string ln);
	std::wstring GetText(std::string str);
	bool Contains(const std::string& arg);
	~TextsDB();

};