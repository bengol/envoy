#pragma once

#include <string>

#include "envoy/config/filter/network/tcp_proxy/v2/tcp_proxy.pb.validate.h"

#include "extensions/filters/network/common/factory_base.h"
#include "extensions/filters/network/well_known_names.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace TTRPCProxy {

/**
 * Config registration for the redis proxy filter. @see NamedNetworkFilterConfigFactory.
 */
class TTRPCProxyFilterConfigFactory
    : public Common::FactoryBase<envoy::config::filter::network::tcp_proxy::v2::TcpProxy> {
public:
  TTRPCProxyFilterConfigFactory() : FactoryBase(NetworkFilterNames::get().TT_RCP_PROXY) {}

  // NamedNetworkFilterConfigFactory
  Network::FilterFactoryCb createFilterFactory(const Json::Object&,
                                               Server::Configuration::FactoryContext&) override;

private:
  Network::FilterFactoryCb createFilterFactoryFromProtoTyped(
      const envoy::config::filter::network::tcp_proxy::v2::TcpProxy& proto_config,
      Server::Configuration::FactoryContext& context) override;
};

} // namespace RedisProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
