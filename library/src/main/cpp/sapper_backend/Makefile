TARGETS_LIB := cell/cell row/row mins_field/mins_field

OBJS_LIB := cell/cell.o row/row.o mins_field/mins_field.o

TARGETS_TESTS := test_mins_field_1

OBJS_TESTS := test/mins_field/test1.o

TARGETS := $(TARGETS_LIB) $(TARGETS_TESTS)

OBJS := $(OBJS_LIB) $(OBJS_TESTS)

CFLAGS := -I./ -fsanitize=address -g

librery.a: $(OBJS_LIB)
	$(AR) rcs librery.a $(OBJS_LIB)

test/mins_field/test1: test/mins_field/test1.o
	$(CC) $(CFLAGS) $< librery.a -o $@

test_mins_field_1: librery.a test/mins_field/test1 

all: $(TARGETS)

clean: 
	rm -f $(OBJS) $(TARGETS)


.PHONY: clean all
