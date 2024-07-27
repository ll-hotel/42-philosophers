CC = cc

INC_DIR = include
SRC_DIR = src
OBJ_DIR = .obj

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I${INC_DIR}
DFLAGS = -MMD -MP
LFLAGS = -lpthread

ifneq ("${DEBUG}", "")
	CFLAGS += ${DEBUG}
endif

OBJS = $(patsubst %.c,${OBJ_DIR}/%.o, \
	   main.c \
	   philo.c \
	   philo_fork.c \
	   philo_routine.c \
	   start_philosophers.c \
	   table.c \
	   utils.c \
	   )

DEPS = ${OBJS:.o=.d}

NAME = philo

.PHONY: all
all: ${NAME}

-include ${DEPS}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${IFLAGS} ${DFLAGS} -o $@ ${OBJS} ${LFLAGS}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c | ${OBJ_DIR}
	${CC} ${CFLAGS} ${IFLAGS} ${DFLAGS} -o $@ -c $<

${OBJ_DIR}:
	mkdir -p $(sort $(dir ${OBJS}))

.PHONY: clean
clean:
	rm -rf ${OBJ_DIR}

.PHONY: fclean
fclean: clean
	rm -f ${NAME}

.SILENT: re
.PHONY: re
re: fclean
	make --no-print-directory
