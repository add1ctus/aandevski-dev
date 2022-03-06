load("@io_bazel_rules_docker//cc:image.bzl", "cc_image")
load("@io_bazel_rules_docker//container:container.bzl", "container_push")

cc_binary(
    name = "api_handler_main",
    srcs = ["main.cc"],
    deps = [
        "//proto:web_cc_grpc",
        "//proto:web_cc_proto",
        "@com_google_protobuf//:protobuf",
        "@com_github_google_glog//:glog",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/strings",
    ],
    features = [
        "fully_static_link"
    ]
)

cc_image(
    name = "api_handler_image",
    binary = ":api_handler_main",
)

container_push(
    name = "api_handler_image_push",
    format = "Docker",
    image = ":api_handler_image",
    registry = "ghcr.io",
    repository = "add1ctus/api-handler",
)
