#include "../inc/CircularBuffer.h"

cbuf_handle_t circular_buf_init(circ_buf_data_type* buffer, size_t size)
{
    assert(buffer && size);

    cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));
    assert(cbuf);

    cbuf->buffer = buffer;
    cbuf->max = size;
    circular_buf_reset(cbuf);

    assert(circular_buf_empty(cbuf));

    return cbuf;
}

void circular_buf_reset(cbuf_handle_t handle)
{
    assert(handle);

    handle->head = 0;
    handle->tail = 0;
    handle->full = false;
}

void circular_buf_free(cbuf_handle_t handle)
{
    assert(handle);
    free(handle);
}

bool circular_buf_full(cbuf_handle_t handle)
{
    assert(handle);

    return handle->full;
}

bool circular_buf_empty(cbuf_handle_t handle)
{
    assert(handle);

    return (!handle->full && (handle->head == handle->tail));
}

size_t circular_buf_capacity(cbuf_handle_t handle)
{
    assert(handle);

    return handle->max;
}

size_t circular_buf_size(cbuf_handle_t handle)
{
    assert(handle);

    size_t size = handle->max;

    if(!handle->full)
    {
        if(handle->head >= handle->tail)
        {
            size = (handle->head - handle->tail);
        }
        else
        {
            size = (handle->max + handle->head - handle->tail);
        }
    }

    return size;
}

static void advance_pointer(cbuf_handle_t handle)
{
    assert(handle);

    handle->head = handle->head+1;

    if (handle->head  == handle->max)
    {
        handle->head = 0;
    }

    handle->full = (handle->head == handle->tail);
}

static void retreat_pointer(cbuf_handle_t handle)
{
    assert(handle);

    handle->full = false;
    if (++(handle->tail) == handle->max)
    {
        handle->tail = 0;
    }
}

void circular_buf_put(cbuf_handle_t handle, circ_buf_data_type data)
{
    assert(handle && handle->buffer);

    handle->buffer[handle->head] = data;

    advance_pointer(handle);
}

int circular_buf_get(cbuf_handle_t handle, circ_buf_data_type * data)
{
    assert(handle && data && handle->buffer);

    int r = -1;

    if(!circular_buf_empty(handle))
    {
        *data = handle->buffer[handle->tail];
        retreat_pointer(handle);

        r = 0;
    }

    return r;
}

