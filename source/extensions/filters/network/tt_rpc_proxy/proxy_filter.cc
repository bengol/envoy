#include "extensions/filters/network/tt_rpc_proxy/proxy_filter.h"

#include "envoy/buffer/buffer.h"
#include "envoy/network/connection.h"

#include "common/common/assert.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace TTRPCProxy {

ProxyFilter::ProxyFilter() {

}

ProxyFilter::~ProxyFilter() {

}

Network::FilterStatus ProxyFilter::onData(Buffer::Instance& data, bool end_stream) {
  ENVOY_CONN_LOG(trace, "echo: got {} bytes", read_callbacks_->connection(), data.length());
  read_callbacks_->connection().write(data, end_stream);
  ASSERT(0 == data.length());
  return Network::FilterStatus::StopIteration;
}

} // namespace Echo
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
