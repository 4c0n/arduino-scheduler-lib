#ifndef Scheduler_h
#define Scheduler_h

//#define MYSPECIALDEBUGCONSTANT

#include "Arduino.h"
#include "AbstractTask.h"
#include <ArrayQueue.h>

#ifdef MYSPECIALDEBUGCONSTANT
#include <AbstractDebug.h>
#endif

class Scheduler {
	private:
		ArrayQueue<AbstractTask*> * queue;

#ifdef MYSPECIALDEBUGCONSTANT
		AbstractDebug * debug;
#endif

	public:
		Scheduler();

#ifdef MYSPECIALDEBUGCONSTANT
		Scheduler(unsigned int maxTasks, AbstractDebug * debug);
#else
		Scheduler(unsigned int maxTasks);
#endif

		unsigned int getMaxTasks();
		unsigned int getNumTasksScheduled();
		bool scheduleTask(AbstractTask * task);
		void executeTask();
};

#endif
