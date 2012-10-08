#include "ofxV8Function.h"

#include "ofxV8Object.h"

namespace ofxV8
{

extern void ReportException(v8::TryCatch* try_catch);
	
Function::Function(v8::Handle<v8::Function> func) : f(func)
{
	
}

Object Function::operator()()
{
	if (f.IsEmpty()) return Object();
	
	v8::HandleScope scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Value> result = f->Call(f, 0, NULL);
	if (result.IsEmpty()) ReportException(&try_catch);
	return result;
}

Object Function::operator()(const Object& a1)
{
	if (f.IsEmpty()) return Object();
	
	const int NUM_ARGS = 1;
	v8::HandleScope scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Value> a[NUM_ARGS] = { a1 };
	v8::Handle<v8::Value> result = f->Call(f, NUM_ARGS, a);
	if (result.IsEmpty()) ReportException(&try_catch);
	return result;
}

Object Function::operator()(const Object& a1, const Object& a2)
{
	if (f.IsEmpty()) return Object();
	
	const int NUM_ARGS = 2;
	v8::HandleScope scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Value> a[NUM_ARGS] = { a1, a2 };
	v8::Handle<v8::Value> result = f->Call(f, NUM_ARGS, a);
	if (result.IsEmpty()) ReportException(&try_catch);
	return result;
}

Object Function::operator()(const Object& a1,
							const Object& a2,
							const Object& a3)
{
	if (f.IsEmpty()) return Object();
	
	const int NUM_ARGS = 3;
	v8::HandleScope scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Value> a[NUM_ARGS] = { a1, a2, a3 };
	v8::Handle<v8::Value> result = f->Call(f, NUM_ARGS, a);
	if (result.IsEmpty()) ReportException(&try_catch);
	return result;
}

Object Function::operator()(const Object& a1,
							const Object& a2,
							const Object& a3,
							const Object& a4)
{
	if (f.IsEmpty()) return Object();
	
	const int NUM_ARGS = 4;
	v8::HandleScope scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Value> a[NUM_ARGS] = { a1, a2, a3, a4 };
	v8::Handle<v8::Value> result = f->Call(f, NUM_ARGS, a);
	if (result.IsEmpty()) ReportException(&try_catch);
	return result;
}

Object Function::operator()(const Object& a1,
							const Object& a2,
							const Object& a3,
							const Object& a4,
							const Object& a5)
{
	if (f.IsEmpty()) return Object();
	
	const int NUM_ARGS = 5;
	v8::HandleScope scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Value> a[NUM_ARGS] = { a1, a2, a3, a4, a5 };
	v8::Handle<v8::Value> result = f->Call(f, NUM_ARGS, a);
	if (result.IsEmpty()) ReportException(&try_catch);
	return result;
}

Object Function::operator()(const Object& a1,
							const Object& a2,
							const Object& a3,
							const Object& a4,
							const Object& a5,
							const Object& a6)
{
	if (f.IsEmpty()) return Object();
	
	const int NUM_ARGS = 6;
	v8::HandleScope scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Value> a[NUM_ARGS] = { a1, a2, a3, a4, a5, a6 };
	v8::Handle<v8::Value> result = f->Call(f, NUM_ARGS, a);
	if (result.IsEmpty()) ReportException(&try_catch);
	return result;
}

Object Function::operator()(const Object& a1,
							const Object& a2,
							const Object& a3,
							const Object& a4,
							const Object& a5,
							const Object& a6,
							const Object& a7)
{
	if (f.IsEmpty()) return Object();
	
	const int NUM_ARGS = 7;
	v8::HandleScope scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Value> a[NUM_ARGS] = { a1, a2, a3, a4, a5, a6, a7 };
	v8::Handle<v8::Value> result = f->Call(f, NUM_ARGS, a);
	if (result.IsEmpty()) ReportException(&try_catch);
	return result;
}

Object Function::operator()(const Object& a1,
							const Object& a2,
							const Object& a3,
							const Object& a4,
							const Object& a5,
							const Object& a6,
							const Object& a7,
							const Object& a8)
{
	if (f.IsEmpty()) return Object();
	
	const int NUM_ARGS = 8;
	v8::HandleScope scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Value> a[NUM_ARGS] = { a1, a2, a3, a4, a5, a6, a7, a8 };
	v8::Handle<v8::Value> result = f->Call(f, NUM_ARGS, a);
	if (result.IsEmpty()) ReportException(&try_catch);
	return result;
}

Object Function::operator()(const Object& a1,
							const Object& a2,
							const Object& a3,
							const Object& a4,
							const Object& a5,
							const Object& a6,
							const Object& a7,
							const Object& a8,
							const Object& a9)
{
	if (f.IsEmpty()) return Object();
	
	const int NUM_ARGS = 9;
	v8::HandleScope scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Value> a[NUM_ARGS] = { a1, a2, a3, a4, a5, a6, a7, a8, a9 };
	v8::Handle<v8::Value> result = f->Call(f, NUM_ARGS, a);
	if (result.IsEmpty()) ReportException(&try_catch);
	return result;
}

Object Function::operator()(const Object& a1,
							const Object& a2,
							const Object& a3,
							const Object& a4,
							const Object& a5,
							const Object& a6,
							const Object& a7,
							const Object& a8,
							const Object& a9,
							const Object& a10)
{
	if (f.IsEmpty()) return Object();
	
	const int NUM_ARGS = 10;
	v8::HandleScope scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Value> a[NUM_ARGS] = { a1, a2, a3, a4, a5, a6, a7, a8, a9, a10 };
	v8::Handle<v8::Value> result = f->Call(f, NUM_ARGS, a);
	if (result.IsEmpty()) ReportException(&try_catch);
	return result;
}
	
}