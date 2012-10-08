#pragma once

#include "v8.h"
#include "ofMain.h"

#include "ofxV8Object.h"
#include "ofxV8Function.h"

#include <assert.h> //is being undeffed in ofMain.h?

namespace ofxV8
{

// eval script
Object $(string source, string source_name = "<string>");
Object $$(string script_path);

// add global function
Function $f(string funcname, v8::InvocationCallback function);

}