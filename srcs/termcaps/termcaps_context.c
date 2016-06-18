#include "shell.h"

/*
** Put the terminal in POSIX raw mode
**
**		|c_iflag|
**
** IGNBRK : If this bit is set, BREAK conditions are ignored.
**		A break condition is defined in the context of asynchronous serial data transmission
**		as a series of zero-value bits longer than a single byte.
**
** BRKINT : If IGNBRK is set, a BREAK is ignored. If it is not set but BRKINT is set,
**		then a BREAK causes the input and output queues to be flushed, and if the terminal is
**		the controlling terminal of a foreground process group, it will cause a SIGINT to be sent
**		to this foreground process group. When neither IGNBRK nor BRKINT are set,
**		a BREAK reads as a null byte ('\0'), except when PARMRK is set, in which case it reads as
**		the sequence \377 \0 \0.
**
** PARMRK : If IGNPAR is not set, prefix a character with a parity error or framing error with \377 \0.
**		If neither IGNPAR nor PARMRK is set, read a character with a parity error or framing error as \0
**
** ISTRIP : If this bit is set, valid input bytes are stripped to seven bits; otherwise,
**		all eight bits are available for programs to read.
**
** INLCR : If this bit is set, newline characters ('\n') received as input are passed
**		to the application as carriage return characters ('\r').
**
** IGNCR : If this bit is set, carriage return characters ('\r') are discarded on input.
**		Discarding carriage return may be useful on terminals that send both carriage return and
**		linefeed when you type the RET key.
**
** ICRNL : If this bit is set and IGNCR is not set, carriage return characters ('\r')
**		received as input are passed to the application as newline characters ('\n').
**
** IXON : If this bit is set, start/stop control on output is enabled. In other words, if the computer
**		receives a STOP character, it suspends output until a START character is received. In this case,
**		the STOP and START characters are never passed to the application program. If this bit is not set,
**		then START and STOP can be read as ordinary characters. See section Special Characters for Flow Control.
**
**
**		|c_oflag|
**
** OPOST : If this bit is set, output data is processed in some unspecified way so that it is displayed
**		appropriately on the terminal device. This typically includes mapping newline characters ('\n')
**		onto carriage return and linefeed pairs. If this bit isn't set, the characters are transmitted as-is.
**
**
**		|c_lflag|
**
** ECHO : If this bit is set, echoing of input characters back to the terminal is enabled.
**
** ECHONL : If this bit is set and the ICANON bit is also set, then the newline ('\n') character is echoed even if the ECHO bit is not set.
**
** ICANON : This bit, if set, enables canonical input processing mode. Otherwise, input is processed in noncanonical mode
**
** ISIG : This bit controls whether the INTR, QUIT, and SUSP characters are recognized.
**		The functions associated with these characters are performed if and only if this bit is set.
**		Being in canonical or noncanonical input mode has no affect on the interpretation of these characters.
**		You should use caution when disabling recognition of these characters.
**		Programs that cannot be interrupted interactively are very user-unfriendly. If you clear this bit,
**		your program should provide some alternate interface that allows the user to interactively send
**		the signals associated with these characters, or to escape from the program.
**
** IEXTEN : POSIX.1 gives IEXTEN implementation-defined meaning, so you cannot rely on this
**		interpretation on all systems. On BSD systems and the GNU system, it enables the LNEXT
**		and DISCARD characters. See section Other Special Characters.
**
**
**		|c_cflag|
**
**	CSIZE : This is a mask for the number of bits per character.
**
**	PARENB : If this bit is set, generation and detection of a parity bit are enabled. See section Input Modes,
**		for information on how input parity errors are handled. If this bit is not set, no parity bit
**		is added to output characters, and input characters are not checked for correct parity.
**
**	CS8 : This specifies eight bits per byte.
**
*/

static int s_termios_init(t_termcaps_context *context)
{
	if (tcgetattr(0, &context->termios_old) != 0)
	{
		log_fatal("tcgetattr() failed");
		return (0);
	}
	context->termios_new = context->termios_old;
	context->termios_new.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | IXON
							 | INLCR | IGNCR | ICRNL);
	context->termios_new.c_oflag &= ~(OPOST | ONLCR);
	context->termios_new.c_oflag |= (OPOST | ONLCR);
	context->termios_new.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	context->termios_new.c_cflag &= ~(CSIZE | PARENB);
	context->termios_new.c_cflag |= CS8;
	context->termios_new.c_cc[VMIN] = 0;
	context->termios_new.c_cc[VTIME] = 10;
	return (1);
}

