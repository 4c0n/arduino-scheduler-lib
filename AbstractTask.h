#ifndef AbstractTask_h
#define AbstractTask_h

#include "Arduino.h"

#ifdef MYSPECIALDEBUGCONSTANT
#include <AbstractDebug.h>
#endif

class AbstractTask {
   private:
      unsigned long executionTime;

   protected:

#ifdef MYSPECIALDEBUGCONSTANT
      AbstractDebug * debug;
#endif

   public:

#ifdef MYSPECIALDEBUGCONSTANT
      AbstractTask(unsigned long executionTime,  AbstractDebug * debug) {
         this->debug = debug;
#else
      AbstractTask(unsigned long executionTime) {
#endif

         this->executionTime = executionTime;

#ifdef MYSPECIALDEBUGCONSTANT
         String message("AbstractTask::AbstractTask: executionTime: ");
         message.concat(this->executionTime);
         this->debug->info(message);
#endif
      }


      virtual ~AbstractTask() {
      }

      virtual void execute() = 0;


      unsigned long getExecutionTime() {

#ifdef MYSPECIALDEBUGCONSTANT
         String message("AbstractTask::getExecutionTime: executionTime: ");
         message.concat(this->executionTime);
         this->debug->info(message);
#endif

         return this->executionTime;
      }


      void setExecutionTime(unsigned long executionTime) {
         this->executionTime = executionTime;

#ifdef MYSPECIALDEBUGCONSTANT
         String message("AbstractTask::setExecutionTime: executionTime: ");
         message.concat(this->executionTime);
         this->debug->info(message);
#endif

      }
};

#endif
