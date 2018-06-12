#pragma once

#include <cstdint>
#include <list>
#include <memory>
#include <string>

#include "envoy/network/filter.h"
#include "common/common/logger.h"
#include "extensions/filters/network/tt_rpc_proxy/codec.h"


namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace TTRPCProxy {

/**
 * A TT Thrift proxy
 */
class ProxyFilter : public Network::ReadFilter, 
                    public DecoderCallbacks,
                    public Logger::Loggable<Logger::Id::thrift_rpc> {
public:
  ProxyFilter(DecoderFactory& factory);
  ~ProxyFilter();

  // Network::ReadFilter
  Network::FilterStatus onData(Buffer::Instance& data, bool end_stream) override;
  Network::FilterStatus onNewConnection() override { return Network::FilterStatus::Continue; }
  void initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) override;

  // RedisProxy::DecoderCallbacks
  void onRespValue(RespValuePtr&& value) override;

private:
  Network::ReadFilterCallbacks* read_callbacks_{};
  DecoderPtr decoder_;
};

} // namespace RedisProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
