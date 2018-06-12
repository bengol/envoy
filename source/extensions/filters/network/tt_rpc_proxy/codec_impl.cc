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

void DecoderImpl::decode(Buffer::Instance& data) {
    TransportDecoderCallback callback;
    AutoTransportImpl* transport_decoder = new AutoTransportImpl(callback);

    try {
        bool success = transport_decoder->decodeFrameStart(data);
        ENVOY_LOG(trace, " decode thrift protocol data, result: {}", success);
        if (success) {
            transport_decoder->decodeFrameEnd(data);
        }
    } catch (EnvoyException& e) {
        ENVOY_LOG(trace, "exception: {}", e.what());
    }

    delete transport_decoder;

    RespValuePtr response_value;
    callbacks_.onRespValue(std::move(response_value));

}

} // namespace TTRPCProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy