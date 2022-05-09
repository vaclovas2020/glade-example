build:
	g++ main.cc -o glade-example `pkg-config gtkmm-3.0 --cflags --libs`