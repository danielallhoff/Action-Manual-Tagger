#include "MyQSlider.h"

bool MyQSlider::eventFilter(QObject *obj, QEvent *event) {
	if (event->type() == QEvent::Wheel && obj == this) {
		return true;

	}
	return false;
}