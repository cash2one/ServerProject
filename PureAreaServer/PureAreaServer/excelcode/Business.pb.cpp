// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Business.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Business.pb.h"

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

namespace ExcelConf {

namespace {

const ::google::protobuf::Descriptor* Business_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Business_reflection_ = NULL;
const ::google::protobuf::Descriptor* Business_t_Business_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Business_t_Business_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Business_2eproto() {
  protobuf_AddDesc_Business_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Business.proto");
  GOOGLE_CHECK(file != NULL);
  Business_descriptor_ = file->message_type(0);
  static const int Business_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Business, datas_),
  };
  Business_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Business_descriptor_,
      Business::default_instance_,
      Business_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Business, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Business, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Business));
  Business_t_Business_descriptor_ = Business_descriptor_->nested_type(0);
  static const int Business_t_Business_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Business_t_Business, tbxid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Business_t_Business, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Business_t_Business, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Business_t_Business, price_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Business_t_Business, disprice_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Business_t_Business, person_),
  };
  Business_t_Business_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Business_t_Business_descriptor_,
      Business_t_Business::default_instance_,
      Business_t_Business_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Business_t_Business, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Business_t_Business, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Business_t_Business));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Business_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Business_descriptor_, &Business::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Business_t_Business_descriptor_, &Business_t_Business::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Business_2eproto() {
  delete Business::default_instance_;
  delete Business_reflection_;
  delete Business_t_Business::default_instance_;
  delete Business_t_Business_reflection_;
}

void protobuf_AddDesc_Business_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016Business.proto\022\tExcelConf\"\241\001\n\010Business"
    "\022-\n\005datas\030\001 \003(\0132\036.ExcelConf.Business.t_B"
    "usiness\032f\n\nt_Business\022\r\n\005tbxid\030\001 \002(\r\022\014\n\004"
    "type\030\002 \002(\r\022\n\n\002id\030\003 \002(\r\022\r\n\005price\030\004 \002(\t\022\020\n"
    "\010disprice\030\005 \002(\t\022\016\n\006person\030\006 \002(\t", 191);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Business.proto", &protobuf_RegisterTypes);
  Business::default_instance_ = new Business();
  Business_t_Business::default_instance_ = new Business_t_Business();
  Business::default_instance_->InitAsDefaultInstance();
  Business_t_Business::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Business_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Business_2eproto {
  StaticDescriptorInitializer_Business_2eproto() {
    protobuf_AddDesc_Business_2eproto();
  }
} static_descriptor_initializer_Business_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Business_t_Business::kTbxidFieldNumber;
const int Business_t_Business::kTypeFieldNumber;
const int Business_t_Business::kIdFieldNumber;
const int Business_t_Business::kPriceFieldNumber;
const int Business_t_Business::kDispriceFieldNumber;
const int Business_t_Business::kPersonFieldNumber;
#endif  // !_MSC_VER

Business_t_Business::Business_t_Business()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Business_t_Business::InitAsDefaultInstance() {
}

Business_t_Business::Business_t_Business(const Business_t_Business& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Business_t_Business::SharedCtor() {
  _cached_size_ = 0;
  tbxid_ = 0u;
  type_ = 0u;
  id_ = 0u;
  price_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  disprice_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  person_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Business_t_Business::~Business_t_Business() {
  SharedDtor();
}

void Business_t_Business::SharedDtor() {
  if (price_ != &::google::protobuf::internal::kEmptyString) {
    delete price_;
  }
  if (disprice_ != &::google::protobuf::internal::kEmptyString) {
    delete disprice_;
  }
  if (person_ != &::google::protobuf::internal::kEmptyString) {
    delete person_;
  }
  if (this != default_instance_) {
  }
}

void Business_t_Business::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Business_t_Business::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Business_t_Business_descriptor_;
}

const Business_t_Business& Business_t_Business::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Business_2eproto();
  return *default_instance_;
}

Business_t_Business* Business_t_Business::default_instance_ = NULL;

Business_t_Business* Business_t_Business::New() const {
  return new Business_t_Business;
}

