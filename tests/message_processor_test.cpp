#include "network_message_processor/message_processor.hpp"

#include <gtest/gtest.h>

namespace network_message_processor {
namespace {

TEST(MessageProcessorTest, PreservesMessage) {
    const MessageProcessor processor;

    EXPECT_EQ(processor.process("hello"), "hello");
}

TEST(MessageProcessorTest, PreservesEmptyMessage) {
    const MessageProcessor processor;

    EXPECT_TRUE(processor.process("").empty());
}

}  // namespace
}  // namespace network_message_processor
