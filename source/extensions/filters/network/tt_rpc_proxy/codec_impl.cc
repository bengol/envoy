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

void DecoderImpl::decode(Buffer::Instance& data) {
    RespValuePtr response_value;
    callbacks_.onRespValue(std::move(response_value));
    ENVOY_LOG(trace, "start decode thrift protocol data, len: {}", data.length());
}

} // namespace TTRPCProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy