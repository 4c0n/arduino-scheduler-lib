#include "Arduino.h"
#include "Scheduler.h"

#ifdef MYSPECIALDEBUGCONSTANT
Scheduler::Scheduler(int maxTasks, AbstractDebug * debug) {
	this->debug = debug;
#else
Scheduler::Scheduler(int maxTasks) {
#endif

	this->maxTasks = maxTasks;
	this->tasksScheduled = 0;
	this->queue = new AbstractTask*[maxTasks];

#ifdef MYSPECIALDEBUGCONSTANT
	this->debug->info("Scheduler::Scheduler: Constructed Scheduler:");
	String message ("Scheduler::Scheduler: maxTasks: ");
	message.concat(this->maxTasks);
	this->debug->info(message);
	message = "Scheduler::Scheduler: tasksScheduled: ";
	message.concat(this->tasksScheduled);
	this->debug->info(message);
#endif

}


/**
For now tasks should be scheduled in chromatic order.
So first tasks in front
**/
bool Scheduler::scheduleTask(AbstractTask * task) {
	if(this->tasksScheduled == this->maxTasks) {

#ifdef MYSPECIALDEBUGCONSTANT
		this->debug->error("Scheduler::scheduleTask: Task queue is full!");
#endif

		return false;
	}

	this->queue[this->tasksScheduled] = task;
	this->tasksScheduled++;

#ifdef MYSPECIALDEBUGCONSTANT
	this->debug->info("Scheduler::scheduleTask: Scheduled new task.");
	String message ("Scheduler::scheduleTask: Task scheduled at: ");
	message.concat(task->getExecutionTime());
	this->debug->info(message);
	message = "Scheduler::scheduleTask: tasksScheduled: ";
	message.concat(this->tasksScheduled);
	this->debug->info(message);
#endif

	return true;
}

void Scheduler::executeTasks() {
	if(this->tasksScheduled > 0) {
		unsigned long now = millis();

#ifdef MYSPECIALDEBUGCONSTANT
		String message("Scheduler::executeTasks: now: ");
		message.concat(now);
		this->debug->info(message);
#endif

		if(this->queue[0]) {
			if(this->queue[0]->getExecutionTime() <= now) {
				this->queue[0]->execute();
				this->tasksScheduled--;
				delete this->queue[0];

#ifdef MYSPECIALDEBUGCONSTANT
				message = "Scheduler::executeTasks: Task executed and removed from queue.";
				this->debug->info(message);
#endif

				// would it be more performant to keep two queues and swap between them?
				// probably even more  efficient to make an array queue if not already available
				AbstractTask* * queue = new AbstractTask*[this->maxTasks];
				for(int i = 0; i < this->tasksScheduled; i++) {
					queue[i] = this->queue[i + 1];
				}

				delete this->queue;
				this->queue = queue;
				this->tasksScheduled = tasksScheduled;

#ifdef MYSPECIALDEBUGCONSTANT
				this->debug->info("Scheduler::executeTasks: Replaced queue.");
				String message("Scheduler::executeTasks: tasksScheduled: ");
				message.concat(this->tasksScheduled);
				this->debug->info (message);
#endif

			}
		}
	}
}
