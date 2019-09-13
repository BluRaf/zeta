src := $(wildcard src/*.c)
src += $(wildcard deps/log.c/src/*.c)
obj := $(src:.c=.o)
bin := game

CFLAGS := -g -Ideps/log.c/src
LDFLAGS := -lallegro -lallegro_image

# list the libfoo rule as a dependency
$(bin): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) $(bin)

# this is the new rule for recursively building libfoo
#.PHONY: libfoo
#libfoo:
#	$(MAKE) -C libs/foo
