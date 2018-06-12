#pragma once

#include <memory>
#include <string>
#include <vector>

#include "envoy/buffer/buffer.h"
#include "envoy/common/exception.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace TTRPCProxy {

/**
 * A variant implementation of a RESP value optimized for peformance. A C++11 union is used for
 * the underlying type so that no unnecessary allocations/constructions are needed.
 */
class RespValue {
public:
  RespValue() {}
  ~RespValue() {}
};

typedef std::unique_ptr<RespValue> RespValuePtr;

/**
 * Callbacks that the decoder fires.
 */
class DecoderCallbacks {
public:
  virtual ~DecoderCallbacks() {}

  /**
   * Called when a new top level RESP value has been decoded. This value may include multiple
   * sub-values in the case of arrays or nested arrays.
   * @param value supplies the decoded value that is now owned by the callee.
   */
  virtual void onRespValue(RespValuePtr&& value) PURE;
};

/**
 * A thrift rpc decoder
 */
class Decoder {
public:
  virtual ~Decoder() {}

  /**
   * Decode thrift rpc bytes.
   * @param data supplies the data to decode. All bytes will be consumed by the decoder or a
   *        ProtocolError will be thrown.
   */
  virtual void decode(Buffer::Instance& data) PURE;
};

typedef std::unique_ptr<Decoder> DecoderPtr;

/**
 * A factory for a thrift rpc decoder.
 */
class DecoderFactory {
public:
  virtual ~DecoderFactory() {}

  /**
   * Create a decoder given a set of decoder callbacks.
   */
  virtual DecoderPtr create(DecoderCallbacks& callbacks) PURE;
};

/**
 * A tt thrift protocol error.
 */
class ProtocolError : public EnvoyException {
public:
  ProtocolError(const std::string& error) : EnvoyException(error) {}
};

} // namespace TTRPCProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy