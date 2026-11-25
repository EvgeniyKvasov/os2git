CC = icc
CFLAGS = 
OBJS = init.obj main.obj hash.obj add.obj status.obj objects.obj checkout.obj diff.obj commit.obj log.obj

os2git.exe: $(OBJS)
	$(CC) $(OBJS) /Feos2git.exe
	
init.obj: Commands\init.cpp Commands\init.hpp
	$(CC) $(CFLAGS) /c Commands\init.cpp
	
main.obj: main.cpp
	$(CC) $(CFLAGS) /c main.cpp
	
hash.obj: Core\hash.cpp Core\hash.hpp
	$(CC) $(CFLAGS) /c Core\hash.cpp
	
add.obj: Commands\add.cpp Commands\add.hpp Core\hash.hpp Core\objects.hpp
	$(CC) $(CFLAGS) /c Commands\add.cpp 
	
status.obj: Commands\status.cpp Commands\status.hpp
	$(CC) $(CFLAGS) /c Commands\status.cpp
	
objects.obj: Core\objects.cpp Core\objects.hpp
	$(CC) $(CFLAGS) /c Core\objects.cpp
	
checkout.obj: Commands\checkout.cpp Commands\checkout.hpp
	$(CC) $(CFLAGS) /c Commands\checkout.cpp
	
diff.obj: Commands\diff.cpp Commands\diff.hpp 
	$(CC) $(CFLAGS) /c Commands\diff.cpp 
	
commit.obj: Commands\commit.cpp Commands\commit.hpp 
	$(CC) $(CFLAGS) /c Commands\commit.cpp 

log.obj: Commands\log.cpp Commands\log.hpp 
	$(CC) $(CFLAGS) /c Commands\log.cpp 
	
clean:
	del *.obj os2git.exe
	