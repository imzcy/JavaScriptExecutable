#ifndef _JSE_H_
#define _JSE_H_

#include <v8.h>

namespace JSE {

template <typename TypeName>
inline void JSE_SET_METHOD(const TypeName &recv, const char *name, v8::FunctionCallback callback)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope handle_scope(isolate);
    v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, callback);

    v8::Local<v8::Function> fn = t->GetFunction();
    v8::Local<v8::String> fn_name = v8::String::NewFromUtf8(isolate, name);
    fn->SetName(fn_name);
    recv->Set(fn_name, fn);
}

inline void JSE_SET_PROTOTYPE_METHOD(v8::Handle<v8::FunctionTemplate> recv,
    const char* name,
    v8::FunctionCallback callback) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::HandleScope handle_scope(isolate);
    v8::Handle<v8::Signature> s = v8::Signature::New(isolate, recv);
    v8::Local<v8::FunctionTemplate> t =
        v8::FunctionTemplate::New(isolate, callback, v8::Handle<v8::Value>(), s);
    recv->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, name),
        t->GetFunction());
}

#define JSE_UI_SET_ACCESSOR(tpl, str, get, set) (tpl)->PrototypeTemplate()->SetAccessor(String::NewFromUtf8(isolate, str), get, set)

#define JSE_UI_SET_EVENTS(self, slot, impl, signal) connect(impl, SIGNAL(signal), self, SLOT(slot))

void FuncTest(const v8::FunctionCallbackInfo<v8::Value> &args);

}

#endif // _JSE_H_