/**
 * @file get_next_line.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Get next line project, see `getline` for more
 * informations about the get_next_line.
 * @version 0.1
 * @date 2022-08-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdarg.h>
#include "get_next_line.h"

void __free_vl(int size_args, ...)
{
    va_list ap;
    int __i = 0;
    void *ptr;

    va_start(ap, size_args);
    while (__i < size_args)
    {
        ptr = va_arg(ap, void *);
        if (NULL == ptr)
        {
            break;
        }
        free(ptr);
        __i++;
    }
    va_end(ap);
}

int contain_end_of_line(char *ptr)
{
    int index_per_iteration;

    index_per_iteration = INIT_INTEGER;
    while (ptr[index_per_iteration] != '\0')
    {
        if (ptr[index_per_iteration] == '\n')
        {
            return FUNCTION_SUCCESS;
        }
        index_per_iteration++;
    }
    return FUNCTION_FAILURE;
}

int join(char **dest, const char *src)
{
    size_t dest_size = NULL == *dest ? 0 : strlen(*dest);
    size_t source_size = NULL == src ? 0 : strlen(src);
    char *tempr;
    int index_per_iteration;
    int number_of_index_fill;

    tempr = (char *)malloc(sizeof(char) * (source_size + dest_size + 1));
    if (NULL == tempr)
    {
        PUT_ERROR(strerror(errno));
        return FUNCTION_FAILURE;
    }
    number_of_index_fill = INIT_INTEGER;
    index_per_iteration = INIT_INTEGER;
    while (index_per_iteration < (int)(dest_size))
    {
        tempr[number_of_index_fill] = (*dest)[index_per_iteration];
        number_of_index_fill++;
        index_per_iteration++;
    }
    index_per_iteration = INIT_INTEGER;
    while (index_per_iteration < (int)(source_size))
    {
        tempr[number_of_index_fill] = src[index_per_iteration];
        number_of_index_fill++;
        index_per_iteration++;
    }
    tempr[number_of_index_fill] = '\0';
    free(*dest);
    *dest = tempr;
    return FUNCTION_SUCCESS;
}

int get_number_iter_before_end(const char *lineptr, size_t index_start_lineptr, const char end)
{
    int index_per_iteration;

    index_per_iteration = INIT_INTEGER;
    while (lineptr[index_start_lineptr] != end)
    {
        index_start_lineptr++;
        index_per_iteration++;
    }
    return index_per_iteration;
}

int init_buffer(char **dest, const char *src, size_t index_start_src, const char end)
{
    int index_per_iteration;

    *dest = (char *)malloc(sizeof(char) * (get_number_iter_before_end(src, index_start_src, end) + 1));
    if (NULL == *dest)
    {
        PUT_ERROR(strerror(errno));
        return FUNCTION_FAILURE;
    }
    index_per_iteration = INIT_INTEGER;
    while (src[index_start_src] != end)
    {
        (*dest)[index_per_iteration] = src[index_start_src];
        index_start_src++;
        index_per_iteration++;
    }
    (*dest)[index_per_iteration] = '\0';
    return FUNCTION_SUCCESS;
}

int manage_container_and_return(char *left_buffer, char *right_buffer, char **ptr_container, char **ptr_return)
{
    int return_from_function;

    return_from_function = join(ptr_return, *ptr_container);
    if (FUNCTION_FAILURE == return_from_function)
    {
        return FUNCTION_FAILURE;
    }
    return_from_function = join(ptr_return, left_buffer);
    if (FUNCTION_FAILURE == return_from_function)
    {
        return FUNCTION_FAILURE;
    }
    if (*ptr_container != NULL)
    {
        free(*ptr_container);
        *ptr_container = NULL;
    }
    return_from_function = join(ptr_container, right_buffer);
    if (FUNCTION_FAILURE == return_from_function)
    {
        return FUNCTION_FAILURE;
    }
    return FUNCTION_SUCCESS;
}

int manage_end_of_line(char *buffer, char **ptr_container, char **ptr_return)
{
    char *left_buffer;
    char *right_buffer;
    int return_from_function;

    return_from_function = init_buffer(&left_buffer, buffer, INIT_INTEGER, '\n');
    if (FUNCTION_FAILURE == return_from_function)
    {
        return FUNCTION_FAILURE;
    }
    return_from_function = init_buffer(&right_buffer, buffer, strlen(left_buffer), '\0');
    if (FUNCTION_FAILURE == return_from_function)
    {
        __free_vl(1, left_buffer);
        return FUNCTION_FAILURE;
    }
    return_from_function = manage_container_and_return(left_buffer, right_buffer, ptr_container, ptr_return);
    if (FUNCTION_FAILURE == return_from_function)
    {
        __free_vl(2, left_buffer, right_buffer);
        return FUNCTION_FAILURE;
    }
    __free_vl(2, left_buffer, right_buffer);
    return FUNCTION_SUCCESS;
}

int read_line_into_buffer(const int fd, char **ptr_container, char **ptr_return)
{
    char *ptr_read;
    ssize_t readline;
    int return_from_function;

    while (true)
    {
        ptr_read = (char *)malloc(sizeof(char) * (READ_SIZE + 1));
        if (NULL == ptr_read)
        {
            PUT_ERROR(strerror(errno));
            return FUNCTION_FAILURE;
        }
        readline = read(fd, ptr_read, READ_SIZE);
        if (FUNCTION_FAILURE == readline)
        {
            PUT_ERROR(strerror(errno));
            __free_vl(1, ptr_read);
            return FUNCTION_FAILURE;
        }
        else
        {
            ptr_read[readline] = '\0';
        }
        return_from_function = contain_end_of_line(ptr_read);
        if (FUNCTION_SUCCESS == return_from_function)
        {
            return_from_function = manage_end_of_line(ptr_read, ptr_container, ptr_return);
            if (FUNCTION_FAILURE == return_from_function)
            {
                __free_vl(1, ptr_read);
                return FUNCTION_FAILURE;
            }
            else
            {
                break;
            }
        }
        else
        {
            return_from_function = join(ptr_return, *ptr_container);
            if (FUNCTION_FAILURE == return_from_function)
            {
                __free_vl(1, ptr_read);
                return FUNCTION_FAILURE;
            }
            else
            {
                __free_vl(1, *ptr_container);
                *ptr_container = NULL;
            }
            return_from_function = join(ptr_return, ptr_read);
            if (FUNCTION_FAILURE == return_from_function)
            {
                __free_vl(1, ptr_read);
                return FUNCTION_FAILURE;
            }
            else
            {
                __free_vl(1, ptr_read);
            }
            if (READ_ZERO == readline)
            {
                return EXIT_EOF;
            }
            else if (READ_SIZE == readline)
            {
                continue;
            }
            else
            {
                break;
            }
        }
    }
    __free_vl(1, ptr_read);
    return FUNCTION_SUCCESS;
}

char *get_next_line(const int fd)
{
    static char *ptr_container = NULL;
    char *ptr_return = NULL;
    int return_from_function;

    return_from_function = read_line_into_buffer(fd, &ptr_container, &ptr_return);
    if (FUNCTION_FAILURE == return_from_function || EXIT_EOF == return_from_function)
    {
        __free_vl(2, ptr_container, ptr_return);
        return NULL;
    }
    return ptr_return;
}
