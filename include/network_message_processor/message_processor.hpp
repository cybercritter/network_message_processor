#pragma once

#include <string>
#include <string_view>

namespace network_message_processor {

class MessageProcessor {
public:
    std::string process(std::string_view message) const;
};

}  // namespace network_message_processor
