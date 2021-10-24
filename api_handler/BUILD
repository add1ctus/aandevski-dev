cc_binary(
    name = "api_handler_main",
    srcs = ["main.cc"],
    deps = [
        "//proto:web_cc_grpc",
        "//proto:web_cc_proto",
        "@com_github_google_glog//:glog",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
        "@com_google_absl//absl/flags:flag",
    ],
)
