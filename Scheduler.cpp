#include "Arduino.h"
#include "Scheduler.h"

#ifdef MYSPECIALDEBUGCONSTANT
Scheduler::Scheduler(int maxTasks, AbstractDebug * debug) {
	this->debug = debug;
#else
Scheduler::Scheduler(int maxTasks) {
#endif

	this->queue = new ArrayQueue<AbstractTask*>(maxTasks);

#ifdef MYSPECIALDEBUGCONSTANT
	this->debug->info("Scheduler::Scheduler: Constructed Scheduler:");
	String message ("Scheduler::Scheduler: maxTasks: ");
	message.concat(maxTasks);
	this->debug->info(message);
	message = "Scheduler::Scheduler: tasksScheduled: ";
	message.concat(this->queue->getSize());
	this->debug->info(message);
#endif

}


/**
For now tasks should be scheduled in chromatic order.
So first tasks in front
**/
bool Scheduler::scheduleTask(AbstractTask * task) {
	bool retVal = this->queue->push(task);

	if(!retVal) {

#ifdef MYSPECIALDEBUGCONSTANT
		this->debug->error("Scheduler::scheduleTask: Task queue is full!");
#endif

		return false;
	}

#ifdef MYSPECIALDEBUGCONSTANT
	this->debug->info("Scheduler::scheduleTask: Scheduled new task.");
	String message ("Scheduler::scheduleTask: Task scheduled at: ");
	message.concat(task->getExecutionTime());
	this->debug->info(message);
	message = "Scheduler::scheduleTask: tasksScheduled: ";
	message.concat(this->queue->getSize());
	this->debug->info(message);
#endif

	return true;
}

void Scheduler::executeTask() {
	if(this->queue->getSize() > 0) {
		unsigned long now = millis();

		if(this->queue->peek()->getExecutionTime() <= now) {
			AbstractTask* task = queue->pop();
			task->execute();
			delete task;

#ifdef MYSPECIALDEBUGCONSTANT
			String message("Scheduler::executeTask: now: ");
			message.concat(now);
			this->debug->info(message);
#endif
		}
	}
}
