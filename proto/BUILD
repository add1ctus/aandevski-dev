load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

package(
    default_visibility = ["//visibility:public"],
)

proto_library(
    name = "web_proto",
    srcs = ["web.proto"],
    deps = [
        "@com_google_protobuf//:timestamp_proto",
    ],
)

cc_proto_library(
    name = "web_cc_proto",
    deps = [":web_proto"],
)

cc_grpc_library(
    name = "web_cc_grpc",
    srcs = [":web_proto"],
    deps = [":web_cc_proto"],
    grpc_only = True,
)
