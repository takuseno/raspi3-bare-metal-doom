#include "stdio.h"
#include "stdlib.h"
#include "string.h"

extern volatile unsigned char __disk_start;
extern volatile unsigned char __disk_end;

void puts(char* s) {
    printf(s);
}

int vsnprintf(char* s, size_t n, const char* fmt, va_list args) {
    // ignore n
    return vsprintf(s, (char*)fmt, args);
}

int fprintf(FILE* stream, const char *fmt, ...) {
    __builtin_va_list args;
    __builtin_va_start(args, fmt);
    int bufsize = vsprintf(stream->ptr, (char*) fmt, args);
    stream->count += bufsize;
    return bufsize;
}

FILE* disk[100];
char* file_names[100];
unsigned file_count = 0;


FILE *fopen(const char *path, const char *mode) {
    static unsigned long cursor_from_end = 0;
    if (strchr(mode, 'r')) {  // read mode
        for (int i = 0; i < file_count; ++i) {
            if (strcmp(file_names[i], path)) {
                FILE* file = disk[i];
                file->ptr = file->base;
                file->mode = 'r';
                return file;
            }
        }
        return NULL;
    } else if (strchr(mode, 'w')) {  // write mode
        for (int i = 0; i < file_count; ++i) {
            if (strcmp(file_names[i], path)) {
                // overwrite
                FILE* file = disk[i];
                file->ptr = file->base;
                file->count = 0;
                file->mode = 'w';
                return file;
            }
        }

        // create new one
        FILE* new_file = disk[file_count];
        cursor_from_end += 1 * 1024 * 1024;
        unsigned long total_size = &__disk_end - &__disk_start;
        if (cursor_from_end > total_size) {
            return NULL;
        }
        new_file->base = (char*)(&__disk_end - cursor_from_end);
        new_file->ptr = new_file->base;
        new_file->bufsiz = 1 * 1024 * 1024;
        new_file->mode = 'w';
        new_file->count = 0;
        file_names[file_count] = (char*) malloc(strlen(path) + 1);
        strcpy(file_names[file_count], path);
        file_count++;
        return new_file;
    }
    return NULL;
}

int fclose(FILE *stream) {
    // do nothing
    return 0;
}

int fseek(FILE *fp, long offset, int origin) {
    if (origin == SEEK_END) {
        fp->ptr = fp->base + fp->count;
    } else if (origin == SEEK_SET) {
        fp->ptr = fp->base;
    }
    if (origin == SEEK_CUR || origin == SEEK_END || origin == SEEK_SET) {
        fp->ptr += offset;
        if (((fp->ptr - fp->base) <= fp->count) && (fp->ptr >= fp->base)) {
            return 0;
        }
    }
    return -1;
}


size_t fwrite(const void *buf, size_t size, size_t n, FILE *fp) {
    char* chbuf = (char*) buf;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < size; ++j) {
            *fp->ptr++ = *chbuf++;
        }
    }
    return size * n;
}

size_t fread(void* ptr, size_t size, size_t n, FILE* fp) {
    char* chbuf = (char*) ptr;
    size_t count = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fp->ptr == fp->base + fp->count) {
                return count;
            }
            *chbuf++ = *fp->ptr++;
            ++count;
        }
    }
    return size * n;
}

long ftell(FILE *fp) {
    return fp->ptr - fp->base;
}
