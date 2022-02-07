load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# ~~~ PYTHON PIP ~~~
http_archive(
    name = "rules_python",
    sha256 = "954aa89b491be4a083304a2cb838019c8b8c3720a7abb9c4cb81ac7a24230cea",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.4.0/rules_python-0.4.0.tar.gz",
)

load("@rules_python//python:pip.bzl", "pip_install")

pip_install(
    name = "pip_deps",
    requirements = "//:python_requirements.txt",
)

# ~~~ GRPC ~~~
http_archive(
    name = "com_github_grpc_grpc",
    strip_prefix = "grpc-b0f37a22bbae12a4b225a88be6d18d5e41dce881",
    urls = [
        "https://github.com/grpc/grpc/archive/b0f37a22bbae12a4b225a88be6d18d5e41dce881.tar.gz",
    ],
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

# ~~~ PROTO RULES ~~~
http_archive(
    name = "rules_proto",
    sha256 = "66bfdf8782796239d3875d37e7de19b1d94301e8972b3cbd2446b332429b4df1",
    strip_prefix = "rules_proto-4.0.0",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/refs/tags/4.0.0.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/refs/tags/4.0.0.tar.gz",
    ],
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

# ~~~ ABSEIL ~~~
http_archive(
    name = "com_google_absl",
    strip_prefix = "abseil-cpp-278e0a071885a22dcd2fd1b5576cc44757299343",
    urls = ["https://github.com/abseil/abseil-cpp/archive/278e0a071885a22dcd2fd1b5576cc44757299343.zip"],
)

# ~~~ GOOGLE PROTOBUFS ~~~
http_archive(
    name = "com_google_protobuf",
    strip_prefix = "abseil-cpp-17b30e96476be70b8773b2b807bab857fd3ceb39",
    urls = ["https://github.com/protocolbuffers/protobuf/archive/17b30e96476be70b8773b2b807bab857fd3ceb39.zip"],
)

# ~~~ GLOG ~~~
http_archive(
    name = "com_github_gflags_gflags",
    sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
    strip_prefix = "gflags-2.2.2",
    urls = ["https://github.com/gflags/gflags/archive/v2.2.2.tar.gz"],
)

http_archive(
    name = "com_github_google_glog",
    sha256 = "21bc744fb7f2fa701ee8db339ded7dce4f975d0d55837a97be7d46e8382dea5a",
    strip_prefix = "glog-0.5.0",
    urls = ["https://github.com/google/glog/archive/v0.5.0.zip"],
)

# ~~~ CONTAINERS ~~~
http_archive(
    name = "io_bazel_rules_docker",
    sha256 = "92779d3445e7bdc79b961030b996cb0c91820ade7ffa7edca69273f404b085d5",
    strip_prefix = "rules_docker-0.20.0",
    urls = ["https://github.com/bazelbuild/rules_docker/releases/download/v0.20.0/rules_docker-v0.20.0.tar.gz"],
)

load(
    "@io_bazel_rules_docker//repositories:repositories.bzl",
    container_repositories = "repositories",
)

container_repositories()

load(
    "@io_bazel_rules_docker//cc:image.bzl",
    _cc_image_repos = "repositories",
)

_cc_image_repos()
