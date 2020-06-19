/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#include "AsyncTimerLib.h"

AsyncTimer::AsyncTimer(unsigned long microsInterval) : AsyncTimer(microsInterval, false, nullptr)
{
}

AsyncTimer::AsyncTimer(unsigned long microsInterval, AsyncTimerCallback onFinish) : AsyncTimer(microsInterval, false, onFinish)
{

}

AsyncTimer::AsyncTimer(unsigned long microsInterval, bool autoReset) : AsyncTimer(microsInterval, false, nullptr)
{
}

AsyncTimer::AsyncTimer(unsigned long microsInterval, bool autoReset, AsyncTimerCallback onFinish)
{
	Interval = microsInterval;
	AutoReset = autoReset;
	OnFinish = onFinish;
}

void AsyncTimer::Start()
{
	Reset();
	_isActive = true;
}

void AsyncTimer::Reset()
{
	_startTime = micros();
}

void AsyncTimer::Stop()
{
	_isActive = false;
}

bool AsyncTimer::Update()
{
	if (_isActive == false) return false;

	if (static_cast<unsigned long>(micros() - _startTime) >= Interval)
	{
		if (OnFinish != nullptr) OnFinish();

		_isExpired = !AutoReset;
		_isActive = AutoReset;
		Reset();
	}
	return _isExpired;
}

void AsyncTimer::Update(AsyncTimer &next)
{
	if (Update())
	{
		_isExpired = false;
		next.Start();
	}
}

void AsyncTimer::SetIntervalMillis(unsigned long interval)
{
	Interval = 1000 * interval;
}

void AsyncTimer::SetIntervalMicros(unsigned long interval)
{
	Interval = interval;
}

unsigned long AsyncTimer::GetStartTime()
{
	return _startTime;
}

unsigned long AsyncTimer::GetElapsedTime()
{
	return micros() - _startTime;
}

unsigned long AsyncTimer::GetRemainingTime()
{
	return Interval - micros() + _startTime;
}

bool AsyncTimer::IsActive() const
{
	return _isActive;
}

bool AsyncTimer::IsExpired() const
{
	return _isExpired;
}

void AsyncTimer::Every(unsigned long millisInterval, AsyncTimerCallback onFinish)
{
	this->SetIntervalMillis(millisInterval);
	this->OnFinish = onFinish;
	this->AutoReset = true;
	this->Start();
}

void AsyncTimer::In(unsigned long millisInterval, AsyncTimerCallback onFinish)
{
	this->SetIntervalMillis(millisInterval);
	this->AutoReset = false;
	this->OnFinish = onFinish;
	this->Start();
}
