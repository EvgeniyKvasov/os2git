CC = icc
CFLAGS = 
OBJS = init.obj main.obj hash.obj

os2git.exe: $(OBJS)
	$(CC) $(OBJS) /Feos2git.exe
	
init.obj: Commands\init.cpp Commands\init.hpp
	$(CC) $(CFLAGS) /c Commands\init.cpp
	
main.obj: main.cpp
	$(CC) $(CFLAGS) /c main.cpp
	
hash.obj: Core\hash.cpp Core\hash.hpp
	$(CC) $(CFLAGS) /c Core\hash.cpp
	
clean:
	del *.obj os2git.exe
	