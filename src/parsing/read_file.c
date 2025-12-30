#include "../../includes/cub3d.h"

static int count_lines(char *filename)
{
    int     fd;
    int     count;
    char    buffer[1];

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (-1);
    count = 0;
    while (read(fd, buffer, 1) > 0)
    {
        if (buffer[0] == '\n')
            count++;
    }
    close(fd);
    return (count + 1);
}

static char *read_line(int fd)
{
    char    *line;
    char    buffer[1];
    int     i;
    int     ret;

    line = malloc(1000);
    if (!line)
        return (NULL);
    i = 0;
    while ((ret = read(fd, buffer, 1)) > 0)
    {
        if (buffer[0] == '\n')
            break;
        line[i++] = buffer[0];
    }
    line[i] = '\0';
    if (ret == 0 && i == 0)
    {
        free(line);
        return (NULL);
    }
    return (line);
}

char **read_file(char *filename)
{
    int     fd;
    char    **lines;
    int     i;
    int     total_lines;

    total_lines = count_lines(filename);
    if (total_lines < 0)
        error_exit("Cannot open file");
    lines = malloc(sizeof(char *) * (total_lines + 1));
    if (!lines)
        error_exit("Malloc failed");
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit("Cannot open file");
    i = 0;
    while (i < total_lines)
    {
        lines[i] = read_line(fd);
        if (!lines[i])
            break;
        i++;
    }
    lines[i] = NULL;
    close(fd);
    return (lines);
}
