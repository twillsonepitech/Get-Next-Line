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
# define READ_SIZE      (100)
#endif // READ_SIZE

#define INIT_INTEGER        (0)
#define INIT_POINTER        (NULL)
#define FUNCTION_SUCCESS    (0)
#define FUNCTION_FAILURE    (-1)
#define EXIT_EOF            (1)
#define READ_ZERO           (0)
#define READ_FAIL           (-1)
#define PUT_ERROR(err)      fprintf(stderr, "Error: [%s].\n", err)

char *get_next_line(const int fd);

#endif /* !GET_NEXT_LINE_H_ */
