/**
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */

#ifndef OPENDNP3_MASTERSCHEDULER_H
#define OPENDNP3_MASTERSCHEDULER_H

#include <openpal/executor/IExecutor.h>
#include <openpal/container/Settable.h>
#include <openpal/container/ManagedPtr.h>

#include "opendnp3/master/UserPollTask.h"
#include "opendnp3/master/IMasterTask.h"
#include "opendnp3/master/IScheduleCallback.h"

#include <vector>
#include <functional>

namespace opendnp3
{

class MasterScheduler
{		

public:	

	MasterScheduler(openpal::IExecutor& executor, IScheduleCallback& callback);	
	
	// ---------- other public functions ----------------

	/*
	* Add a task to the scheduler
	*/
	void Schedule(openpal::ManagedPtr<IMasterTask> pTask);

	/**
	* @return Task to start or undefined pointer if no task to start
	*/
	openpal::ManagedPtr<IMasterTask> Start();

	/*
	* Startup
	*/
	void OnLowerLayerUp();

	/**
	* Cleanup all existing tasks & cancel any timers
	*/
	void OnLowerLayerDown();	

private:

	static bool Enabled(const IMasterTask& task) { return !task.ExpirationTime().IsMax(); }

	static int Compare(const openpal::MonotonicTimestamp& now, const IMasterTask& lhs, const IMasterTask& rhs);

	std::vector<openpal::ManagedPtr<IMasterTask>>::iterator GetNextTask(const openpal::MonotonicTimestamp& now);

	openpal::ManagedPtr<IMasterTask> PopNextTask();
	
	void StartOrRestartTimer(const openpal::MonotonicTimestamp& expiration);

	void StartTimer(const openpal::TimeDuration& timeout);

	void StartTimer(const openpal::MonotonicTimestamp& expiration);

	void OnTimerExpiration();	

	bool CancelScheduleTimer();		

	// ----------- static configuration ---------

	openpal::IExecutor* pExecutor;
	IScheduleCallback* pCallback;

	// ----------- dynamic state -----------

	bool isOnline;	
	openpal::ITimer* pTimer;	
	std::vector<openpal::ManagedPtr<IMasterTask>> tasks;
};

}



#endif
