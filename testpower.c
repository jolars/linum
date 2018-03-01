#include <stdio.h>
#include "libpower.h"

// https://stackoverflow.com/a/7898516/312332
void clearInputBuffer() {
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

// OBS: kräver rätt format på input

void test_r() {
	float volt;
	float resistance;
	
	printf("\nVolt: ");
	scanf("%f", &volt);
	clearInputBuffer();

	printf("Resistance: ");
	scanf("%f", &resistance);
	clearInputBuffer();

	printf("\nPower: %lf\n\n", calc_power_r(volt, resistance));
}

void test_i() {
	float volt;
	float current;
	
	printf("\nVolt: ");
	scanf("%f", &volt);
	clearInputBuffer();

	printf("Current: ");
	scanf("%f", &current);
	clearInputBuffer();

	printf("\nPower: %lf\n\n", calc_power_i(volt, current));
}

int main(int argc, char **argv) {
	for (;;) {
		int choice;
		printf("Choose:\n\n1) Test calc_power_r\n2) Test calc_power_i\n3) Quit\n\n(1/2/3): ");
		scanf("%d", &choice);
		clearInputBuffer();

		if (choice == 1) {
			test_r();
		} else if (choice == 2) {
			test_i();
		} else if (choice == 3) {
			break;
		} else {
			puts("\nInvalid option\n\n");
		}


	}
	return 0;
}

