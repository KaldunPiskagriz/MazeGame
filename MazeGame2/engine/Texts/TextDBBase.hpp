#pragma once
#include <unordered_map>
#include <string>

class TextDBBase {

protected:

	std::unordered_map<std::string, std::wstring> base;

public:

	std::wstring Get(std::string str) {
		if (base.contains(str))
			return base[str];
		else
			return L"text not found";
	}

	bool Contains(const std::string& arg) {
		return base.contains(arg);
	}

};