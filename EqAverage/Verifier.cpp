#include "Verifier.h"
#include <unordered_set>

namespace verifier {
	Verifier::Verifier(int *a, int length) {
		int s = 0;
		for (int i = 0; i < length; i++) {
			s += a[i];
			this->vect.push_back(a[i]);
		}
		this->sum = s;
		this->length = length;

	}
	void Verifier::showArrayValue() {
		for (int i = 0; i < length; i++) {
			printf("%d ", vect[i]);
		}
	}


	bool Verifier::verify() {
		std::vector<int> indexes;

		for (int i = 1; i <= length / 2; i++) {
			if ((sum * i )% length == 0) {
				indexes.push_back(i);
			}
		}

		if (indexes.empty()) {
			return  false;
		}
		else {
			std::vector<std::unordered_set<int>> sums(length / 2 + 1);
			sums[0].insert(0);
			for (int i = 0; i < length; i++) {
				for (int j = (length / 2); j >= 1; j--)
				{
					for (int k : sums[j - 1]) {
						sums[j].insert(vect[i] + k);
					}
				}
			}

			float array_average = (float)sum / length;
			for (int i:indexes) {
				for (int j : sums[i]) {
					float  subsetAverage = (float)j / i;
					if (subsetAverage == array_average ) {
						return true;
					}
				}
			}
			return false;
		}

	}
}




