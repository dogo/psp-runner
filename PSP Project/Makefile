TARGET = Runner
CFLAGS = -G0 -Wall -O2
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

GAMEOBJECTS=Src/Main.o Src/ScreenManager.o Src/AnykeyScreen.o Src/Runner.o Src/Obstacles.o Src/Ranking.o Src/GameScreen.o
UTIL=Src/util/Drawing.o

OBJS = $(GAMEOBJECTS) $(UTIL)

LIBDIR =
LDFLAGS =
STDLIBS= -losl -lmikmod -lpng -lz -lpsphprm -lstdc++ \
		-lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgu -lpspaudiolib -lpspaudio -lm \
		-lpspmpeg -lpspaudiocodec
LIBS=$(STDLIBS)$(YOURLIBS)

BUILD_PRX = 1
PSP_FW_VERSION=390
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Runner
PSP_EBOOT_ICON = ICON0.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
