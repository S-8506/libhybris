/*
 * Copyright (C) 2013 Simon Busch <morphis@gravedo.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fcntl.h>
#include <sys/stat.h>

#include <ui/GraphicBuffer.h>
#include <ui/GraphicBufferMapper.h>
#include <ui/GraphicBufferAllocator.h>

#include <hybris/ui/ui_compatibility_layer.h>

struct graphic_buffer
{
    android::GraphicBuffer *self;
};

struct graphic_buffer* graphic_buffer_new(void)
{
    struct graphic_buffer *buffer = NULL;

    buffer = (struct graphic_buffer*) malloc(sizeof(struct graphic_buffer));
    if (!buffer)
        return NULL;

    buffer->self = new android::GraphicBuffer();

    return buffer;
}

struct graphic_buffer* graphic_buffer_new_sized(uint32_t w, uint32_t h,
                                                int32_t format, uint32_t usage)
{
    struct graphic_buffer *buffer = NULL;

    buffer = (struct graphic_buffer*) malloc(sizeof(struct graphic_buffer));
    if (!buffer)
        return NULL;

    buffer->self = new android::GraphicBuffer(w, h, format, usage);

    return buffer;
}

struct graphic_buffer* graphic_buffer_new_existing(uint32_t w, uint32_t h,
                                              int32_t format, uint32_t usage,
                                              uint32_t stride, void *handle,
                                              bool keepOwnership)
{
    struct graphic_buffer *buffer = NULL;

    buffer = (struct graphic_buffer*) malloc(sizeof(struct graphic_buffer));
    if (!buffer)
        return NULL;

#if ANDROID_VERSION_MAJOR>=8
    buffer->self = new android::GraphicBuffer(w, h, format, 1, usage, stride, (native_handle_t*) handle, keepOwnership);
#else
    buffer->self = new android::GraphicBuffer(w, h, format, usage, stride, (native_handle_t*) handle, keepOwnership);
#endif

    return buffer;

}

void graphic_buffer_free(struct graphic_buffer *buffer)
{
    if (!buffer)
        return;

    free(buffer);
}

uint32_t graphic_buffer_get_width(struct graphic_buffer *buffer)
{
    return buffer->self->getWidth();
}

uint32_t graphic_buffer_get_height(struct graphic_buffer *buffer)
{
    return buffer->self->getHeight();
}

uint32_t graphic_buffer_get_stride(struct graphic_buffer *buffer)
{
    return buffer->self->getStride();
}

uint32_t graphic_buffer_get_usage(struct graphic_buffer *buffer)
{
    return buffer->self->getUsage();
}

int32_t graphic_buffer_get_pixel_format(struct graphic_buffer *buffer)
{
    return buffer->self->getPixelFormat();
}

uint32_t graphic_buffer_reallocate(struct graphic_buffer *buffer, uint32_t w,
                                   uint32_t h, int32_t f, uint32_t usage)
{
#if ANDROID_VERSION_MAJOR>=8
    return buffer->self->reallocate(w, h, f, 1, usage);
#else
    return buffer->self->reallocate(w, h, f, usage);
#endif
}

uint32_t graphic_buffer_lock(struct graphic_buffer *buffer, uint32_t usage, void **vaddr)
{
    return buffer->self->lock(usage, vaddr);
}

uint32_t graphic_buffer_unlock(struct graphic_buffer *buffer)
{
    return buffer->self->unlock();
}

void* graphic_buffer_get_native_buffer(struct graphic_buffer *buffer)
{
    return buffer->self->getNativeBuffer();
}

#if ANDROID_VERSION_MAJOR==4 && ANDROID_VERSION_MINOR<=3
void graphic_buffer_set_index(struct graphic_buffer *buffer, int index)
{
    return buffer->self->setIndex(index);
}

int graphic_buffer_get_index(struct graphic_buffer *buffer)
{
    return buffer->self->getIndex();
}
#endif

int graphic_buffer_init_check(struct graphic_buffer *buffer)
{
    return buffer->self->initCheck();
}
