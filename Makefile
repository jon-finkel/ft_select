# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/25 23:01:23 by nfinkel           #+#    #+#              #
#    Updated: 2017/12/28 14:42:10 by nfinkel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

#	Environment
OS :=						$(shell uname)

#	Output
NAME :=						ft_select

#	Compiler
CC :=						gcc

ifneq ($(OS), Linux)
	FLAGS +=				-Wall -Wextra -Werror
endif

HEADERS :=					-I ./includes/
O_FLAG :=					-O2

#	Directories
LIBFTDIR :=					./libft/
OBJDIR :=					./build/

SRCS_DIR :=					./srcs/

#	Sources
SRC +=						main.c loop.c signal_handler.c input_arrow.c
SRC +=						restore_configuration.c get_coordinates.c
SRC +=						color_output.c display_files.c display_help.c
SRC +=						flag_reverse_video.c flag_underline.c

OBJECTS =					$(patsubst %.c,$(OBJDIR)%.o,$(SRCS))

SRCS +=						$(SRC)

vpath %.c $(SRCS_DIR)

#################
##    RULES    ##
#################

all: $(NAME)

$(NAME): $(OBJECTS)
	@printf "\e[32m\e[1m[Object files compiled]\e[m\n"
	@$(CC) $(DEBUG) $(FLAGS) $(O_FLAG) $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(SRCS))) -L $(LIBFTDIR) -lft -lncurses -o $@
	@printf "\e[32m\e[1m[Binary file \e[91m\e[1m$(NAME) \e[32m\e[1mcompiled!]\e[m\n"

$(OBJECTS): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)%.o: %.c
	$(CC) $(DEBUG) $(FLAGS) $(O_FLAG) $(HEADERS) -c $< -o $@

clean:
	@/bin/rm -rf $(OBJDIR)
	@printf "\e[32m\e[1m[Object files cleaned]\e[m\n"
#	@$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	@/bin/rm -f $(NAME)
	@printf "\e[32m\e[1m[Binary file \e[91m\e[1m$(NAME) \e[32m\e[1mcleaned]\e[m\n"
#	@$(MAKE) fclean -C $(LIBFTDIR)

libft:
	@$(MAKE) -C $(LIBFTDIR)

noflags: FLAGS :=
noflags: re

re: fclean all

.PHONY: all cat clean fclean libft noflags re

#################
##  WITH LOVE  ##
#################

