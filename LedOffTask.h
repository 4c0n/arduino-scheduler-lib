#ifndef LedOffTask_h
#define LedOffTask_h

#include "Arduino.h"
#include "AbstractTask.h"

class LedOffTask : public AbstractTask {
	private:
		byte pin = 13;		

	public:
		LedOffTask() : AbstractTask(13) {
		}

		LedOffTask(byte pin) : AbstractTask(pin) {
			this->pin = pin;
		}

		void execute() {
			digitalWrite(this->pin, LOW);
		}
};

#endif
