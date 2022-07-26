// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: uposcashdrawer.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "uposcashdrawer.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace JposcashdrawerZMQ {

namespace {

const ::google::protobuf::Descriptor* Params_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Params_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* CmdTypeCashDrawer_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_uposcashdrawer_2eproto() {
  protobuf_AddDesc_uposcashdrawer_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "uposcashdrawer.proto");
  GOOGLE_CHECK(file != NULL);
  Params_descriptor_ = file->message_type(0);
  static const int Params_offsets_[10] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, cmd_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, insthdl_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, int32param_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, uint32param_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, uint64param_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, boolparam_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, strparam_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, buffer_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, errortext_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, errorcode_),
  };
  Params_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Params_descriptor_,
      Params::default_instance_,
      Params_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Params, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Params));
  CmdTypeCashDrawer_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_uposcashdrawer_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Params_descriptor_, &Params::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_uposcashdrawer_2eproto() {
  delete Params::default_instance_;
  delete Params_reflection_;
}

void protobuf_AddDesc_uposcashdrawer_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024uposcashdrawer.proto\022\021JposcashdrawerZM"
    "Q\"\361\001\n\006Params\0221\n\003cmd\030\001 \001(\0162$.Jposcashdraw"
    "erZMQ.CmdTypeCashDrawer\022\017\n\007instHdl\030\002 \001(\r"
    "\022\026\n\nint32Param\030\003 \003(\005B\002\020\001\022\027\n\013uint32Param\030"
    "\004 \003(\rB\002\020\001\022\027\n\013uint64Param\030\005 \003(\004B\002\020\001\022\021\n\tbo"
    "olParam\030\006 \003(\010\022\020\n\010strParam\030\007 \003(\t\022\016\n\006buffe"
    "r\030\010 \001(\014\022\021\n\terrorText\030\t \001(\t\022\021\n\terrorCode\030"
    "\n \001(\005*\364\002\n\021CmdTypeCashDrawer\022\017\n\013UPOSlibIn"
    "it\020\000\022\017\n\013UPOSlibExit\020\001\022\017\n\013UPOSlibOpen\020\002\022\020"
    "\n\014UPOSlibClose\020\003\022\020\n\014UPOSlibClaim\020\004\022\025\n\021UP"
    "OSlibGetClaimed\020\005\022\022\n\016UPOSlibRelease\020\006\022\033\n"
    "\027UPOSlibSetDeviceEnabled\020\007\022\033\n\027UPOSlibGet"
    "DeviceEnabled\020\010\022\023\n\017UPOSlibGetState\020\t\022\027\n\023"
    "UPOSlibSetAsyncMode\020\n\022\027\n\023UPOSlibGetAsync"
    "Mode\020\013\022\023\n\017UPOSlibDirectIO\020\014\022\025\n\021UPOSlibOp"
    "enDrawer\020\r\022\021\n\rUPOSlibOpened\020\016\022\035\n\031UPOSlib"
    "WaitForDrawerClose\020\017B3\n\033com.bizerba.jpos"
    ".CashDrawerB\024UposCashDrawerProtos", 713);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "uposcashdrawer.proto", &protobuf_RegisterTypes);
  Params::default_instance_ = new Params();
  Params::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_uposcashdrawer_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_uposcashdrawer_2eproto {
  StaticDescriptorInitializer_uposcashdrawer_2eproto() {
    protobuf_AddDesc_uposcashdrawer_2eproto();
  }
} static_descriptor_initializer_uposcashdrawer_2eproto_;
const ::google::protobuf::EnumDescriptor* CmdTypeCashDrawer_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CmdTypeCashDrawer_descriptor_;
}
bool CmdTypeCashDrawer_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int Params::kCmdFieldNumber;
const int Params::kInstHdlFieldNumber;
const int Params::kInt32ParamFieldNumber;
const int Params::kUint32ParamFieldNumber;
const int Params::kUint64ParamFieldNumber;
const int Params::kBoolParamFieldNumber;
const int Params::kStrParamFieldNumber;
const int Params::kBufferFieldNumber;
const int Params::kErrorTextFieldNumber;
const int Params::kErrorCodeFieldNumber;
#endif  // !_MSC_VER

