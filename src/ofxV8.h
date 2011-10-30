#pragma once

#include "ofMain.h"
#include "v8.h"

#include "ofxV8Object.h"
#include "ofxV8Function.h"

namespace ofxV8
{

// eval script
Object $(string source, string source_name = "<string>");
Object $$(string script_path);

// add global function
Function $f(string funcname, v8::InvocationCallback function);

}