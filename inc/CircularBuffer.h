#include "StandardInc.h"
#define circ_buf_data_type BYTE
#define EXAMPLE_BUFFER_SIZE 32
#define INPUT_DATA_TYPE BYTE
struct circular_buf_t {
    circ_buf_data_type * buffer;
    size_t head;
    size_t tail;
    size_t max; //of the buffer
    bool full;
};

typedef struct circular_buf_t circular_buf_t;
typedef circular_buf_t* cbuf_handle_t;

cbuf_handle_t circular_buf_init(circ_buf_data_type* buffer, size_t size);

void circular_buf_free(cbuf_handle_t me);

void circular_buf_reset(cbuf_handle_t me);

void circular_buf_put(cbuf_handle_t me, circ_buf_data_type data);

bool circular_buf_get(cbuf_handle_t me, BYTE *data);

bool circular_buf_empty(cbuf_handle_t me);

bool circular_buf_full(cbuf_handle_t me);

size_t circular_buf_capacity(cbuf_handle_t me);

size_t circular_buf_size(cbuf_handle_t me);