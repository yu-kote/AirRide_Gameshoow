#include "DecrementTimeUI.h"

void DecrementTimeUI::timeUpdate()
{
	if (flame <= 0 &&
		seconds <= 0 &&
		minutes <= 0) {
		time_zero = true;
	}else if (start) {
		time_zero = false;
		flame--;
		if (flame <= 0) {
			flame = 60;
			seconds--;
		}
		if (seconds <= 0) {
			seconds = 60;
			minutes--;
		}
	}
}