#ifndef LIBTORRENT_RASTERBAR_MACROS_H_
#define LIBTORRENT_RASTERBAR_MACROS_H_

#define REQUIRE_ARGUMENTS(n)                                                  \
  if (info.Length() < (n)) {                                                  \
    return Nan::ThrowTypeError("Expected " #n "arguments");                   \
  }

#define ARGUMENTS_OPTIONAL_OBJECT(i, var, defaultValue)                       \
  v8::Local<v8::Object> var;                                                  \
  if (info.Length() > i && !info[i]->IsUndefined()) {                         \
    if (!info[i]->IsObject()) {                                               \
      return Nan::ThrowTypeError("Argument " #i " must be a Object");         \
    }                                                                         \
    var = info[i]->ToObject();                                                \
  } else {                                                                    \
    var = (defaultValue);                                                     \
  }

#define ARGUMENTS_IS_NUMBER(i)                                                \
  (info.Length() > (i) && info[i]->IsNumber())

#define ARGUMENTS_REQUIRE_NUMBER(i, var)                                      \
  if (!ARGUMENTS_IS_NUMBER(i)) {                                              \
    return Nan::ThrowTypeError("Argument " #i " must be a Number");           \
  }                                                                           \
  int64_t var = info[i]->IntegerValue();

#define ARGUMENTS_IS_BOOLEAN(i)                                               \
  (info.Length() > (i) && info[i]->IsBoolean())

#define ARGUMENTS_REQUIRE_BOOLEAN(i, var)                                     \
  if (!ARGUMENTS_IS_BOOLEAN(i)) {                                             \
    return Nan::ThrowTypeError("Argument " #i " must be a Boolean");          \
  }                                                                           \
  bool var = info[i]->BooleanValue();

#define ARGUMENTS_IS_STRING(i)                                                \
  (info.Length() > (i) && info[i]->IsString())

#define ARGUMENTS_REQUIRE_STRING(i, var)                                      \
  if (!ARGUMENTS_IS_STRING(i)) {                                              \
    return Nan::ThrowTypeError("Argument " #i " must be a String");           \
  }                                                                           \
  Nan::Utf8String var(info[i]);

#define ARGUMENTS_IS_FUNCTION(i)                                              \
  (info.Length() > (i) && info[i]->IsFunction())

#define ARGUMENTS_REQUIRE_FUNCTION(i, var)                                    \
  if (!ARGUMENTS_IS_FUNCTION(i)) {                                            \
    return Nan::ThrowTypeError("Argument " #i " must be a Function");         \
  }                                                                           \
  v8::Local<v8::Function> var = v8::Local<v8::Function>::Cast(info[i]);

#define ARGUMENTS_IS_OBJECT(i)                                               \
  (info.Length() >= (i) && info[i]->IsObject())

#define ARGUMENTS_IS_INSTANCE(i, cls)                                         \
  (ARGUMENTS_IS_OBJECT(i) && Nan::New(cls::prototype)->HasInstance(info[i]))

#define ARGUMENTS_REQUIRE_INSTANCE(i, cls, var)                               \
  if (!ARGUMENTS_IS_INSTANCE(i, cls)) {                                       \
    return Nan::ThrowTypeError("Argument " #i " must be a " #cls);            \
  }                                                                           \
  cls* var = Nan::ObjectWrap::Unwrap<cls>(info[i]->ToObject());

#define ARGUMENTS_IS_BUFFER(i)                                                \
  (info.Length() >= (i) && node::Buffer::HasInstance(info[i]))

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
