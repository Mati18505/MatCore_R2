#pragma once

namespace MatCore {
	class FileDialog {
	public:
		//Zwracaj� puste stringi je�li anulowane
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}