Params::Params()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:JposcashdrawerZMQ.Params)
}

void Params::InitAsDefaultInstance() {
}

Params::Params(const Params& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:JposcashdrawerZMQ.Params)
}

void Params::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  cmd_ = 0;
  insthdl_ = 0u;
  buffer_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  errortext_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  errorcode_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Params::~Params() {
  // @@protoc_insertion_point(destructor:JposcashdrawerZMQ.Params)
  SharedDtor();
}

void Params::SharedDtor() {
  if (buffer_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete buffer_;
  }
  if (errortext_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete errortext_;
  }
  if (this != default_instance_) {
  }
}

void Params::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Params::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Params_descriptor_;
}

const Params& Params::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_uposcashdrawer_2eproto();
  return *default_instance_;
}

Params* Params::default_instance_ = NULL;

Params* Params::New() const {
  return new Params;
}

void Params::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Params*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 131) {
    ZR_(cmd_, insthdl_);
    if (has_buffer()) {
      if (buffer_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        buffer_->clear();
      }
    }
  }
  if (_has_bits_[8 / 32] & 768) {
    if (has_errortext()) {
      if (errortext_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        errortext_->clear();
      }
    }
    errorcode_ = 0;
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  int32param_.Clear();
  uint32param_.Clear();
  uint64param_.Clear();
  boolparam_.Clear();
  strparam_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Params::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:JposcashdrawerZMQ.Params)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .JposcashdrawerZMQ.CmdTypeCashDrawer cmd = 1;
      case 1: {
        if (tag == 8) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::JposcashdrawerZMQ::CmdTypeCashDrawer_IsValid(value)) {
            set_cmd(static_cast< ::JposcashdrawerZMQ::CmdTypeCashDrawer >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_instHdl;
        break;
      }

      // optional uint32 instHdl = 2;
      case 2: {
        if (tag == 16) {
         parse_instHdl:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &insthdl_)));
          set_has_insthdl();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_int32Param;
        break;
      }

      // repeated int32 int32Param = 3 [packed = true];
      case 3: {
        if (tag == 26) {
         parse_int32Param:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_int32param())));
        } else if (tag == 24) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 26, input, this->mutable_int32param())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_uint32Param;
        break;
      }

      // repeated uint32 uint32Param = 4 [packed = true];
      case 4: {
        if (tag == 34) {
         parse_uint32Param:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_uint32param())));
        } else if (tag == 32) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 34, input, this->mutable_uint32param())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_uint64Param;
        break;
      }

      // repeated uint64 uint64Param = 5 [packed = true];
      case 5: {
        if (tag == 42) {
         parse_uint64Param:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, this->mutable_uint64param())));
        } else if (tag == 40) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 1, 42, input, this->mutable_uint64param())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_boolParam;
        break;
      }

      // repeated bool boolParam = 6;
      case 6: {
        if (tag == 48) {
         parse_boolParam:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 1, 48, input, this->mutable_boolparam())));
        } else if (tag == 50) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, this->mutable_boolparam())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_boolParam;
        if (input->ExpectTag(58)) goto parse_strParam;
        break;
      }

      // repeated string strParam = 7;
      case 7: {
        if (tag == 58) {
         parse_strParam:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_strparam()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->strparam(this->strparam_size() - 1).data(),
            this->strparam(this->strparam_size() - 1).length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "strparam");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(58)) goto parse_strParam;
        if (input->ExpectTag(66)) goto parse_buffer;
        break;
      }

      // optional bytes buffer = 8;
      case 8: {
        if (tag == 66) {
         parse_buffer:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_buffer()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(74)) goto parse_errorText;
        break;
      }

      // optional string errorText = 9;
      case 9: {
        if (tag == 74) {
         parse_errorText:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_errortext()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->errortext().data(), this->errortext().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "errortext");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(80)) goto parse_errorCode;
        break;
      }

      // optional int32 errorCode = 10;
      case 10: {
        if (tag == 80) {
         parse_errorCode:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &errorcode_)));
          set_has_errorcode();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:JposcashdrawerZMQ.Params)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:JposcashdrawerZMQ.Params)
  return false;
