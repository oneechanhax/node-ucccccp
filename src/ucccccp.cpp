 
/*
 *
 *	A bridge for ucccccp from c++ to javascript
 *
 *
 */

#include <node.h>

#include "../ucccccp/ucccccp.hpp"

namespace nodeucccccp {

// Ripped from node example for ease of use
using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

// Whats with all these string formats AAAAAA
const char* ToCString(const String::Utf8Value& value) {
  return *value ? *value : "error";
}
	
// For encrypting ucccccp code
void Encrypt(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate(); // For error throwing
		
	// check if input is valid
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Nothing to encrypt")));
		return;
	}
		
	// Output encrypted
	String::Utf8Value str(args[0]);
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, ucccccp::encrypt(std::string(ToCString(str))).c_str()));
}
	
void Decrypt(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate(); // For error throwing
		
	// check if input is valid
	if (args.Length() < 1) {
		String::Utf8Value str(args[0]);
		if (!ucccccp::validate(std::string(ToCString(str)))) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Not encrypted in ucccccp")));
			return;
		}
	}
		
	// Output decrypted
	String::Utf8Value str(args[0]);
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, ucccccp::decrypt(std::string(ToCString(str))).c_str()));
}
	
// Our init
void Init(Local<Object> exports) {
	NODE_SET_METHOD(exports, "encrypt", Encrypt);
	NODE_SET_METHOD(exports, "decrypt", Decrypt);
}

NODE_MODULE(ucccccp, Init)
	
}



