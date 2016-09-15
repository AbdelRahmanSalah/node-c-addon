// hello.cc
#include <node.h>
#include <stdlib.h>     /* srand, rand */

namespace demo {

  using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Number;
using v8::String;
using v8::Value;

void Add(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  double value = args[0]->NumberValue() + args[1]->NumberValue();
  Local<Number> num = Number::New(isolate, value);

  args.GetReturnValue().Set(num);
}

void GenerateRandom(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Number> num = Number::New(isolate, rand());

  args.GetReturnValue().Set(num);
}
// use it to return function not value
void CreateFunction(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

 Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, GenerateRandom);
 Local<Function> fn = tpl->GetFunction();

 // omit this to make it anonymous
 fn->SetName(String::NewFromUtf8(isolate, "generateRandom"));

 args.GetReturnValue().Set(fn);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "add", Add);
  NODE_SET_METHOD(exports, "random", GenerateRandom);
}

NODE_MODULE(addon, init)

}  // namespace demo
