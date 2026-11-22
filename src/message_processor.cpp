#include "network_message_processor/message_processor.hpp"

namespace network_message_processor {

std::string MessageProcessor::process(std::string_view message) const {
    return std::string(message);
}

}  // namespace network_message_processor
