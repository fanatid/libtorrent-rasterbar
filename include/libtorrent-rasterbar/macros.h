#ifndef LIBTORRENT_RASTERBAR_MACROS_H_
#define LIBTORRENT_RASTERBAR_MACROS_H_

#define REQUIRE_ARGUMENT_NUMBER(i, var)                                       \
  if (info.Length() <= (i) || !info[i]->IsNumber()) {                         \
    return Nan::ThrowTypeError("Argument " #i " must be a number");           \
  }                                                                           \
  int64_t var = info[i]->IntegerValue();

#define REQUIRE_ARGUMENT_BOOLEAN(i, var)                                      \
  if (info.Length() <= (i) || !info[i]->IsBoolean()) {                        \
    return Nan::ThrowTypeError("Argument " #i " must be a boolean");          \
  }                                                                           \
  bool var = info[i]->BooleanValue();

#define REQUIRE_ARGUMENT_STRING(i, var)                                       \
  if (info.Length() <= (i) || !info[i]->IsString()) {                         \
    return Nan::ThrowTypeError("Argument " #i " must be a string");           \
  }                                                                           \
  Nan::Utf8String var(info[i]);

#define REQUIRE_ARGUMENT_FUNCTION(i, var)                                     \
  if (info.Length() <= (i) || !info[i]->IsFunction()) {                       \
    return Nan::ThrowTypeError("Argument " #i " must be a string");           \
  }                                                                           \
  v8::Local<v8::Function> var = v8::Local<v8::Function>::Cast(info[i]);

#define REQUIRE_ARGUMENT_INSTANCE(i, cls, var)                                \
  if (info.Length() < (i) || !info[i]->IsObject() || !Nan::New(cls::prototype)->HasInstance(info[i])) { \
    return Nan::ThrowTypeError("Argument " #i " must be a " #cls);            \
  }                                                                           \
  cls* var = Nan::ObjectWrap::Unwrap<cls>(info[i]->ToObject());

#define SET_VALUE(target, key, value)                                         \
  Nan::Set(target, Nan::New(key).ToLocalChecked(), value);

#define SET_STRING(target, key, value)                                        \
  SET_VALUE(target, key, Nan::New(value).ToLocalChecked());

#define SET_BOOLEAN(target, key, value)                                       \
  SET_VALUE(target, key, Nan::New(value));

#define SET_INTEGER(target, key, value)                                       \
  SET_VALUE(target, key, Nan::New(value));

#define SET_FUNCTION(target, key, value)                                      \
  SET_VALUE(target, key, Nan::New<v8::Function>(value));

#endif // LIBTORRENT_RASTERBAR_MACROS_H_