cat:
	@clear;
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@#\`.\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@:\`\`\`,.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@.\`:\`\`.,,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@,.;,\`\`\`,,.\`,\`#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`:;\`\`  \`\`,::::.\`\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@#;;\`;\`   \`\`\`\`::::,\`+@@@@@;\`\`\`..,,,:,,,,.\`\`:#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;:\`\`;\`\`   \`\`\`\`\`,:::.\`,,::::::::::::::::::::,,..#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;,\`\`\`;\`\`    \`\`\`\`\`,::::::::::,,,,,,,,,,::::::::::,\`;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:,##+\`:,\`\`   \` \`\`\`\`,.:,\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.,::::::,\`\`@@@@@@@@@@@@@@@@@@@@@@@@\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.;#@;+\`;;\`\`   \`\`\`\`\`\` \`\`\`\`\`\`   \`\`\`\`\`\`   \`\`\`\`\`\`\`\`.::::::,\`@@@@@@@@@@@@@@@@@@@@@. @@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,\`#@##+:+;\`\`   \`\`\`\`    \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  \`\`\`:::::::,.@@@@@@@@@@@@@@@@@\`,,\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`\`\`@#\`@@@#;\`\`  \`\`\`\`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`::::::::,\`#@@@@@@@@@@@@#\`::.\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`,:\`;@@@@@\`\`\`  \`\`\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`:::::::::,.@@@@@@+;:..::::\`\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:,#:@@@@@@@\`\`\`  \`\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`,:::::::::,::\`.:::::::::\`\`\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.;##@@@@@@@@:\`       \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`.::::::::::.::::::::,\`\` \`.@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.;##@@@@@@@@#.\`  \`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,:::::::::,:.\`\`\`\`\`\`\` \`:,@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;\`,\`@@@@@@@@@#\`\`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`::::::::::\`\` \`\`\`   \`\`\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#;.\`\`@@@@@@@@#;\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`.:::::::::\`\` \`\`  \`;:@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,:.\`;#@@@##,\`\`\`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  \`\`\`.::::::::\`\`    \`:.@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:+.:+#\`+#:\`\`\`\`\`\`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.:::::::\`\`\` \`+;\`@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`;\`::#\`.\`\`\`\`\` \`\`   \`\`\`  \`\`\`\`\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.:::::,\` \`:\`+\`@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@.+\` \`\`\`\`\`\`\` \`\`\`\`\`\`\`\`\`   \`\`\`\`\`\`\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`\`\`,:::,\`\`#+:;@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`.\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`\`###+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`\`\`.:\`#+\`\`@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`+##@@@@#+.\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`\`.:+#;\`@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`+#@@@@@@@@#:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`,,:;;@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@@@@@@@@#;\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`:,\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@,:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`@@@@@@@@@@@@@#,\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@,\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@@@@@@@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,.@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`;#@@@@@@@@@@@@@@@+\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`;##\`\`\`\`,#@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@+;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@@##+\`+##@@@@#.\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@+\`\`\`,\`@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@,:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@#,:...:+#@@@@+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@\`\`\`\`,@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@,,\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:#@@@#,.,,,,,,\`#@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:#@@@#\`\`\`,:@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`@@@#\`,,,,,,,,:+@@@#;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`+@@@@#;\`\`\`.@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@@#:,,,,,,,,,:#@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@@#\`\`\`,@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@;\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@#,,,,,,,,,,,#@@@#\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`####@@#\`\`\`.\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`;\` \`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@:,,,,,,,,,,,,#@@@.\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+:;+@@#:\`\`\`.@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@;;\` \`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,,.,,,,,;#@@@;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:,,:#@@+\`\`\`.@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@.;\`\`    \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#;,,,,\` \`,,,,,#@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:,,,+@@#\`\`\`\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`\` \`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,\`  ,,,,.+@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.,,,,#@#\`\`\`\`#@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`\`\`\`  \`\`\`\`\`\`\`\`\`\`\`\` \`#@@#:,,,,   .,,,,;@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,,,,;#@#\`\` \`;@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`  \`  \`\`\`\`\`\`\`\`\`\`\`\` \`#@@#:,,,,   \`,,,,:#@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,,,,:#@#.\`\`\`.@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`  \`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,    ,,,,:#@@#\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,\`.,,+@#:\`  \`@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`     \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,    ,,,,:#@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.. \`,,+@#;\`   @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`     \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,    ,,,,:#@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.  ,.\`@@;\`   @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`;\`    \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,\`   ,,,,:#@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  ,.;@#;\` \` @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@.;\`\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@#:,,,,.  \`,,,;;#@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  ,.;@#:\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@:\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`@@@:,,,,,  .,,#@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  ,.;##:\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@+\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`;#@@#.,,,,\`\`,,,#@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  ,.;##,\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,,,,,,,.+@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`,:#@#\`\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,,,,,,,,#@@@+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`. .,@@@#\`\`\`  @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@,,\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@@+,,,,,,,,,,;#@@@;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,\`,,#@@#\`\`\`  @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@.;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:#@@#,,,,,,,,,,;@@@#.\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`,,,,:@@#\`\`\` \`@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@;,\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@#:,,,,,,,:#@@@#\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`.,,,+@@+\`\`\` \`@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@+\`:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@@##:,,,,,:#@@@@+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`:,,:#@#;\`\`\` \`@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@,:.\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.#@@@@#\`:::;#@@@@#\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`;::\`#@#.\` \` \`@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@+;\` \`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@@@@@####@@@@@+\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:#\`#@@#\`\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`;\`    \`\`\`\`\`\`\`\`\`\`\`\`\`\`.#@@@@@@@@@@@@@#.\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@\`\`\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;.  \`\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@@@@@@@@#+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@#.\`\`\` \`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;;\` \`:,\`\`  \`\`\`\`\`\`\`\` \`\`+#@@@@@@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@@#\`\`\`\` \`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.;\` \`;;,\` \`  \`\`\`\`\`\`\`\`\`+@@@@@@@@##\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`,#@#.\`\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.:  \`\`\`\`;\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@##+\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+#,\`\`    @@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@#@@@@@@@@@@@@@@,\`  .\`\`\`\`;.\`\`\`  \`\`\`\`\`\`\`;+++,\`\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`\`  \`\` #@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@;.@@@@@@@@@@@@@@.\`  ,\`\`\`\`\`;:\`\`       \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`  \`   @@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@\`;\`\`@@@@@@@@@@@@.\` \`:\`\`\`\`\`#+\`,\`\`\`\` \` \`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`    @@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@\`+;:\`;@@@@@@@@@@.\` \`:\`\`\`\`@@@@#+;\`\`\`\`\`\`\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@\`+\`\`\`;;;;;;;;;;;:,\` \`:\`\`\`+@@@@@@@##\`.\`\`\`\`\`\`    \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`   \`\`\`\`.\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@.+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`;.  ,\`\`\`#@@@@@@@@@@##\`,\`\`\`\`\`\`    \`\` \`  \`\`\`\`\`\`\`\`\`\`\`   \`     \`\`.\`#:@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@:+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`;\`  .;\`\`@@@@@@@@@@@@@@@##\`:.\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.\`#@@\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`;.  \`;\`\`@@@@@@@@@@@@@@@@@@@@####+;,..\`\`\`\`\`\`\`\`\`\`\`\`\`.:\`###@@@@\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@\`+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`;:\` \`;\`+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########@@@@@@@@@@@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@:+\`\`\`\`\`\`\`::::,:::::,\` \`.;\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@.+\`\`\`\`\`\`:::,.,,,,.,,,\`\`\`:\`#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@.+\`\`\`\`\`;:::,,,..,,,,..\`\`\`\`#@@@@@@@@@@@@@@@@@@#@@@@@@@@@@#@@@@@@@@+@@#+,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@,+\`\`\`\`\`\`;::::,,,,,,,,,.\`\`,\`@@@@@@@@@@@@@@@@@##@@@@@@@@#.#@@@@@#+@@#.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@\`+\`\`\`\`\`\`\`;;::,,,,,,,,,,..\`.+#@@@@@@@@@@@@@@@#;#@@@##,##;+##;\`#@#,\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@#:+\`\`\`\`\`\`;;;;::,,,,,,,,..,.\`;#@@@@@@@@@@@@@@@#+::+#@@@@@##@##.;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,\`\`\`\`\`;;;:,,,:;;:,,,.,.\`.\`,,.\`##@@@@@@@@@@@@@@@@@@@@@@@#\`.+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`\`;;;;;;;;;;;;::,,. \`.  .,,,\`\`.\`###@@@@@@@@@@@@@@##;\`;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#..,;;,:;;;;;;:,,,....      ,,,,,,\`\`\`\`.,:\`\`+++++\`:,.:#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@:,;;;;\`\`\`;;;,,....,,,,,,.\`      ,,::::,,\`\`      \`...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@,+\`\`\`\`\`\`\`\`;;:,,,,,,,,\`         ,,:::::::,,.\`\`\`\`\`...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#:+\`\`\`\`\`\`\`\`;;::,,,,,.          ::::::::::::::,,,,.+:\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+:+\`\`\`\`\`\`\`\`;;;:,.\`.:\`         :;::::::::::::::,\`  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`:\`\`\`\`\`\`\`\`;;:\`+@#\`\`          ,;;::::::::::::,.     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,:\`\`\`;;,.#@@@\`\`            .;\`\`:::::::::,;,   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#;:@@@@@@\`\`              \`;\`\`\`;::::::\`\`:     #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:.                 \`;\`\`\`\`\`\`\`\`\`\`;       .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+,                   \`,;\`\`\`\`\`\`\`\`;     .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:\`                      .;\`\`\`\`\`\`;\`     \`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`\`          .\`             \`:;\`\`\`;\`     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+:          .:\`               \`.;\`;\`      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,\`          @.,                  \`.        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;,          ;@\`:                             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,\`          @@,;                              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
