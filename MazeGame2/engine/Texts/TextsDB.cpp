#include "TextsDB.hpp"

TextsDB::TextsDB() {
	base.clear();
}

void TextsDB::AddLanguage(std::string langName, TextDBBase* baseptr) {
	base[langName] = baseptr;
	Logger* engineLogger = Logger::GetInstance();
	engineLogger->PrintMessage("Created language: " + langName);
}

void TextsDB::ChangeLanguage(std::string ln) {
	if (lang != ln) { 
		if (base.contains(ln)) {
			lang = ln;
		} else {

		}
	}
}

std::wstring TextsDB::GetText(std::string str) {
	return base[lang]->Get(str);
}

bool TextsDB::Contains(const std::string& arg) {
	return base[lang]->Contains(arg);
}

TextsDB::~TextsDB() {
	for (auto& i : base) {
		delete i.second;
	}
}

