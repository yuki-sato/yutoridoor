# simple
yutoridoor:
	gcc -std=c99 -D_POSIX_C_SOURCE -lwiringPi -o yutoridoor cweb/cweb_object.c cweb/cweb_http.c cweb/cweb_render.c cweb/cweb_main.c main.c
