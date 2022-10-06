#pragma once

#include <ext.h>

enum
{
	VALUE_INT32, VALUE_FLOAT32
};

enum
{
	OP_ADD, OP_SUB,
	OP_MUL, OP_DIV,
};

union TweenValue
{
	int32 INT32;
	float FLOAT32;
};

struct TweenJob
{
	// value to interpolate
	void* value;
	// amount to change each update
	TweenValue modifier;
	// data type
	int8 value_t;
	
	// add, subtract, multiply or divide
	int8 operation;
	
	// flag to be set on completion
	int8* completion = 0;
	
	// number of updates left
	// until completion of job
	int32 timer = 0;
};

typedef Array<TweenJob> Tween;

void NewJob(Tween& tween, void* value, void* modifier, int8 datatype, int8 operation, int duration, int8* completion = 0)
{
	TweenJob job;
	
	job.value = value;
	job.value_t = datatype;
	
	if (datatype == VALUE_INT32)
		job.modifier.INT32 = * (int32*) modifier;
	else
		job.modifier.FLOAT32 = * (float*) modifier;
	
	job.operation = operation;
	job.completion = completion;
	job.timer = duration;
	
	tween.append(job);
}

void UpdateJob(TweenJob& job)
{	
	TweenValue* value = (TweenValue*) job.value;
	
	switch (job.operation)
	{
		case OP_ADD:
			if (job.value_t == VALUE_INT32)
				value->INT32 += job.modifier.INT32;
			else
				value->FLOAT32 += job.modifier.FLOAT32;
			break;
		case OP_SUB:
			if (job.value_t == VALUE_INT32)
				value->INT32 -= job.modifier.INT32;
			else
				value->FLOAT32 -= job.modifier.FLOAT32;
			break;
		case OP_MUL:
			if (job.value_t == VALUE_INT32)
				value->INT32 *= job.modifier.INT32;
			else
				value->FLOAT32 *= job.modifier.FLOAT32;
			break;
		case OP_DIV:
			if (job.value_t == VALUE_INT32)
				value->INT32 /= job.modifier.INT32;
			else
				value->FLOAT32 /= job.modifier.FLOAT32;
			break;
		default:
			break;
	}
	
	job.timer--;
	if (job.timer == 0)
	{
		if (job.completion) *job.completion = 1;
	}
}

void UpdateJobs(Tween& tween)
{
	for (int i = 0; i < tween.size; i++)
	{
		TweenJob& job = tween.data[i];
		UpdateJob(job);
		if (job.timer < 1)
		{
			tween.remove(i);
			continue;
		}
	}
}

// value, target, duration
void LinearInterpolate(Tween& tween, int8 datatype, void* value, int duration, void* target, int8* completion = 0)
{
	if (datatype == VALUE_INT32)
	{
		int modifier = (* (int*) target) - (* (int*) value);
		NewJob(tween, value, &modifier, datatype, OP_ADD, duration, completion);
	}
	
	if (datatype == VALUE_FLOAT32)
	{
		float modifier = (* (float*) target) - (* (float*) value);
		NewJob(tween, value, &modifier, datatype, OP_ADD, duration, completion);
	}
}

// value, modifier, duration
void LinearInterpolate(Tween& tween, int8 datatype, void* value, void* modifier, int duration, int8* completion = 0)
{
	NewJob(tween, value, modifier, datatype, OP_ADD, duration, completion);
}

// value, modifier, target
void LinearInterpolate(Tween& tween, int8 datatype, void* value, void* modifier, void* target, int8* completion = 0)
{
	if (datatype == VALUE_INT32)
	{
		// (target - value) / modifier
		// total change / change per step = number of steps
		int duration = ( (* (int*) target) - (* (int*) value) ) / (* (int*) modifier);
		NewJob(tween, value, modifier, datatype, OP_ADD, duration, completion);
	}
	
	if (datatype == VALUE_FLOAT32)
	{
		int duration = ( (* (float*) target) - (* (float*) value) ) / (* (float*) modifier);
		NewJob(tween, value, &modifier, datatype, OP_ADD, duration, completion);
	}
}

// value, total change, duration
void LinearInterpolate(Tween& tween, int8 datatype, int duration, void* value, void* change, int8* completion = 0)
{
	if (datatype == VALUE_INT32)
	{
		int modifier = (* (int*) change) / duration;
		NewJob(tween, value, &modifier, datatype, OP_ADD, duration, completion);
	}
	
	if (datatype == VALUE_FLOAT32)
	{
		float modifier = (* (float*) change) / duration;
		NewJob(tween, value, &modifier, datatype, OP_ADD, duration, completion);
	}
}