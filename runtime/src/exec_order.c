/* zocle — Z OpenCL Environment
 * Copyright (C) 2009 Wei Hu <wei.hu.tw@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <cl.h>

#include <osal.h>
#include <cl_internal.h>

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueMarker(cl_command_queue    command_queue,
                cl_event *          event) CL_API_SUFFIX__VERSION_1_0 {
  cl_command cmd = NULL;
  cl_int return_code = CL_SUCCESS;
  cl_event event_allocated = NULL;
  
  if (NULL == command_queue) {
    return_code = CL_INVALID_COMMAND_QUEUE;
    goto error;
  }
  if (NULL == event) {
    return_code = CL_INVALID_VALUE;
    goto error;
  }
  
  cmd = clOsalCalloc(sizeof(struct _cl_command));
  if (NULL == cmd) {
    return_code = CL_OUT_OF_HOST_MEMORY;
    goto error;
  }
  cmd->type = CL_COMMAND_MARKER;
  
  cvector_cl_command_push_back(command_queue->commands, cmd);
  cmd->execution_status = CL_QUEUED;
  
  event_allocated = clOsalCalloc(sizeof(struct _cl_event));
  if (NULL == event_allocated) {
    return_code = CL_OUT_OF_HOST_MEMORY;
    goto error;
  }
  event_allocated->command = cmd;
  (*event) = event_allocated;
  goto success;
  
 error:
  if (cmd != NULL) {
    clOsalFree(cmd);
    cmd = NULL;
  }
  if (event_allocated != NULL) {
    clOsalFree(event_allocated);
    event_allocated = NULL;
  }
  
 success:
  return return_code;
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueWaitForEvents(cl_command_queue command_queue,
                       cl_uint          num_events,
                       const cl_event * event_list) CL_API_SUFFIX__VERSION_1_0 {
  cl_command cmd = NULL;
  cl_int return_code = CL_SUCCESS;
  
  cmd = clOsalCalloc(sizeof(struct _cl_command));
  if (NULL == cmd) {
    return_code = CL_OUT_OF_HOST_MEMORY;
    goto error;
  }
  cmd->type = CL_COMMAND_WAIT_FOR_EVENTS;
  
  cvector_cl_command_push_back(command_queue->commands, cmd);
  cmd->execution_status = CL_QUEUED;
  goto success;
  
 error:
  if (cmd != NULL) {
    clOsalFree(cmd);
    cmd = NULL;
  }
  
 success:
  return return_code;
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueBarrier(cl_command_queue command_queue) CL_API_SUFFIX__VERSION_1_0 {
  cl_command cmd = NULL;
  cl_int return_code = CL_SUCCESS;
  
  cmd = clOsalCalloc(sizeof(struct _cl_command));
  if (NULL == cmd) {
    return_code = CL_OUT_OF_HOST_MEMORY;
    goto error;
  }
  cmd->type = CL_COMMAND_BARRIER;
  
  cvector_cl_command_push_back(command_queue->commands, cmd);
  cmd->execution_status = CL_QUEUED;
  goto success;
  
 error:
  if (cmd != NULL) {
    clOsalFree(cmd);
    cmd = NULL;
  }
  
 success:
  return return_code;
}

CL_API_ENTRY cl_int CL_API_CALL
clFlush(cl_command_queue command_queue) CL_API_SUFFIX__VERSION_1_0 {
  /* TODO: implement this function */
  return CL_SUCCESS;
}

CL_API_ENTRY cl_int CL_API_CALL
clFinish(cl_command_queue command_queue) CL_API_SUFFIX__VERSION_1_0 {
  /* TODO: implement this function */
  return CL_SUCCESS;
}
