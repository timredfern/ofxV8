#pragma once

#include <tr1/unordered_map>

#include "v8.h"
#include "ofMain.h"

#include "ofxV8Function.h"

namespace ofxV8
{

class Object;
typedef vector<Object> Array;
typedef std::tr1::unordered_map<Object, Object> Hash; // TODO: implement type convert method

class Object
{
public:

	Object();
	Object(v8::Handle<v8::Value> value);
	Object(bool o);
	Object(int o);
	Object(unsigned int o);
	Object(float o);
	Object(double o);
	Object(string o);
	Object(const char* o);
	Object(Array o);
	
	~Object();

	Object(const Object& copy);
	Object& operator=(const Object& copy);
	
	template<class T>
	inline T as() const
	{
		ofLogError("ofxV8", "invalid type");
		return T();
	}

	operator v8::Handle<v8::Value>() { return v; }
	operator const v8::Handle<v8::Value>() const { return v; }

private:

	v8::Handle<v8::Value> v;
};

template<>
inline bool Object::as() const
{
	v8::HandleScope scope;
	return v->BooleanValue();
}

template<>
inline int32_t Object::as() const
{
	v8::HandleScope scope;
	return v->Int32Value();
}

template<>
inline uint32_t Object::as() const
{
	v8::HandleScope scope;
	return v->Uint32Value();
}

template<>
inline float Object::as() const
{
	v8::HandleScope scope;
	return v->NumberValue();
}

template<>
inline double Object::as() const
{
	v8::HandleScope scope;
	return v->NumberValue();
}

template<>
inline string Object::as() const
{
	v8::HandleScope scope;

	if (v->IsArray())
	{
		string str;

		v8::Local<v8::Array> a = v8::Local<v8::Array>(v8::Array::Cast(*v));
		for (int i = 0; i < a->Length(); i++)
		{
			Object o = a->Get(i);
			str += o.as<string>() + ", ";
		}

		if (!str.empty()) str.resize(str.length() - 2);

		return "[" + str + "]";
	}
	else if (v->IsString())
	{
		return *v8::String::Utf8Value(v);
	}
	else if (v->IsObject())
	{
		return *v8::String::Utf8Value(v->ToObject()->ObjectProtoToString());
	}
	else
	{
		return *v8::String::Utf8Value(v);
	}
}

template<>
inline Array Object::as() const
{
	v8::HandleScope scope;

	if (!v->IsArray())
	{
		ofLogError("ofxV8", "this is not an Array");
		return Array();
	}

	Array result;
	v8::Local<v8::Array> a = v8::Local<v8::Array>(v8::Array::Cast(*v));

	for (int i = 0; i < a->Length(); i++)
		result.push_back(a->Get(i));

	return result;
}

template<>
inline Function Object::as() const
{
	v8::HandleScope scope;
	
	if (!v->IsFunction())
	{
		ofLogError("ofxV8", "this is not a Function");
		return Function();
	}

	v8::Local<v8::Function> func = v8::Local<v8::Function>(v8::Function::Cast(*v));
	return Function(func);
}
	
}