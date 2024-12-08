NAME=binary_div
DIR=${PREFIX}/local/bin
FLAGS = -fuse-ld=lld -pie -g -std=gnu11

# For PC
pc:
	gcc -std=gnu11 -pie -Og -g ${wildcard ../*.c} -o ${NAME}.exe

clean_pc:
	rm -f ${NAME}.exe

# For android, using termux
android: aarch64

android_run: android
	${DIR}/${NAME}
	
android_debug: android
	lldb ${DIR}/${NAME}

arm:
	clang --target=armv7-linux-androideabi ${FLAGS} -o $(DIR)/$(NAME) ${wildcard ../*.c} 

aarch64:
	clang --target=aarch64-linux-androideabi ${FLAGS} -o $(DIR)/$(NAME) ${wildcard ../*.c}
	
clean_android:
	rm -f $(DIR)/$(NAME)
