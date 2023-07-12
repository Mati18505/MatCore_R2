#pragma once

namespace MatCore {
	class FileDialog {
	public:
		//Zwracaj¹ puste stringi jeœli anulowane
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}