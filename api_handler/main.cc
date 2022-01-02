#include "absl/flags/flag.h"
#include "absl/strings/str_cat.h"
#include "glog/logging.h"
#include "grpc++/security/server_credentials.h"
#include "grpc++/server_builder.h"
#include "proto/web.grpc.pb.h"
#include "proto/web.pb.h"

ABSL_FLAG(std::string, grpc_server_port, "", "Port to listen to.");

namespace {
using ::aandevski::blog::proto::BlogService;

constexpr char kPortEnvVarName[] = "PORT";
constexpr char kAddressBind[] = "dns:///[::]:";
constexpr char kDefaultPort[] = "8080";

class BlogServiceImpl : public BlogService::Service {};

std::string GetListeningAddressAndPort() {
  if (const std::string &port_str = absl::GetFlag(FLAGS_grpc_server_port);
      !port_str.empty()) {
    return absl::StrCat(kAddressBind, port_str);
  }
  if (const char *port = std::getenv(kPortEnvVarName); port != nullptr) {
    return absl::StrCat(kAddressBind, port);
  }
  return absl::StrCat(kAddressBind, kDefaultPort);
}

} // namespace

int main(int argc, char **argv) {
  ::google::InitGoogleLogging(argv[0]);
  std::string server_address = GetListeningAddressAndPort();

  BlogServiceImpl service;
  ::grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<::grpc::Server> server(builder.BuildAndStart());
  LOG(INFO) << "Server listening on " << server_address;
  server->Wait();
  return 0;
}
