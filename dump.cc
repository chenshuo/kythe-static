#include "storage.pb.h"

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

// copied from DecodeStaticClaimTable in
// kythe/cxx/common/indexing/frontend.cc
void dumpEntries(const char* file)
{
  using namespace google::protobuf::io;
  int fd = open(file, O_RDONLY, S_IREAD | S_IWRITE);
  GOOGLE_CHECK_GE(fd, 0) << "Couldn't open input file " << file;
  FileInputStream file_input_stream(fd);
  //GzipInputStream gzip_input_stream(&file_input_stream);
  CodedInputStream coded_input_stream(&file_input_stream);
  google::protobuf::uint32 byte_size;
  // Silence a warning about input size.
  coded_input_stream.SetTotalBytesLimit(INT_MAX, -1);
  int count = 0;
  while (coded_input_stream.ReadVarint32(&byte_size))
  {
    auto limit = coded_input_stream.PushLimit(byte_size);
    proto::Entry entry;
    GOOGLE_CHECK(entry.ParseFromCodedStream(&coded_input_stream));
    printf("[%d]\n%s\n", count, entry.DebugString().c_str());
    coded_input_stream.PopLimit(limit);
    ++count;
  }
  printf("total %d\n", count);
  close(fd);
}

int main(int argc, char* argv[])
{
  if (argc > 1)
    dumpEntries(argv[1]);
}
