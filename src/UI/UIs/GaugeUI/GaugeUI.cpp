#include "GaugeUI.h"

void GaugeUI::changeGauge(float value,float max)
{
	if (value >= max) {
		gauge_max = true;
	}
	else{
		gauge_max = false;
	}
	gauge_size.x = value / max * gauge_max_x;
}
