#yup
#
# Jennifer Utley
# jau100020@utdallas.edu
# SE 3377.501
# Makefile for program 6

CXX = g++
CXXFLAGS = -Wall
CPPFLAGS = -Wall -g -I /scratch/perkins/include
LDFLAGS = -L /scratch/perkins/lib
LDLIBS = -l cdk -l curses
EXECFILE = prog6
PROJECTNAME = prog6backup
OBJS = prog6.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*
	@echo Removed unnecessary files.


$(EXECFILE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
	@echo Created the $(EXECFILE) executable.

# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

