#pragma once
#include <vector>

namespace verifier {
	class Verifier {
	private:
		std::vector<int> vect;
		int length;
		int sum;
	public:
		Verifier(int* array, int length);
		bool verify();
		void showArrayValue();
	};

}
