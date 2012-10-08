#include "ofxV8.h"

namespace ofxV8
{

//
// basic functions based v8's shell.cc
//


// Extracts a C string from a V8 Utf8Value.
const char*ToCString(const v8::String::Utf8Value& value)
{
	return *value ? *value : "<string conversion failed>";
}

// The callback that is invoked by v8 whenever the JavaScript 'print'
// function is called.  Prints its arguments on stdout separated by
// spaces and ending with a newline.
v8::Handle<v8::Value> Print(const v8::Arguments& args)
{
	bool first = true;
	for (int i = 0; i < args.Length(); i++)
	{
		v8::HandleScope handle_scope;
		if (first)
		{
			first = false;
		}
		else
		{
			printf(" ");
		}
		
		v8::String::Utf8Value str(args[i]);
		const char* cstr = ToCString(str);
		
		if (args[0]->IsString())
			printf("'%s'", cstr);
		else
			printf("%s", cstr);
	}
	printf("\n");
	fflush(stdout);
	return v8::Undefined();
}

// Reads a file into a v8 string.
v8::Handle<v8::String> ReadFile(const char* name)
{
	FILE* file = fopen(name, "rb");
	if (file == NULL) return v8::Handle<v8::String>();

	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	char* chars = new char[size + 1];
	chars[size] = '\0';
	for (int i = 0; i < size;)
	{
		int read = fread(&chars[i], 1, size - i, file);
		i += read;
	}
	fclose(file);
	v8::Handle<v8::String> result = v8::String::New(chars, size);
	delete[] chars;
	return result;
}

// The callback that is invoked by v8 whenever the JavaScript 'read'
// function is called.  This function loads the content of the file named in
// the argument into a JavaScript string.
v8::Handle<v8::Value> Read(const v8::Arguments& args)
{
	if (args.Length() != 1)
	{
		return v8::ThrowException(v8::String::New("Bad parameters"));
	}
	v8::String::Utf8Value file(args[0]);
	if (*file == NULL)
	{
		return v8::ThrowException(v8::String::New("Error loading file"));
	}
	v8::Handle<v8::String> source = ReadFile(*file);
	if (source.IsEmpty())
	{
		return v8::ThrowException(v8::String::New("Error loading file"));
	}
	return source;
}

void ReportException(v8::TryCatch* try_catch)
{
	v8::HandleScope handle_scope;
	v8::String::Utf8Value exception(try_catch->Exception());
	const char* exception_string = ToCString(exception);
	v8::Handle<v8::Message> message = try_catch->Message();
	if (message.IsEmpty())
	{
		// V8 didn't provide any extra information about this error; just
		// print the exception.
		printf("%s\n", exception_string);
	}
	else
	{
		// Print (filename):(line number): (message).
		v8::String::Utf8Value filename(message->GetScriptResourceName());
		const char* filename_string = ToCString(filename);
		int linenum = message->GetLineNumber();
		printf("%s:%i: %s\n", filename_string, linenum, exception_string);
		// Print line of source code.
		v8::String::Utf8Value sourceline(message->GetSourceLine());
		const char* sourceline_string = ToCString(sourceline);
		printf("%s\n", sourceline_string);
		// Print wavy underline (GetUnderline is deprecated).
		int start = message->GetStartColumn();
		for (int i = 0; i < start; i++)
		{
			printf(" ");
		}
		int end = message->GetEndColumn();
		for (int i = start; i < end; i++)
		{
			printf("^");
		}
		printf("\n");
		v8::String::Utf8Value stack_trace(try_catch->StackTrace());
		if (stack_trace.length() > 0)
		{
			const char* stack_trace_string = ToCString(stack_trace);
			printf("%s\n", stack_trace_string);
		}
	}
}


// Executes a string within the current v8 context.
v8::Handle<v8::Value> ExecuteString(v8::Handle<v8::String> source, v8::Handle<v8::Value> name)
{
	v8::HandleScope handle_scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::Script> script = v8::Script::Compile(source, name);

	if (script.IsEmpty())
	{
		// Print errors that happened during compilation.
		ReportException(&try_catch);
		return v8::Undefined();
	}
	else
	{
		v8::Handle<v8::Value> result = script->Run();
		if (result.IsEmpty())
		{
			assert(try_catch.HasCaught());
			// Print errors that happened during execution.
			ReportException(&try_catch);
			return v8::Undefined();
		}
		else
		{
			assert(!try_catch.HasCaught());
			if (!result->IsUndefined())
			{
				return result;
			}
			return v8::Undefined();
		}
	}
}


//
// ofxV8
//

v8::Persistent<v8::Context> context;
static v8::Context::Scope *context_scope = NULL;

void initV8()
{
	static bool v8_inited = false;
	if (v8_inited) return;
	v8_inited = true;

	v8::HandleScope scope;
	v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
	global->Set(v8::String::NewSymbol("print"), v8::FunctionTemplate::New(Print));
	global->Set(v8::String::NewSymbol("read"), v8::FunctionTemplate::New(Read));

	const char* extensionNames[] = { "v8/gc" };
	v8::ExtensionConfiguration extensions(sizeof(extensionNames)/sizeof(extensionNames[0]), extensionNames);

	context = v8::Context::New(&extensions, global);
	context_scope = new v8::Context::Scope(context);

	ofLogVerbose("ofxV8", "v8 engine inited");
}

Object $(string source, string source_name)
{
	initV8();

	v8::HandleScope scope;
	return ExecuteString(v8::String::New(source.c_str()),
						 v8::String::NewSymbol(source_name.c_str()));
}

Object $$(string path)
{
	
	ofBuffer buffer;

	if (path.substr(0, 7) == "http://")
		buffer = ofLoadURL(path).data;
	else
		buffer = ofBufferFromFile(path);

	return $(buffer.getText(), path);
	
}

Function $f(string funcname, v8::InvocationCallback function)
{
	initV8();
	
	v8::HandleScope scope;
	v8::Local<v8::Object> global = context->Global();
	
	v8::Local<v8::Function> func = v8::FunctionTemplate::New(function)->GetFunction();
	global->Set(v8::String::NewSymbol(funcname.c_str()), func);
	
	return Function(func);
}

}