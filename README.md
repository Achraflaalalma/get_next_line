<h1 align="center">Get Next Line</h1>
<h2>Summary</h2>
<p>
  Get Next Line is a function that reads a file line by line. It is a function
  that is part of the 42 curriculum and is used in many projects to read files.
  The function is able to read multiple file descriptors at the same time and is
  able to read files with different buffer sizes.
</p>

<h2>Features</h2>
<ul>
  <li>
    Reads from any file <strong>descriptor.</strong>
  </li>
  <li>
    Handles multiple file <strong>descriptors</strong> at the same time.
  </li>
  <li>
    <strong>Returns</strong> each line terminated by a newline character, except for the last line if it doesn't end with a newline.
  </li>
</ul>
<h2>Usage</h2>
<h3>function Prototype</h3>
<p>
	The function prototype is as follows:
</p>

```C
int get_next_line(int fd, char **line);
```

<h3>Parameters</h3>	
	<lu>
		<li>
			<code>fd</code> - The file descriptor that will be used to read.
		</li>
		<li>
			<code>line</code> - The address of a pointer to a character that will be used to save the line read from the file descriptor.
		</li>
	</lu>
<h3>Return Value</h3>
<ul>
	<li>
		The function returns 1 if a line has been read.
	</li>
	<li>
		The function returns 0 if the end of file has been reached.
	</li>
	<li>
		The function returns -1 if an error occurs.
	</li>
</ul>
<h3>Example</h3>
<p>
	The following example demonstrates how to use the get_next_line function to read a file.
</p>

<pre>
	<code>
	#include "get_next_line.h"
	#include <fcntl.h>
	#include <stdio.h>

	int main(void)
	{
		int fd;
		char *line;
		int ret;

		fd = open("file.txt", O_RDONLY);
		if (fd == -1)
			return (1);
		ret = get_next_line(fd, &line);
		while (ret > 0)
		{
			printf("%s\n", line);
			free(line);
			ret = get_next_line(fd, &line);
		}
		if (ret == -1)
			return (1);
		printf("%s\n", line);
		free(line);
		close(fd);
		return (0);
	}
	</code>
</pre>

<h2>Compiling</h2>

```C
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1024 get_next_line.c get_next_line_utils.c your_program.c -o your_program
```

<h2>Bonus Part</h2>

<p>Your <code>get_next_line()</code> can manage multiple file descriptors at the same time.
For example, if you can read from the file descriptors 3, 4 and 5, you should be
able to read from a different fd per call without losing the reading thread of each
file descriptor or returning a line from another fd.
It means that you should be able to call get_next_line() to read from fd 3, then
fd 4, then 5, then once again 3, once again 4, and so forth.</p>

<pre><code>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

void read_from_fd(int fd, const char *label) {
    char *line;
    int result;
    while ((result = get_next_line(fd, &line)) > 0) {
        printf("%s: %s\n", label, line);
        free(line);
    }
    if (result == -1) perror("Error reading file");
}

int main(void) {
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    int fd3 = open("file3.txt", O_RDONLY);
    
    if (fd1 == -1 || fd2 == -1 || fd3 == -1) {
        perror("Error opening files");
        return 1;
    }

    read_from_fd(fd1, "File 1");
    read_from_fd(fd2, "File 2");
    read_from_fd(fd3, "File 3");

    close(fd1);
    close(fd2);
    close(fd3);
    return 0;
}

</code></pre>

<h2>Additional Notes</h2>
<ul>
	<li>
		Ensure you handle memory correctly to avoid leaks.
	</li>
	<li>
		The buffer size can be adjusted according to your needs by defining BUFFER_SIZE
	</li>
</ul>