#undef DO_
}

void Params::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:JposcashdrawerZMQ.Params)
  // optional .JposcashdrawerZMQ.CmdTypeCashDrawer cmd = 1;
  if (has_cmd()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->cmd(), output);
  }

  // optional uint32 instHdl = 2;
  if (has_insthdl()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->insthdl(), output);
  }

  // repeated int32 int32Param = 3 [packed = true];
  if (this->int32param_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(3, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
    output->WriteVarint32(_int32param_cached_byte_size_);
  }
  for (int i = 0; i < this->int32param_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32NoTag(
      this->int32param(i), output);
  }

  // repeated uint32 uint32Param = 4 [packed = true];
  if (this->uint32param_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(4, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
    output->WriteVarint32(_uint32param_cached_byte_size_);
  }
  for (int i = 0; i < this->uint32param_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32NoTag(
      this->uint32param(i), output);
  }

  // repeated uint64 uint64Param = 5 [packed = true];
  if (this->uint64param_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(5, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
    output->WriteVarint32(_uint64param_cached_byte_size_);
  }
  for (int i = 0; i < this->uint64param_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64NoTag(
      this->uint64param(i), output);
  }

  // repeated bool boolParam = 6;
  for (int i = 0; i < this->boolparam_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(
      6, this->boolparam(i), output);
  }

  // repeated string strParam = 7;
  for (int i = 0; i < this->strparam_size(); i++) {
  ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
    this->strparam(i).data(), this->strparam(i).length(),
    ::google::protobuf::internal::WireFormat::SERIALIZE,
    "strparam");
    ::google::protobuf::internal::WireFormatLite::WriteString(
      7, this->strparam(i), output);
  }

  // optional bytes buffer = 8;
  if (has_buffer()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      8, this->buffer(), output);
  }

  // optional string errorText = 9;
  if (has_errortext()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->errortext().data(), this->errortext().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "errortext");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      9, this->errortext(), output);
  }

  // optional int32 errorCode = 10;
  if (has_errorcode()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(10, this->errorcode(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:JposcashdrawerZMQ.Params)
}

::google::protobuf::uint8* Params::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:JposcashdrawerZMQ.Params)
  // optional .JposcashdrawerZMQ.CmdTypeCashDrawer cmd = 1;
  if (has_cmd()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->cmd(), target);
  }

  // optional uint32 instHdl = 2;
  if (has_insthdl()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->insthdl(), target);
  }

  // repeated int32 int32Param = 3 [packed = true];
  if (this->int32param_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      3,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
      _int32param_cached_byte_size_, target);
  }
  for (int i = 0; i < this->int32param_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteInt32NoTagToArray(this->int32param(i), target);
  }

  // repeated uint32 uint32Param = 4 [packed = true];
  if (this->uint32param_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      4,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
      _uint32param_cached_byte_size_, target);
  }
  for (int i = 0; i < this->uint32param_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32NoTagToArray(this->uint32param(i), target);
  }

  // repeated uint64 uint64Param = 5 [packed = true];
  if (this->uint64param_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      5,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
      _uint64param_cached_byte_size_, target);
  }
  for (int i = 0; i < this->uint64param_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt64NoTagToArray(this->uint64param(i), target);
  }

  // repeated bool boolParam = 6;
  for (int i = 0; i < this->boolparam_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteBoolToArray(6, this->boolparam(i), target);
  }

  // repeated string strParam = 7;
  for (int i = 0; i < this->strparam_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->strparam(i).data(), this->strparam(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "strparam");
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(7, this->strparam(i), target);
  }

  // optional bytes buffer = 8;
  if (has_buffer()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        8, this->buffer(), target);
  }

  // optional string errorText = 9;
  if (has_errortext()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->errortext().data(), this->errortext().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "errortext");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        9, this->errortext(), target);
  }

  // optional int32 errorCode = 10;
  if (has_errorcode()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(10, this->errorcode(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:JposcashdrawerZMQ.Params)
  return target;
}

int Params::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .JposcashdrawerZMQ.CmdTypeCashDrawer cmd = 1;
    if (has_cmd()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->cmd());
    }

    // optional uint32 instHdl = 2;
    if (has_insthdl()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->insthdl());
    }

    // optional bytes buffer = 8;
    if (has_buffer()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->buffer());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional string errorText = 9;
    if (has_errortext()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->errortext());
    }

    // optional int32 errorCode = 10;
    if (has_errorcode()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->errorcode());
    }

  }
  // repeated int32 int32Param = 3 [packed = true];
  {
    int data_size = 0;
    for (int i = 0; i < this->int32param_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->int32param(i));
    }
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(data_size);
    }
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _int32param_cached_byte_size_ = data_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    total_size += data_size;
  }

  // repeated uint32 uint32Param = 4 [packed = true];
  {
    int data_size = 0;
    for (int i = 0; i < this->uint32param_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->uint32param(i));
    }
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(data_size);
    }
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _uint32param_cached_byte_size_ = data_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    total_size += data_size;
  }

  // repeated uint64 uint64Param = 5 [packed = true];
  {
    int data_size = 0;
    for (int i = 0; i < this->uint64param_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt64Size(this->uint64param(i));
    }
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(data_size);
    }
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _uint64param_cached_byte_size_ = data_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    total_size += data_size;
  }

  // repeated bool boolParam = 6;
  {
    int data_size = 0;
    data_size = 1 * this->boolparam_size();
    total_size += 1 * this->boolparam_size() + data_size;
  }

  // repeated string strParam = 7;
  total_size += 1 * this->strparam_size();
  for (int i = 0; i < this->strparam_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->strparam(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Params::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Params* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Params*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Params::MergeFrom(const Params& from) {
  GOOGLE_CHECK_NE(&from, this);
  int32param_.MergeFrom(from.int32param_);
  uint32param_.MergeFrom(from.uint32param_);
  uint64param_.MergeFrom(from.uint64param_);
  boolparam_.MergeFrom(from.boolparam_);
  strparam_.MergeFrom(from.strparam_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_cmd()) {
      set_cmd(from.cmd());
    }
    if (from.has_insthdl()) {
      set_insthdl(from.insthdl());
    }
    if (from.has_buffer()) {
      set_buffer(from.buffer());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_errortext()) {
      set_errortext(from.errortext());
    }
    if (from.has_errorcode()) {
      set_errorcode(from.errorcode());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Params::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Params::CopyFrom(const Params& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Params::IsInitialized() const {

  return true;
}

void Params::Swap(Params* other) {
  if (other != this) {
    std::swap(cmd_, other->cmd_);
    std::swap(insthdl_, other->insthdl_);
    int32param_.Swap(&other->int32param_);
    uint32param_.Swap(&other->uint32param_);
    uint64param_.Swap(&other->uint64param_);
    boolparam_.Swap(&other->boolparam_);
    strparam_.Swap(&other->strparam_);
    std::swap(buffer_, other->buffer_);
    std::swap(errortext_, other->errortext_);
    std::swap(errorcode_, other->errorcode_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Params::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Params_descriptor_;
  metadata.reflection = Params_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace JposcashdrawerZMQ

// @@protoc_insertion_point(global_scope)
