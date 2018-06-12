#pragma once

#include <cstdint>
#include <list>
#include <memory>
#include <string>

#include "envoy/network/filter.h"

#include "common/common/logger.h"


namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace TTRPCProxy {

/**
 * A TT Thrift proxy
 */
/**
 * Implementation of a basic echo filter.
 */
class ProxyFilter : public Network::ReadFilter, Logger::Loggable<Logger::Id::filter> {
public:
  ProxyFilter();
  ~ProxyFilter();
  
  // Network::ReadFilter
  Network::FilterStatus onData(Buffer::Instance& data, bool end_stream) override;
  Network::FilterStatus onNewConnection() override { return Network::FilterStatus::Continue; }
  void initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) override {
    read_callbacks_ = &callbacks;
  }

private:
  Network::ReadFilterCallbacks* read_callbacks_{};
};

} // namespace RedisProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
