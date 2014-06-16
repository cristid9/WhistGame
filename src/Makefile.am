AM_CPPFLAGS = -I$(top_srcdir)/src/libWhistGame
LDFLAGS = -no-undefined
CFLAGS += -std=c99 -g -Wall

lib_LTLIBRARIES = libWhistGame.la libWhistGameAI.la

libWhistGameAI_la_SOURCES = AI/robot.c

libWhistGame_la_SOURCES = libWhistGame/deck.c \
                          libWhistGame/player.c \
                          libWhistGame/hand.c \
                          libWhistGame/round.c \
                          libWhistGame/game.c