void Business_t_Business::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    tbxid_ = 0u;
    type_ = 0u;
    id_ = 0u;
    if (has_price()) {
      if (price_ != &::google::protobuf::internal::kEmptyString) {
        price_->clear();
      }
    }
    if (has_disprice()) {
      if (disprice_ != &::google::protobuf::internal::kEmptyString) {
        disprice_->clear();
      }
    }
    if (has_person()) {
      if (person_ != &::google::protobuf::internal::kEmptyString) {
        person_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Business_t_Business::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 tbxid = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &tbxid_)));
          set_has_tbxid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_type;
        break;
      }

      // required uint32 type = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_id;
        break;
      }

      // required uint32 id = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_price;
        break;
      }

      // required string price = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_price:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_price()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->price().data(), this->price().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_disprice;
        break;
      }

      // required string disprice = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_disprice:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_disprice()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->disprice().data(), this->disprice().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_person;
        break;
      }

      // required string person = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_person:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_person()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->person().data(), this->person().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Business_t_Business::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->tbxid(), output);
  }

  // required uint32 type = 2;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->type(), output);
  }

  // required uint32 id = 3;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->id(), output);
  }

  // required string price = 4;
  if (has_price()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->price().data(), this->price().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->price(), output);
  }

  // required string disprice = 5;
  if (has_disprice()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->disprice().data(), this->disprice().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->disprice(), output);
  }

  // required string person = 6;
  if (has_person()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->person().data(), this->person().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      6, this->person(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Business_t_Business::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->tbxid(), target);
  }

  // required uint32 type = 2;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->type(), target);
  }

  // required uint32 id = 3;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->id(), target);
  }

  // required string price = 4;
  if (has_price()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->price().data(), this->price().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->price(), target);
  }

  // required string disprice = 5;
  if (has_disprice()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->disprice().data(), this->disprice().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->disprice(), target);
  }

  // required string person = 6;
  if (has_person()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->person().data(), this->person().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        6, this->person(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Business_t_Business::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 tbxid = 1;
    if (has_tbxid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->tbxid());
    }

    // required uint32 type = 2;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->type());
    }

    // required uint32 id = 3;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required string price = 4;
    if (has_price()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->price());
    }

    // required string disprice = 5;
    if (has_disprice()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->disprice());
    }

    // required string person = 6;
    if (has_person()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->person());
    }

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

void Business_t_Business::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Business_t_Business* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Business_t_Business*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Business_t_Business::MergeFrom(const Business_t_Business& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_tbxid()) {
      set_tbxid(from.tbxid());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_price()) {
      set_price(from.price());
    }
    if (from.has_disprice()) {
      set_disprice(from.disprice());
    }
    if (from.has_person()) {
      set_person(from.person());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Business_t_Business::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Business_t_Business::CopyFrom(const Business_t_Business& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Business_t_Business::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000003f) != 0x0000003f) return false;

  return true;
}

void Business_t_Business::Swap(Business_t_Business* other) {
  if (other != this) {
    std::swap(tbxid_, other->tbxid_);
    std::swap(type_, other->type_);
    std::swap(id_, other->id_);
    std::swap(price_, other->price_);
    std::swap(disprice_, other->disprice_);
    std::swap(person_, other->person_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Business_t_Business::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Business_t_Business_descriptor_;
  metadata.reflection = Business_t_Business_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Business::kDatasFieldNumber;
#endif  // !_MSC_VER

Business::Business()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Business::InitAsDefaultInstance() {
}

Business::Business(const Business& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Business::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Business::~Business() {
  SharedDtor();
}

void Business::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Business::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Business::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Business_descriptor_;
}

const Business& Business::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Business_2eproto();
  return *default_instance_;
}

Business* Business::default_instance_ = NULL;

Business* Business::New() const {
  return new Business;
}

void Business::Clear() {
  datas_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Business::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .ExcelConf.Business.t_Business datas = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_datas:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_datas()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_datas;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Business::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .ExcelConf.Business.t_Business datas = 1;
  for (int i = 0; i < this->datas_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->datas(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Business::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .ExcelConf.Business.t_Business datas = 1;
  for (int i = 0; i < this->datas_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->datas(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Business::ByteSize() const {
  int total_size = 0;

  // repeated .ExcelConf.Business.t_Business datas = 1;
  total_size += 1 * this->datas_size();
  for (int i = 0; i < this->datas_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->datas(i));
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

void Business::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Business* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Business*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Business::MergeFrom(const Business& from) {
  GOOGLE_CHECK_NE(&from, this);
  datas_.MergeFrom(from.datas_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Business::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Business::CopyFrom(const Business& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Business::IsInitialized() const {

  for (int i = 0; i < datas_size(); i++) {
    if (!this->datas(i).IsInitialized()) return false;
  }
  return true;
}

void Business::Swap(Business* other) {
  if (other != this) {
    datas_.Swap(&other->datas_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Business::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Business_descriptor_;
  metadata.reflection = Business_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ExcelConf

// @@protoc_insertion_point(global_scope)
