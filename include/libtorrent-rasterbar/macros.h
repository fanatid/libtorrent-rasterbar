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

#endif // LIBTORRENT_RASTERBAR_MACROS_H_
