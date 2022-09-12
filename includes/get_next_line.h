/**
 * @file get_next_line.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Get next line header, contain a MACRO to know
 * how many bytes to read per line.
 * @version 0.1
 * @date 2022-08-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

#if !defined(READ_SIZE)
# define READ_SIZE      (400)
#endif // READ_SIZE

#define INIT_INTEGER        (0)
#define INIT_POINTER        (NULL)
#define SUCCESS             (0)
#define FAILURE             (-1)
#define FUNCTION_SUCCESS    (0)
#define FUNCTION_FAILURE    (-1)
#define EXIT_EOF            (1)
#define READ_ZERO           (0)
#define READ_FAIL           (-1)
#define PUT_ERROR(err)      fprintf(stderr, "Error: [%s].\n", err)
#define CONTAINS_CHAR(s, __c, ret)   \
  (__extension__                  \
    ({                      \
      ret = FAILURE;          \
      const char *__old = (s); \
      while (*__old) { if (*__old == __c) ret = SUCCESS; __old++; }  \
      ret;                 \
    })               \
  )                   \

/**
 * @brief Free all arguments passed through va args.
 * 
 * @param size_args Number of arguments passed in parameter
 * @param ... Arguments to be freed
 */
void free_args_va_arguments(const int size_args, ...);

/**
 * @brief Joins strings, create a tmp pointer that will be filled by
 *      the *__dest and __src, then we dereference __dest and change
 *      the content of it by tmp pointer.
 * 
 * @param __dest Destination pointer
 * @param __src Source pointer
 * @return int 
 */
int join(char **__restrict __dest, const char *__restrict __src);

/**
 * @brief Loop through lineptr from start `index_start_lineptr` until
 *      we reach end.
 * 
 * @param lineptr Loop through lineptr
 * @param index_start_lineptr Start index
 * @param end End char
 * @return int 
 */
int number_iteration_until_end(const char *__restrict lineptr, size_t index_start_lineptr, const char end);

/**
 * @brief Fill __src into __dest, as __dest is a dbl ptr, we dereference it to access
 *      the real pointer.
 * 
 * @param __dest Destination pointer
 * @param __src Source pointer
 * @param index_start_src Starting index for Source pointer
 * @param end Loop into __src until we reach char end
 * @return int 
 */
int init_buffer(char **__restrict __dest, const char *__restrict __src, size_t index_start_src, const char end);

/**
 * @brief Init right buffer and fill it into ptr_container, init left buffer
 *      and fill it into ptr_return.
 * 
 * @param left_buffer Left buffer
 * @param right_buffer Right buffer
 * @param ptr_container Static buffer to be filled
 * @param ptr_return Return pointer value
 * @return int 
 */
int join_return_value(char *__restrict left_buffer, char *__restrict right_buffer,
        char **__restrict ptr_container, char **__restrict ptr_return);

/**
 * @brief Manage buffer, check if buffer contains end of line and split buffer
 *      before EOL in ptr return and after EOL into ptr container.
 * 
 * @param buffer Read buffer
 * @param ptr_container Static buffer to be filled
 * @param ptr_return Return pointer value
 * @return int 
 */
int manage_buffer(char *__restrict buffer, char **__restrict ptr_container, char **__restrict ptr_return);

/**
 * @brief Read line with file descriptor and manage return pointer.
 * 
 * @param fd File descriptor
 * @param ptr_container Static buffer to be filled
 * @param ptr_return Return pointer value
 * @return int 
 */
int read_line_into_buffer(const int fd, char **__restrict ptr_container, char **__restrict ptr_return);

/**
 * @brief Get the next line object.
 * 
 * @param fd File descriptor
 * @return char* 
 */
char *get_next_line(const int fd);

#endif /* !GET_NEXT_LINE_H_ */
