AM_CPPFLAGS = -I$(top_srcdir)/src/libWhistGame
AM_CPPFLAGS += -I$(top_srcdir)/src/AI
AM_CPPFLAGS += -I$(top_srcdir)/src/ServerWhist/database
AM_CPPFLAGS += -I$(top_srcdir)/src/ServerWhist/parser
AM_CPPFLAGS += -I$(top_srcdir)/src/ServerWhist/server
CFLAGS += -std=c99 -std=c++11 -g -Wall 
LDFLAGS += -lSDL2 -lSDL2_image -lSDL2_ttf -pthread -lmysqlcppconn -lboost_system

lib_LTLIBRARIES = libWhistGame.la libWhistGameAI.la
bin_PROGRAMS = Whist ClientTest Server

ClientTest_SOURCES = ClientWhist/main.cpp

Server_SOURCES = ServerWhist/main.cpp ServerWhist/database/Database.cpp \
		 ServerWhist/parser/parser.cpp ServerWhist/server/Player.cpp \
		 ServerWhist/server/Players.cpp ServerWhist/server/Connection.cpp \
		 ServerWhist/server/ProcessingCommand.cpp

Whist_SOURCES = Graphics/main.cpp Graphics/MenuWindow.cpp Graphics/Button.cpp \
		Graphics/BotsChoice.cpp Graphics/Symbol.cpp \
		Graphics/WindowMP.cpp Graphics/TypeChoice.cpp \
		Graphics/TableWindow.cpp Graphics/FireAnimationWhist.cpp \
		Graphics/SimpleAnimationWhist.cpp Graphics/ScoreWindow.cpp \
		Graphics/CardsFromTable.cpp Graphics/PlayerCards.cpp \
		Graphics/Players.cpp Graphics/Bid.cpp

Whist_LDADD = libWhistGame.la libWhistGameAI.la

libWhistGameAI_la_SOURCES = AI/robot.c

libWhistGame_la_SOURCES = libWhistGame/deck.c \
                          libWhistGame/player.c \
                          libWhistGame/hand.c \
                          libWhistGame/round.c \
                          libWhistGame/game.c
