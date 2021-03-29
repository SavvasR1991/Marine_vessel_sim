#pragma once
#ifndef JOBS_H
#define JOBS_H

/*************************** VESSEL JOBS INTERFACE *****************************/
class Jobs {	//Jobs
	private:
		virtual void reset() = 0;
		virtual void patroling() = 0;
		virtual void vanguared() = 0;
		virtual void shadowing() = 0;
		virtual void lock() = 0;
};

#endif
