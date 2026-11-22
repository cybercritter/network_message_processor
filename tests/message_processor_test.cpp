#include "message_processor.h"

#include <cstring>
#include <gtest/gtest.h>

TEST (MessageProcessorTest, PreservesMessageWithEmbeddedNull)
{
  const char message[] = { 'h', 'i', '\0', 'x' };
  char output[sizeof message] = {};

  EXPECT_EQ (MESSAGE_PROCESSOR_OK,
             message_processor_process (message, sizeof message, output,
                                        sizeof output));
  EXPECT_EQ (0, std::memcmp (output, message, sizeof message));
}

TEST (MessageProcessorTest, AcceptsEmptyMessage)
{
  EXPECT_EQ (MESSAGE_PROCESSOR_OK,
             message_processor_process (nullptr, 0, nullptr, 0));
}

TEST (MessageProcessorTest, RejectsSmallBufferWithoutWriting)
{
  const char message[] = { 'h', 'i', '\0', 'x' };
  char output[] = { 'z', 'z', 'z', 'z' };

  EXPECT_EQ (MESSAGE_PROCESSOR_BUFFER_TOO_SMALL,
             message_processor_process (message, sizeof message, output, 3));
  EXPECT_EQ (0, std::memcmp (output, "zzzz", sizeof output));
}

TEST (MessageProcessorTest, RejectsNullPointersForNonemptyMessages)
{
  const char message[] = "x";
  char output[1] = {};

  EXPECT_EQ (MESSAGE_PROCESSOR_INVALID_ARGUMENT,
             message_processor_process (nullptr, 1, output, sizeof output));
  EXPECT_EQ (MESSAGE_PROCESSOR_INVALID_ARGUMENT,
             message_processor_process (message, 1, nullptr, 0));
}

TEST (MessageProcessorTest, SupportsOverlappingBuffers)
{
  char buffer[] = "hello";

  EXPECT_EQ (MESSAGE_PROCESSOR_OK,
             message_processor_process (buffer, 4, buffer + 1, 4));
  EXPECT_EQ (0, std::memcmp (buffer, "hhell", 5));
}
