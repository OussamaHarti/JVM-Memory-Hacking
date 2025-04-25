#include "Utils.h"

#include <windows.h>
#include <iostream>
#include <random>
#include <thread>
#include <psapi.h>

namespace Utils {
	void Errors::manageError(const std::string& error) {
		MessageBoxA(NULL, error.c_str(), "Error", MB_OK | MB_ICONERROR);
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		exit(0);
	};

	double Math::generateRandomNumber(const double& min, const double& max) {
		if (min == max || min > max) return max;

		std::random_device random;
		std::mt19937 gen(random());
		std::uniform_real_distribution<double> dist(min, max);
		return dist(gen);
	};

	std::string Minecraft::getMinecraftVersion(const std::string& input, float* number) {
		size_t pos = input.find("1.");
		if (pos != std::string::npos) {
			size_t end = pos + 2; // start from the position after "1."
			while (end < input.size() && (isdigit(input[end]) || input[end] == '.')) {
				++end;
			}
			if (number != nullptr) *number = atof(input.substr(pos + 2, end - (pos + 2)).c_str());

			return input.substr(pos, end - pos);
		}
		return std::string{};
	};
}