# Example of Parsing Long Options with `getopt_long`

## Functions

### `getopt_long`

`c = getopt_long (argc, argv, "vti:", long_options, &option_index);`

`vti: ` means `-v` is single option while `-i` cannot show up alone, it should be like `-i FLAG_AFTER`, and in this program if we run some commands in the terminal:

```ruby
$make op
g++ -std=c++11 -O3 -o getop_test getop_test.cpp
$make test
./getop_test --implementation BINARY
option -i with value `BINARY'
verbose flag is disabled
./getop_test -i BINARY
option -i with value `BINARY'
verbose flag is disabled
./getop_test --verbose -i UNSORTED
option -i with value `UNSORTED'
verbose flag is set
./getop_test --v -i UNSORTED
option -i with value `UNSORTED'
verbose flag is set
./getop_test --verbose -i FIBONACCI
option -i with value `FIBONACCI'
verbose flag is set
./getop_test -test -i FIBONACCI
option -t
getop_test: invalid option -- e
getop_test: invalid option -- s
option -t
option -i with value `FIBONACCI'
verbose flag is disabled
```





## Reference

### get_long_opt_test.cpp

```cpp
#include <iostream>
#include <getopt.h>

using namespace std;

/* Flag set by ‘--verbose’. */
static int verbose_flag;

int main (int argc, char **argv)
{
  int c;
  string argument;
  while (1)
    {
      static struct option long_options[] =
        {
          /* These options set a flag. */
          {"verbose", no_argument,       &verbose_flag, 1},
          {"brief",   no_argument,       &verbose_flag, 0},
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"test",     			no_argument,       0, 't'},
          {"implementation",  	required_argument,       0, 'i'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "vti:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 't':
          printf ("option -t\n");
          break;

        case 'i':
          printf ("option -i with value `%s'\n", optarg);
          argument = optarg;
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

  /* Instead of reporting ‘--verbose’
     and ‘--brief’ as they are encountered,
     we report the final status resulting from them. */
  if (verbose_flag)
    puts ("verbose flag is set");
  else puts("verbose flag is disabled");

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }

  exit (0);
}
```



### Makefile

```ruby
op: getop_test.cpp
	g++ -std=c++11 -O3 -o getop_test getop_test.cpp

test:
	./getop_test --implementation BINARY
	./getop_test -i BINARY
	./getop_test --verbose -i UNSORTED
	./getop_test --v -i UNSORTED
	./getop_test --verbose -i FIBONACCI
	./getop_test -test -i BINARY
```

