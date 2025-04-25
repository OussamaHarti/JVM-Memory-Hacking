#pragma once
#include <Windows.h>
#include <string>
#include <vector>

namespace Utils {

	namespace Errors {
		void manageError(const std::string& error);
	}

	namespace Math {
		double generateRandomNumber(const double& min, const double& max);
	}

	namespace Minecraft {
		std::string getMinecraftVersion(const std::string& input, float* number);
	}
}