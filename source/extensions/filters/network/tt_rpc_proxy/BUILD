licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

envoy_cc_library(
    name = "buffer_helper_lib",
    srcs = ["buffer_helper.cc"],
    hdrs = ["buffer_helper.h"],
    deps = [
        "//source/common/buffer:buffer_lib",
        "//source/common/common:assert_lib",
        "//source/common/common:byte_order_lib",
    ],
)

envoy_cc_library(
    name = "protocol_lib",
    srcs = [
        "binary_protocol.cc",
        "compact_protocol.cc",
        "protocol.cc",
    ],
    hdrs = [
        "binary_protocol.h",
        "compact_protocol.h",
        "protocol.h",
    ],
    external_deps = ["abseil_optional"],
    deps = [
        ":buffer_helper_lib",
        "//source/common/singleton:const_singleton",
    ],
)

envoy_cc_library(
    name = "transport_lib",
    srcs = ["transport.cc"],
    hdrs = ["transport.h"],
    deps = [
        ":buffer_helper_lib",
        ":protocol_lib",
        "//source/common/common:assert_lib",
        "//source/common/common:utility_lib",
        "//source/common/singleton:const_singleton",
    ],
)

envoy_cc_library(
    name = "codec_interface",
    hdrs = ["codec.h"],
    deps = ["//include/envoy/buffer:buffer_interface"],
)

envoy_cc_library(
    name = "codec_lib",
    srcs = ["codec_impl.cc"],
    hdrs = ["codec_impl.h"],
    deps = [
        ":codec_interface",
        ":transport_lib",
        "//source/common/common:assert_lib",
        "//source/common/common:minimal_logger_lib",
        "//source/common/common:utility_lib",
    ],
)

envoy_cc_library(
    name = "proxy_filter_lib",
    srcs = ["proxy_filter.cc"],
    hdrs = ["proxy_filter.h"],
    deps = [
        ":transport_lib",
        ":codec_interface",
        "//include/envoy/network:drain_decision_interface",
        "//include/envoy/network:filter_interface",
        "//include/envoy/upstream:cluster_manager_interface",
        "//source/common/buffer:buffer_lib",
        "//source/common/common:assert_lib",
        "//source/common/config:utility_lib",
        "@envoy_api//envoy/config/filter/network/tcp_proxy/v2:tcp_proxy_cc",
    ],
)

envoy_cc_library(
    name = "config",
    srcs = ["config.cc"],
    hdrs = ["config.h"],
    deps = [
        "//include/envoy/registry",
        "//source/common/config:filter_json_lib",
        "//source/common/tcp_proxy",
        "//source/extensions/filters/network:well_known_names",
        "//source/extensions/filters/network/common:factory_base_lib",
        "//source/extensions/filters/network/tt_rpc_proxy:proxy_filter_lib",
        "//source/extensions/filters/network/tt_rpc_proxy:codec_lib",
    ],
)
