#include "message_processor.h"

#include <safeclib/safe_mem_lib.h>

enum message_processor_result
message_processor_process (const void *message, size_t message_size,
                           void *output, size_t output_size)
{
  if (message_size == 0)
    {
      return MESSAGE_PROCESSOR_OK;
    }
  if (message == NULL || output == NULL)
    {
      return MESSAGE_PROCESSOR_INVALID_ARGUMENT;
    }

  if (output_size < message_size)
    {
      return MESSAGE_PROCESSOR_BUFFER_TOO_SMALL;
    }

  int status = memmove_s (output, output_size, message, message_size);

  if (status != 0)
    {
      return MESSAGE_PROCESSOR_MEMMOVE_FAILED;
    }
  
  return MESSAGE_PROCESSOR_OK;
}
