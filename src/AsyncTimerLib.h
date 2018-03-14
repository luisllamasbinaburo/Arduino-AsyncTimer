/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#ifndef _ASYNCTIMERLIB_h
#define _ASYNCTIMERLIB_h
 
#include "Arduino.h"

typedef void(*AsyncTimerCallback)();

class AsyncTimer
{
 public:
	AsyncTimer(unsigned long microsInterval);
	AsyncTimer(unsigned long microsInterval, AsyncTimerCallback OnFinish);

	AsyncTimer(unsigned long microsInterval, bool autoReset);
	AsyncTimer(unsigned long microsInterval, bool autoReset, AsyncTimerCallback OnFinish);

	void Start();
	void Reset();
	void Stop();
	bool Update();

	void SetIntervalMillis(unsigned long interval);
	void SetIntervalMicros(unsigned long interval);
	
	unsigned long GetStartTime();
	unsigned long GetElapsedTime();
	unsigned long GetRemainingTime();

	bool IsActive() const;
	bool IsExpired() const;
	
	unsigned long Interval;
	bool AutoReset;
	
	AsyncTimerCallback OnFinish;

private:
	bool _isActive;
	bool _isExpired;
	unsigned long _startTime;
};
#endif

