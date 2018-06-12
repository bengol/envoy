#pragma once

#include <cstdint>
#include <forward_list>
#include <string>
#include <vector>

#include "common/common/logger.h"

#include "extensions/filters/network/tt_rpc_proxy/codec.h"
#include "extensions/filters/network/tt_rpc_proxy/transport.h"
#include "extensions/filters/network/tt_rpc_proxy/protocol.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace TTRPCProxy {

class TransportDecoderCallback : public TransportCallbacks, Logger::Loggable<Logger::Id::thrift_rpc> {
public:
    void transportFrameStart(absl::optional<uint32_t> size) override;
    void transportFrameComplete() override;
};

class ProtocolDecoderCallback : public ProtocolCallbacks, Logger::Loggable<Logger::Id::thrift_rpc> {
public:
    void messageStart(const absl::string_view name, MessageType msg_type, int32_t seq_id) override;
    void structBegin(const absl::string_view name) override;
    void structField(const absl::string_view name, FieldType field_type, int16_t field_id) override;
    void structEnd() override;
    void messageComplete() override;
};

class DecoderImpl : public Decoder, Logger::Loggable<Logger::Id::thrift_rpc> {
public:
  DecoderImpl(DecoderCallbacks& callbacks) : callbacks_(callbacks) {}

  // TTRPCProxy::Decoder
  void decode(Buffer::Instance& data) override;

private:
  DecoderCallbacks& callbacks_;
};

/**
 * A factory implementation that returns a real decoder.
 */
class DecoderFactoryImpl : public DecoderFactory {
public:
  // TTRPCProxy::DecoderFactory
  DecoderPtr create(DecoderCallbacks& callbacks) override {
    return DecoderPtr{new DecoderImpl(callbacks)};
  }
};

} // namespace TTRPCProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy