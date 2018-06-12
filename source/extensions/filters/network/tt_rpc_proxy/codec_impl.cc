#include "extensions/filters/network/tt_rpc_proxy/codec_impl.h"

#include <cstdint>
#include <string>
#include <vector>

#include "common/common/assert.h"
#include "common/common/fmt.h"
#include "common/common/utility.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace TTRPCProxy {

void TransportDecoderCallback::transportFrameStart(absl::optional<uint32_t> size) {
    ENVOY_LOG(trace, "transportFrameStart, size:{}", size.has_value());
}

void TransportDecoderCallback::transportFrameComplete() {
    ENVOY_LOG(trace, "transportFrameComplete");
}

void ProtocolDecoderCallback::messageStart(const absl::string_view name, MessageType msg_type, int32_t seq_id) {
    UNREFERENCED_PARAMETER(name);
    UNREFERENCED_PARAMETER(msg_type);
    UNREFERENCED_PARAMETER(seq_id);
}

void ProtocolDecoderCallback::structBegin(const absl::string_view name) {
    UNREFERENCED_PARAMETER(name);
}

void ProtocolDecoderCallback::structField(const absl::string_view name, FieldType field_type, int16_t field_id) {
    UNREFERENCED_PARAMETER(name);
    UNREFERENCED_PARAMETER(field_type);
    UNREFERENCED_PARAMETER(field_id);
}

void ProtocolDecoderCallback::structEnd() {

}

void ProtocolDecoderCallback::messageComplete() {

}

void DecoderImpl::decode(Buffer::Instance& data) {
    TransportDecoderCallback transport_callback;
    ProtocolDecoderCallback protocol_callback;
    AutoTransportImplPtr transport_decoder = std::make_unique<AutoTransportImpl>(transport_callback);
    AutoProtocolImplPtr protocol_decoder = std::make_unique<AutoProtocolImpl>(protocol_callback);

    try {
        // Transport decode
        bool success = transport_decoder->decodeFrameStart(data);
        ENVOY_LOG(trace, " decode thrift transport: {}", success);
        if (success) {
            transport_decoder->decodeFrameEnd(data);
        }

        // protocol decode
        std::string name;
        MessageType msg_type;
        int32_t seq_id;
        success = protocol_decoder->readMessageBegin(data, name, msg_type, seq_id);
        ENVOY_LOG(trace, " decode thrift protocol: {}", success);
        if (success) {
            ENVOY_LOG(trace, "name:{} msg_type:{} seq_id:{}", name, static_cast<int8_t>(msg_type), seq_id);
        }
        protocol_decoder->readMessageEnd(data);
    } catch (EnvoyException& e) {
        ENVOY_LOG(trace, "exception: {}", e.what());
    }

    RespValuePtr response_value;
    callbacks_.onRespValue(std::move(response_value));

}

} // namespace TTRPCProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy