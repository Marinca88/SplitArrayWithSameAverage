#pragma once

#include <numeric>
#include <stdio.h>;
#include <stdlib.h>
#include "Verifier.h"


namespace testLibrary {
	int* create_array(int *l) {
		int first_partition_length = rand() % 15 + 1;
		int* first_partition = (int*)malloc((first_partition_length + 1) * sizeof(int));
		for (int i = 0; i < first_partition_length; i++) {
			first_partition[i] = rand() % 10001;
		}
		int sm = 0;
		int first_partition_sum = std::accumulate(first_partition, first_partition + first_partition_length, sm);
		int  second_partition_length = rand() % 15 + 1;
		while ((first_partition_sum * second_partition_length) % first_partition_length != 0) {
			second_partition_length--;
		}
		int* second_partition = (int*)malloc((second_partition_length + 1) * sizeof(int));
		for (int i = 0; i < second_partition_length; i++) {
			second_partition[i] = rand() % 10001;
		}
		sm = 0;
		int second_partition_sum = std::accumulate(second_partition, second_partition + second_partition_length, sm);
		if ((first_partition_sum * second_partition_length) / first_partition_length < second_partition_sum) {
			int   diff = second_partition_sum - ((first_partition_sum * second_partition_length) / first_partition_length);
			int i = 0;
			while (diff != 0) {
				if (second_partition[i] - diff >= 0) {
					second_partition[i] -= diff;
					diff = 0;
				}
				else {
					diff -= second_partition[i];
					second_partition[i] += 0;
					i++;
				}
			}
		}
		if ((first_partition_sum * second_partition_length) / first_partition_length > second_partition_sum) {
			int   diff = ((first_partition_sum * second_partition_length) / first_partition_length) - second_partition_sum;
			int i = 0;
			while (diff != 0) {
				if (second_partition[i] + diff <= 10000) {
					second_partition[i] += diff;
					diff = 0;
				}
				else {
					int until_max = 10000 - second_partition[i];
					second_partition[i] += until_max;
					diff -= until_max;
					i++;
				}
			}
		}
		int array_length = first_partition_length + second_partition_length;
		int* array = (int*)malloc(sizeof(int) * (array_length + 1));
		for (int i = 0; i < first_partition_length; i++) {
			array[i] = first_partition[i];
		}
		for (int i = 0; i < second_partition_length; i++) {
			array[first_partition_length + i] = second_partition[i];
		}
		free(first_partition);
		free(second_partition);
		*l = array_length;
		return  array;
	}

	void test() {
		int length;
		printf("OK ARRAY\n");
		int* array = create_array(&length);
		verifier::Verifier v(array,length);
		bool ver= v.verify();
		if (ver == true) {
			printf("TEST PASSED:\nEXPECTED VALUE 1 : RECIVED VALUE %d\n", ver);
		}
		else {
			printf("TEST  FAILED:\nEXPECTED VALUE 1 : RECIVED VALUE %d\n", ver);
		}
		printf("NOT OK ARRAY\n");
		for (int i = 0; i < length-1; i++) {
			array[i] = 0;
		}
		verifier::Verifier v1(array, length);
		bool ver1 = v1.verify();
		if (ver1 == false) {
			printf("TEST PASSED:\nEXPECTED VALUE 0 : RECIVED VALUE %d\n", ver1);
		}
		else {
			printf("TEST  FAILED:\nEXPECTED VALUE 0 : RECIVED VALUE %d\n", ver1);
		}

	}
}