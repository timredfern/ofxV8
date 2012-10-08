#include "testApp.h"

using namespace ofxV8;

v8::Handle<v8::Value> cppfunc(const v8::Arguments& args)
{
	printf("this is cppfunc\n");
	return v8::Undefined();
}

//--------------------------------------------------------------
void testApp::setup()
{
	
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(40);
	
	
	// js to oF type convert
	cout << $("'Hello v8!'").as<string>() << endl;
	cout << $("42").as<int>() << endl;
	cout << $("3.14 * 2").as<float>() << endl;
	
	// eval string
	$("print('eval string')");
	
	// eval file
	$$("test.js");
	
	// call js function
	Function jsfunc = $("(function test(a, b, c) { print(a, b, c); })").as<Function>();
	jsfunc("call", "from", "oF");
	
	// set callback function
	$f("call_cppfunc", cppfunc);
	$("call_cppfunc()");
	
	// pass c++ object as argment
	Function add = $("(function add(v1, v2) { return v1 + v2; })").as<Function>();
	
	Object result;
	
	Object v1(10), v2(20);
	result = add(v1, v2);
	cout << result.as<int>() << endl;
	
	Object s1("foo"), s2("bar");
	result = add(s1, s2);
	cout << result.as<string>() << endl;
	
	// global object lifetime
	$("var js_value = 0");
}

//--------------------------------------------------------------
void testApp::update()
{
	
}

//--------------------------------------------------------------
void testApp::draw()
{
	// global object lifetime
	string js_value = $("js_value++").as<string>();
	
	ofDrawBitmapString("js_value=" + js_value, 10, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
