#include "extensions/filters/network/tt_rpc_proxy/proxy_filter.h"
#include "extensions/filters/network/tt_rpc_proxy/transport.h"

#include "envoy/buffer/buffer.h"
#include "envoy/network/connection.h"

#include "common/common/assert.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace TTRPCProxy {

ProxyFilter::ProxyFilter(DecoderFactory& factory)
  : decoder_(factory.create(*this)) {
}

ProxyFilter::~ProxyFilter() {

}

void ProxyFilter::initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) {
  read_callbacks_ = &callbacks;
}

Network::FilterStatus ProxyFilter::onData(Buffer::Instance& data, bool end_stream) {
  ENVOY_CONN_LOG(trace, "ProxyFilter: got {} bytes, end_stream: {}", read_callbacks_->connection(), data.length(), end_stream);
  try {
    decoder_->decode(data);
    ENVOY_CONN_LOG(trace, "ProxyFilter: {} bytes after transport", read_callbacks_->connection(), data.length());
    return Network::FilterStatus::Continue;
  } catch (EnvoyException&) {
    ENVOY_CONN_LOG(trace, "decode error", read_callbacks_->connection());
    return Network::FilterStatus::StopIteration;
  }
}

void ProxyFilter::onRespValue(RespValuePtr&& value) {
  assert(&value);
}

} // namespace Echo
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