/*
** Emacs like
*/

static int s_initialize_key_map_meta(void)
{
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_M, &key__send));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_Q,
	&key__delete_command_line));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_D,
	&key__delete_under_cursor));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_A,
	&key__cursor_to_begin_of_line));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_E,
	&key__cursor_to_end_of_line));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_SPACE,
	&key__select));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_W, &key__cut));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_X, &key__copy));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_Y, &key__paste));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_K,
	&key__cut_to_end_of_line));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_CURSOR_LEFT,
	&key__cursor_to_prev_word));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_CURSOR_RIGHT,
	&key__cursor_to_next_word));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_BACKSPACE,
	&key__backspace));
	ASSERT(caps__init_func_by_keycode(CAPS__KEYCODE_CTRL_I,
	&key__completion));
	return (1);
}

/*
** Legit
*/

static int s_initialize_key_map_cursor(void)
{
	caps__init_func(DELETE_UNDER_CURSOR_KEY, &key__delete_under_cursor);
	caps__init_func(CURSOR_LEFT_KEY, &key__cursor_to_prev_character);
	caps__init_func(CURSOR_RIGHT_KEY, &key__cursor_to_next_character);
	caps__init_func(CURSOR_UP_KEY, &key__cursor_to_prev_command);
	caps__init_func(CURSOR_DOWN_KEY, &key__cursor_to_next_command);
	caps__init_func(SHIFTED_CURSOR_LEFT_KEY, &key__cursor_to_prev_word);
	caps__init_func(SHIFTED_CURSOR_RIGHT_KEY, &key__cursor_to_next_word);
	caps__init_func(SCROLLING_BACKWARD_KEY, &key__cursor_to_prev_line);
	caps__init_func(SCROLLING_FORWARD_KEY, &key__cursor_to_next_line);
	caps__init_func(CURSOR_HOME_KEY, &key__cursor_to_begin_of_line);
	caps__init_func(CURSOR_HOME_DOWN_KEY, &key__cursor_to_end_of_line);
	caps__init_func(BEGIN_KEY, &key__cursor_to_begin_of_line);
	caps__init_func(END_KEY, &key__cursor_to_end_of_line);
	caps__init_func(MARK_KEY, &key__select);
	caps__init_func(SELECT_KEY, &key__select);
	caps__init_func(COPY_KEY, &key__copy);
	caps__init_func(ENTER_KEY, &key__send);
	return (1);
}

int		termcaps_initialize(const int fd,
		const char *prompt,
		t_termcaps_context *context)
{
	if (fd < 0 || prompt == NULL || context == NULL)
	{
		log_error("fd %d prompt %p context %p", fd, (void *)prompt, (void *)context);
		return (0);
	}
	if (!s_initialize_key_map_meta() || !s_initialize_key_map_cursor())
	{
		log_fatal("s_initialize_key_map() failed");
		return (0);
	}
	context->state = STATE_REGULAR;
	if (!s_termios_init(context))
	{
		log_fatal("s_termios_init() failed");
		return (0);
	}
	context->fd = fd;
	context->prompt.size = ft_strlen(prompt);
	context->prompt.bytes = ft_strdup(prompt);
	if (context->prompt.bytes == NULL)
	{
		log_error("ft_strdup() failed");
		return (0);
	}
	list_head__init(&context->history);
	list_head__init(&context->command_line);
	list_head__init(&context->copy);
	context->selection_offset_start = 0;
	context->selection_offset_end = 0;
	context->buffer = NULL;
	context->is_initialized = 1;
	return (1);
}

int		termcaps_finalize(t_termcaps_context *context)
{
	list_head__history_destroy(&context->history);
	list_head__command_line_destroy(&context->command_line);
	list_head__command_line_destroy(&context->copy);
	free(context->prompt.bytes);
	context->is_initialized = 0;
	return (1);
}
