#ifndef LedOffTask_h
#define LedOffTask_h

#include "Arduino.h"
#include "AbstractTask.h"

class LedOffTask : public AbstractTask {
	private:
		byte pin = 13;		

	public:
		LedOffTask(unsigned long executionTime) : AbstractTask(executionTime) {
		}

		LedOffTask(unsigned long executionTime, byte pin) : AbstractTask(executionTime) {
			this->pin = pin;
		}

		virtual ~LedOffTask() {
		}

		void execute() {
			digitalWrite(this->pin, LOW);
		}
};

#endif
