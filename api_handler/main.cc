#include "absl/flags/flag.h"
#include "glog/logging.h"
#include "grpc++/security/server_credentials.h"
#include "grpc++/server_builder.h"
#include "proto/web.grpc.pb.h"
#include "proto/web.pb.h"

ABSL_FLAG(std::string, grpc_server_address, "0.0.0.0:50051",
          "Address and port to bind to the server.");

using ::aandevski::blog::proto::BlogService;

class BlogServiceImpl : public BlogService::Service {};

int main(int argc, char **argv) {
  ::google::InitGoogleLogging(argv[0]);
  std::string server_address = absl::GetFlag(FLAGS_grpc_server_address);

  BlogServiceImpl service;
  ::grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<::grpc::Server> server(builder.BuildAndStart());
  LOG(INFO) << "Server listening on " << server_address;
  server->Wait();
  return 0;
}
