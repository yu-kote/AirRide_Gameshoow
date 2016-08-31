#include "IncrementTimeUI.h"

void IncrementTimeUI::timeUpdate()
{
	if (start) {
		flame++;
		if (flame == 60) {
			flame = 0;
			seconds++;
		}
		if (seconds == 60) {
			seconds = 0;
			minutes++;
		}
	}
}
