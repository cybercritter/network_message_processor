#ifndef NETWORK_MESSAGE_PROCESSOR_MESSAGE_PROCESSOR_H
#define NETWORK_MESSAGE_PROCESSOR_MESSAGE_PROCESSOR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

  enum message_processor_result
  {
    MESSAGE_PROCESSOR_OK,
    MESSAGE_PROCESSOR_INVALID_ARGUMENT,
    MESSAGE_PROCESSOR_BUFFER_TOO_SMALL,
    MESSAGE_PROCESSOR_MEMMOVE_FAILED,
  };

  enum message_processor_result message_processor_process (const void *message,
                                                           size_t message_size,
                                                           void *output,
                                                           size_t output_size);

#ifdef __cplusplus
}
#endif

#endif
