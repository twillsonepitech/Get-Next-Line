#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int fd = -1;

void open_file(const char *file)
{
    fd = open(file, O_RDONLY);
    cr_redirect_stdout();
}

void close_file(void)
{
    if (fd != -1)
        close(fd);
}

Test(get_next_line_test_read_line_ptr, read_line)
{
    open_file("tests/data.txt");
    char *expected = "Confidence is so overrated.";
    char *got = get_next_line(fd);
    cr_assert_str_eq(got, expected);
    close_file();
}

Test(get_next_line_all_file, read_file)
{
    const char expected[] = "/**\n"
                            " * @file get_next_line.h\n"
                            " * @author Thomas Willson (thomas.willson@epitech.eu)\n"
                            " * @brief Get next line header, contain a MACRO to know\n"
                            " * how many bytes to read per line.\n"
                            " * @version 0.1\n"
                            " * @date 2022-08-08\n"
                            " * \n"
                            " * @copyright Copyright (c) 2022\n"
                            " * \n"
                            " */\n"
                            "#ifndef GET_NEXT_LINE_H_\n"
                            "# define GET_NEXT_LINE_H_\n\n"
                            "#if !defined(READ_SIZE)\n"
                            "# define READ_SIZE      (100)\n"
                            "#endif // READ_SIZE\n\n"
                            "#define INIT_INTEGER        (0)\n"
                            "#define INIT_POINTER        (NULL)\n"
                            "#define FUNCTION_SUCCESS    (0)\n"
                            "#define FUNCTION_FAILURE    (-1)\n"
                            "#define EXIT_EOF            (1)\n"
                            "#define READ_ZERO           (0)\n"
                            "#define READ_FAIL           (-1)\n"
                            "#define PUT_ERROR(err)      fprintf(stderr, \"Error: [%s].\\n\", err)\n\n"
                            "#endif /* !GET_NEXT_LINE_H_ */\n";

    open_file("tests/file.txt");
    char *got = (char *)malloc(sizeof(char) * (strlen(expected) + 1));
    if (!got)
        cr_log_error("malloc() error");
    int it = 0;
    while (true)
    {
        char *s = get_next_line(fd);
        if (s == NULL)
            break;
        for (size_t i = 0; i < strlen(s); i++) {
            got[it++] = s[i];
        }
        free(s);
    }
    got[it] = '\0';
    cr_assert_str_eq(got, expected);
    free(got);
    close_file();
}