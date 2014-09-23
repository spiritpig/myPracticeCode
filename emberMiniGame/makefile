cc := g++
OFLAG = -o
rd = rd
rm = del
mv = move
mkdir = mkdir
exeSuffix = bin
objSuffix = obj
gameExe = emberGame

# 后缀规则，指定了cpp或者c后缀的文件生成o后缀文件
# 执行的操作
.SUFFIXES: .o .cpp .c
.cpp.o: 
	$(cc) $(CPPFLAGS) -c $<
.c.o:
	$(cc) $(CPPFLAGS) -c $<

all: \
    mkBin \
    gameExe

#生成bin目录
mkBin:
	-$(mkdir) $(exeSuffix)

# 生成执行程序
gameExe: commonHeader.o emberMap.o
	-$(cc) $(OFLAG)$(exeSuffix)\$(gameExe) \
	emberMap.o \
	commonHeader.o \


# 生成库文件
emberMap.o: emberMap.cpp
commonHeader.o: commonHeader.cpp	

clean:
	-$(rd) /S /Q bin 
	-$(rm) *.o
