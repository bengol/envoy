#include "extensions/filters/network/tt_rpc_proxy/config.h"

#include <memory>
#include <string>

#include "envoy/registry/registry.h"

#include "common/config/filter_json.h"

#include "extensions/filters/network/tt_rpc_proxy/proxy_filter.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace TTRPCProxy {

Network::FilterFactoryCb TTRPCProxyFilterConfigFactory::createFilterFactoryFromProtoTyped(
    const envoy::config::filter::network::tcp_proxy::v2::TcpProxy& proto_config,
    Server::Configuration::FactoryContext& context) {
  assert(&proto_config);
  assert(&context);
  return [](Network::FilterManager& filter_manager) -> void {
    filter_manager.addReadFilter(
        std::make_shared<ProxyFilter>());
  };
}

Network::FilterFactoryCb
TTRPCProxyFilterConfigFactory::createFilterFactory(const Json::Object& json_config,
                                                   Server::Configuration::FactoryContext& context) {
  envoy::config::filter::network::tcp_proxy::v2::TcpProxy proto_config;
  Config::FilterJson::translateTcpProxy(json_config, proto_config);
  return createFilterFactoryFromProtoTyped(proto_config, context);
}

/**
 * Static registration for the tt_rpc_proxy filter. @see RegisterFactory.
 */
static Registry::RegisterFactory<TTRPCProxyFilterConfigFactory,
                                 Server::Configuration::NamedNetworkFilterConfigFactory>
    registered_;

} // namespace RedisProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
